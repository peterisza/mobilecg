/*
 * aducloader - A serial download program for ADuC702x microcontrollers
 * Copyright (C) 2006, 2007 Robert Fitzsimons
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  Look for the COPYING file in the top
 * level directory.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * This is an in-circuit serial download program for the Analog Devices
 * ADuC702x range of microcontrollers.  The relevant protocol details
 * are described in application note AN-724.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <poll.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

struct record {
	struct record *next;
	int count;
	uint32_t address;
	uint8_t data[0];
};

const int DATA_BUFFER_SIZE = 250;
uint8_t *io_buffer;
uint8_t *data_buffer;

int reset;
int follow;

int serial_open(const char *ttyfilename, speed_t speed);
int serial_close(int fd);
int serial_read_fully(int fd, uint8_t *buffer, int count, int timeout);
int serial_write_fully(int fd, const uint8_t *buffer, int count, int timeout);
int serial_read(int fd, uint8_t *buffer, int count, int timeout);

int baudrate_to_speed_t(const char *baudrate, speed_t *speed);

int fill_packet(uint8_t *buffer, char cmd, uint32_t address, const uint8_t *data, int data_len);
void dump_buffer(FILE *f, const uint8_t *buffer, int len);
void dump_text(FILE *f, const uint8_t *buffer, int len);
int process_ihexfile(const char *filename, struct record **rec_p);
int do_serial_comms(const char *devfilename, const char *baudrate, struct record *root);

int main(int argc, char **argv)
{
	int rc = 0;
	struct record *root = NULL;
	struct record *rec;
	struct record *nrec;
	const char *ttyfile = NULL;
	const char *ihexfile = NULL;
	const char *baudrate = "9600";

	while (1) {
		static struct option long_options[] = {
			{"ttyfile", 1, 0, 't'},
			{"ihexfile", 1, 0,'i'},
			{"baudrate", 1, 0,'b'},
			{"reset", 0, &reset, 1},
			{"follow", 0, &follow, 1},
			{0, 0, 0, 0},
		};
		int option_index = 0;
		int c = getopt_long(argc, argv, "", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
		case 0:
			break;
		case 't':
			ttyfile = optarg;
			break;
		case 'i':
			ihexfile = optarg;
			break;
		case 'b':
			baudrate = optarg;
			break;
		default:
			goto usage_error;
		}
	}

	if ((optind < argc) || (ttyfile == NULL) || (ihexfile == NULL)) {
		goto usage_error;
	}

	fprintf(stderr, "aducloader, " ADUCLOADER_VERSION "\n");

	io_buffer = malloc(sizeof(uint8_t) * 1024);
	if (io_buffer == NULL) {
		fprintf(stderr, "error allocating io_buffer memory\n");
		rc = -1;
		goto error;
	}

	data_buffer = malloc(sizeof(uint8_t) * 256);
	if (data_buffer == NULL) {
		fprintf(stderr, "error allocating data_buffer memory\n");
		rc = -1;
		goto error;
	}

	if (process_ihexfile(ihexfile, &root) < 0) {
		fprintf(stderr, "error processing ihex_file\n");
		rc = -1;
		goto error;
	}

	if (do_serial_comms(ttyfile, baudrate, root) < 0) {
		fprintf(stderr, "serial comms failed\n");
		rc = -1;
		goto error;
	}

error:
	for (rec = root; rec != NULL; rec = nrec) {
		nrec = rec->next;
		free(rec);
	}

	if (data_buffer != NULL) {
		free(data_buffer);
	}

	if (io_buffer != NULL) {
		free(io_buffer);
	}

	return rc;

usage_error:
	fprintf(stderr, "Usage: %s --ttyfile=<ttyfile> --ihexfile=<ihexfile> [--baudrate=9600] [--reset] [--follow]\n", argv[0]);
	return -2;
}

int do_serial_comms(const char *ttyfile, const char *baudrate, struct record *root)
{
	int fd;
	int len;
	speed_t speed;
	uint8_t *ptr;
	struct record *rec;
	const uint8_t BACKSPACE[] = {0x08};
	const uint8_t ERASE_ALL[] = {0x00};
	const uint8_t ACK = 0x06;
	ptr = io_buffer;

	if (baudrate_to_speed_t(baudrate, &speed)) {
		fprintf(stderr, "unsupported baudrate, %s\n", baudrate);
		return -1;
	}

	fd = serial_open(ttyfile, speed);
	if (fd < 0) {
		fprintf(stderr, "error opening serial port\n");
		return -1;
	}

	fprintf(stdout, "Trying to synchronize with ADuC70xx: ");
	fflush(stdout);
	
	while (serial_read_fully(fd, ptr, 1, 100));
	
	do {
		len = serial_write_fully(fd, BACKSPACE, sizeof(BACKSPACE), 1000);
		len = serial_read_fully(fd, ptr, 24, 100);
		
	} while (!((len > 6) && (memcmp(ptr, "ADuC70", 6) == 0)));
	
	while (serial_read_fully(fd, ptr, 1, 100));

	if ((len > 6) && (memcmp(ptr, "ADuC70", 6) == 0)) {
		int product_len = (memchr(ptr, ' ', 24) - (void *)ptr);
		fprintf(stdout, "Found %.*s\n", product_len, ptr);

		fprintf(stdout, "Erasing: ");
		fflush(stdout);

		len = fill_packet(ptr, 'E', 0x00000000, ERASE_ALL, sizeof(ERASE_ALL));
		len = serial_write_fully(fd, ptr, len, 1000);
		len = serial_read_fully(fd, ptr, 1, 10000);

		if ((len <= 0) || (ptr[0] != ACK)) {
			fprintf(stdout, "FAILED\n");
			goto error;
		}

		fprintf(stdout, "OK\n");

		rec = root;
		while (rec != NULL) {
			int count = 0;
			uint32_t address = rec->address;
			uint8_t *data = data_buffer;
			struct record *drec;

			for (drec = rec; ((drec != NULL) && ((address + count) == drec->address) && ((count + drec->count) < DATA_BUFFER_SIZE)); drec = drec->next) {
				memcpy(data, drec->data, drec->count);
				data += drec->count;
				count += drec->count;
			}
			rec = drec;

			fprintf(stdout, "Writting (%#x): ", address);
			fflush(stdout);

			len = fill_packet(ptr, 'W', address, data_buffer, count);
			len = serial_write_fully(fd, ptr, len, 1000);
			len = serial_read_fully(fd, ptr, 1, 10000);

			if ((len <= 0) || (ptr[0] != ACK)) {
				fprintf(stdout, "FAILED\n");
				goto error;
			}

			fprintf(stdout, "OK\n");
		}

		if (reset) {
			fprintf(stdout, "Resetting: ");
			fflush(stdout);

			len = fill_packet(ptr, 'R', 0x00000001, NULL, 0);
			len = serial_write_fully(fd, ptr, len, 1000);
			len = serial_read_fully(fd, ptr, 1, 10000);

			if ((len <= 0) || (ptr[0] != ACK)) {
				fprintf(stdout, "FAILED\n");
				goto error;
			}

			fprintf(stdout, "OK\n");
		}
	} else {
		fprintf(stdout, "FAILED\n");
		goto error;
	}

	if (follow) {
		int count = 600;
		while (count--) {
			len = serial_read(fd, ptr, 16, 1000);
			if (len > 0) {
				dump_text(stdout, ptr, len);
			}
		}
	}

error:
	if (serial_close(fd) < 0) {
		fprintf(stderr, "error closing serial port\n");
		return -1;
	}

	return 0;
}

int serial_open(const char *ttyfilename, speed_t speed)
{
	int fd;
	int rc;
	struct termios termio;
	const char *message;

	fd = open(ttyfilename, O_RDWR | O_NONBLOCK | O_NOCTTY);
	if (fd < 0) {
		fprintf(stderr, "serial_open: open failed (%s): %s\n", ttyfilename, strerror(errno));
		return -1;
	}

	rc = fcntl(fd, F_SETFL, 0);
	if (rc < 0) {
		message = "fcntl failed";
		goto error_close;
	}

	rc = tcflush(fd, TCIOFLUSH);
	if (rc < 0) {
		message = "tcflush failed";
		goto error_close;
	}

	rc = tcgetattr(fd, &termio);
	if (rc < 0) {
		message = "tcgetattr failed";
		goto error_close;
	}

	cfmakeraw(&termio);
	rc = cfsetispeed(&termio, speed);
	if (rc < 0) {
		message = "cfsetispeed failed";
		goto error_close;
	}
	rc = cfsetospeed(&termio, speed);
	if (rc < 0) {
		message = "cfsetospeed failed";
		goto error_close;
	}
	termio.c_cflag &= ~PARENB;
	termio.c_cflag &= ~CSTOPB;
	termio.c_cflag &= ~CSIZE;
	termio.c_cflag |= (CLOCAL | CREAD | CS8);

	rc = tcsetattr(fd, TCSANOW, &termio);
	if (rc < 0) {
		message = "tcsetattr failed";
		goto error_close;
	}

	return fd;

error_close:
	fprintf(stderr, "serial_open: %s: %s\n", message, strerror(errno));
	serial_close(fd);
	return -1;
}

int serial_close(int fd)
{
	if (close(fd) < 0) {
		fprintf(stderr, "serial_close: close failed: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}

int serial_read_fully(int fd, uint8_t *buffer, int count, int timeout)
{
	struct pollfd fds;
	int rc;
	int len;
	uint8_t *ptr = buffer;

	while (count > 0) {
		fds.fd = fd;
		fds.events = POLLIN;

		rc = poll(&fds, 1, timeout);
		if (rc == 0) {
			//fprintf(stderr, "serial_read_fully: poll timeout\n");
			break;
		} else if (rc < 0) {
			fprintf(stderr, "serial_read_fully: poll failed %s\n", strerror(errno));
			return -1;
		}

		if (fds.revents & (POLLERR | POLLHUP | POLLNVAL)) {
			fprintf(stderr, "serial_read_fully: poll revents (%hx)\n", fds.revents);
			return -1;
		} else if (fds.revents & (POLLIN)) {
			len = read(fd, ptr, count);
			if (len < 0) {
				//fprintf(stderr, "serial_read_fully: read failed %s\n", strerror(errno));
				return -1;
			}
			ptr += len;
			count -= len;
		}
	}

	return ptr - buffer;
}

int serial_write_fully(int fd, const uint8_t *buffer, int count, int timeout)
{
	struct pollfd fds;
	int rc;
	int len;
	const uint8_t *ptr = buffer;

	while (count > 0) {
		fds.fd = fd;
		fds.events = POLLOUT;

		rc = poll(&fds, 1, timeout);
		if (rc == 0) {
			fprintf(stderr, "serial_write_fully: poll timeout\n");
			break;
		} else if (rc < 0) {
			fprintf(stderr, "serial_write_fully: poll failed %s\n", strerror(errno));
			return -1;
		}

		if (fds.revents & (POLLERR | POLLHUP | POLLNVAL)) {
			fprintf(stderr, "serial_write_fully: poll revents (%hx)\n", fds.revents);
			return -1;
		} else if (fds.revents & (POLLOUT)) {
			len = write(fd, ptr, count);
			if (len < 0) {
				fprintf(stderr, "serial_write_fully: write failed %s\n", strerror(errno));
				return -1;
			}
			ptr += len;
			count -= len;
		}
	}

	return ptr - buffer;
}

int serial_read(int fd, uint8_t *buffer, int count, int timeout)
{
	struct pollfd fds;
	int rc;
	int len;
	uint8_t *ptr = buffer;

	while (count > 0) {
		fds.fd = fd;
		fds.events = POLLIN;

		rc = poll(&fds, 1, timeout);
		if (rc == 0) {
			break;
		} else if (rc < 0) {
			fprintf(stderr, "serial_read: poll failed %s\n", strerror(errno));
			return -1;
		}

		if (fds.revents & (POLLERR | POLLHUP | POLLNVAL)) {
			fprintf(stderr, "serial_read: poll revents (%hx)\n", fds.revents);
			return -1;
		} else if (fds.revents & (POLLIN)) {
			len = read(fd, ptr, count);
			if (len < 0) {
				fprintf(stderr, "serial_read: read failed %s\n", strerror(errno));
				return -1;
			}
			ptr += len;
			count -= len;

			break;
		}
	}

	return ptr - buffer;
}

int baudrate_to_speed_t(const char *baudrate, speed_t *speed)
{
	long int baud = strtol(baudrate, NULL, 10);
	if (errno != 0) {
		return -1;
	}
	switch (baud) {
	case 600: *speed = B600; break;
	case 1200: *speed = B1200; break;
	case 1800: *speed = B1800; break;
	case 2400: *speed = B2400; break;
	case 4800: *speed = B4800; break;
	case 9600: *speed = B9600; break;
	case 19200: *speed = B19200; break;
	case 38400: *speed = B38400; break;
	case 57600: *speed = B57600; break;
	case 115200: *speed = B115200; break;
	default:
		return -1;
	}
	return 0;
}

int fill_packet(uint8_t *buffer, char command, uint32_t address, const uint8_t *data, int data_len)
{
	uint8_t *ptr = buffer;
	uint8_t checksum = 0;
	int i;

	address &= 0xFFFF;

	*(ptr++) = 0x07;
	*(ptr++) = 0x0E;

	checksum += *(ptr++) = 5 + data_len;

	checksum += *(ptr++) = command;

	checksum += *(ptr++) = (address >> 24) & 0xFF;
	checksum += *(ptr++) = (address >> 16) & 0xFF;
	checksum += *(ptr++) = (address >>  8) & 0xFF;
	checksum += *(ptr++) = (address >>  0) & 0xFF;

	for (i = 0; i < data_len; i++) {
		checksum += *(ptr++) = data[i];
	}

	*(ptr++) = 0x00 - checksum;

	return ptr - buffer;
}

void dump_buffer(FILE *f, const uint8_t *buffer, int len)
{
	int i;

	fprintf(f, "Buffer Length %d\n", len);
	for (i = 0; i < len; i++) {
		fprintf(f, "%2.2x", buffer[i]);
	}
	fprintf(f, "\n");
}

void dump_text(FILE *f, const uint8_t *buffer, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		uint8_t c = buffer[i];
		fputc(((isprint(c) || isspace(c)) ? (c) : ('.')), f);
	}
}

int hex1(uint8_t **buffer, uint8_t *value)
{
	uint8_t c = *((*buffer)++);
	if ((c >= '0') && (c <= '9'))
		*(value) = (c - '0');
	else if ((c >= 'A') && (c <= 'F'))
		*(value) = ((c - 'A') + 10);
	else if ((c >= 'a') && (c <= 'f'))
		*(value) = ((c - 'a') + 10);
	else
		return -1;
	return 0;
}

int hex2(uint8_t **buffer, uint8_t *value)
{
	uint8_t v;
	if ((hex1(buffer, &v)) < 0) {
		return -1;
	}
	*(value) = (v << 4);
	if ((hex1(buffer, &v)) < 0) {
		return -1;
	}
	*(value) |= v;
	return 0;
}

int hex4(uint8_t **buffer, uint16_t *value)
{
	uint8_t v;
	if ((hex2(buffer, &v)) < 0) {
		return -1;
	}
	*(value) = (v << 8);
	if ((hex2(buffer, &v)) < 0) {
		return -1;
	}
	*(value) |= v;
	return 0;
}

int read_fully(int fd, uint8_t *buffer, int count)
{
	int len;
	uint8_t *ptr = buffer;
	
	while (count > 0) {
		len = read(fd, buffer, count);
		if (len < 0) {
			fprintf(stderr, "read_fully: read failed %s\n", strerror(errno));
			return -1;
		} else if (len == 0) {
			return 0;
		}
		ptr += len;
		count -= len;
	}

	return ptr - buffer;
}

int process_ihexfile(const char *ihexfile, struct record **rec_p)
{
	int fd;
	int rc;
	int i;
	int len;
	uint8_t *ptr;
	uint8_t c;
	uint8_t ih_count;
	uint16_t ih_address;
	uint8_t ih_type;
	uint8_t ih_data[256];
	uint8_t ih_checksum;
	uint32_t ip = 0;
	struct record *rec;

	fd = open(ihexfile, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "process_ihexfile: open failed (%s) :%s\n", ihexfile, strerror(errno));
		return -1;
	}

	while (1) {
 		ptr = io_buffer;
		len = read_fully(fd, ptr, 1);
		if (len < 0)
			goto read_error;
		else if (len == 0)
			break;

		c = *(ptr++);
		if (c == '\n')
			continue;
		else if (c == '\r')
			continue;
		if (c != ':')
			goto data_error;

 		ptr = io_buffer;
		len = read_fully(fd, ptr, 8);
		if (len < 0)
			goto read_error;
		else if (len == 0)
			goto data_error;

		if (hex2(&ptr, &ih_count) < 0)
			goto data_error;
		if (hex4(&ptr, &ih_address) < 0)
			goto data_error;
		if (hex2(&ptr, &ih_type) < 0)
			goto data_error;

		if (ih_count > 0) {
			ptr = io_buffer;
			len = read_fully(fd, ptr, (ih_count * 2));
			if (len < 0)
				goto read_error;
			else if (len == 0)
				goto data_error;

			for (i = 0; i < ih_count; i++) {
				if (hex2(&ptr, &ih_data[i]) < 0)
					goto data_error;
			}
		}

 		ptr = io_buffer;
		len = read_fully(fd, ptr, 2);
		if (len < 0)
			goto read_error;
		else if (len == 0)
			goto data_error;

		if (hex2(&ptr, &ih_checksum) < 0)
			goto data_error;

		if (ih_type == 0x00) {
			rec = malloc(sizeof(struct record) + (sizeof(uint8_t) * ih_count));
			if (rec == NULL)
				goto memory_error;
			rec->next = NULL;
			rec->count = ih_count;
			rec->address = ip + ih_address;
			memcpy(rec->data, ih_data, ih_count);
			*(rec_p) = rec;
			rec_p = &rec->next;
		} else if (ih_type == 0x02) {
			ip = (((ih_data[0] << 8) | (ih_data[1] << 0)) << 4);
		} else if (ih_type == 0x04) {
			ip = (((ih_data[0] << 8) | (ih_data[1] << 0)) << 16);
		}
	}
	rc = 0;
	goto close;

memory_error:
	fprintf(stderr, "process_ihexfile: memory error\n");
	rc = -1;
	goto close;
read_error:
	fprintf(stderr, "process_ihexfile: read error\n");
	rc = -1;
	goto close;
data_error:
	fprintf(stderr, "process_ihexfile: data error\n");
	rc = -1;
	goto close;

close:
	if (close(fd) < 0) {
		fprintf(stderr, "process_ihexfile: close failed %s\n", strerror(errno));
		return -1;
	}

	return rc;
}

