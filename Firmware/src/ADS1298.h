#ifndef SRC_ADS1298_H_
#define SRC_ADS1298_H_

#include <GPIO.h>

class ADS1298 {
	private:
		GPIO reset;
		GPIO pwdn;
		GPIO pinStart;
		GPIO diffSel;

		enum Register {REG_ID=0, REG_CONFIG1=1, REG_CONFIG2=2, REG_CONFIG3=3};
		enum Command {CMD_WAKEUP = 0x02, CMD_RREG = 0x20, CMD_WREG = 0x40, CMD_SDATAC = 0x11, CMD_START = 0x08, CMD_RDATAC = 0x10};
		enum SpeedDiv {DIV_64=0, DIV_128, DIV_256, DIV_512, DIV_1024, DIV_2048, DIV_4096, DIV_8192};

		int nHardwareChannels;
		static const int FCLK=2000000;

		float realFreq;

		ADS1298();
	public:
		static ADS1298& instance();

		bool start();
		void stop();

		void interrupt();
	private:
		void sendCommand(Command cmd);
		void writeReg(Register reg, uint8_t value);
		uint8_t readReg(Register reg);
		float setSpeed(SpeedDiv div, bool highRes=true);

};

#endif /* SRC_ADS1298_H_ */
