#ifndef SRC_ADS1298_H_
#define SRC_ADS1298_H_

#include <GPIO.h>
#include <CircularBuffer.h>

#define ADS1298_MAX_PACKET_LENGTH ((8+1)*24)

class ADS1298 {
	private:
		GPIO reset;
		GPIO pwdn;
		GPIO pinStart;
		GPIO diffSel;

		char dmaDestBuffer[ADS1298_MAX_PACKET_LENGTH];
		char zeroBuffer[ADS1298_MAX_PACKET_LENGTH];

		enum Register {REG_ID=0, REG_CONFIG1=1, REG_CONFIG2=2, REG_CONFIG3=3};
		enum Command {CMD_WAKEUP = 0x02, CMD_RREG = 0x20, CMD_WREG = 0x40, CMD_SDATAC = 0x11, CMD_START = 0x08, CMD_RDATAC = 0x10, CMD_STOP = 0x0A};
		enum SpeedDiv {DIV_64=0, DIV_128, DIV_256, DIV_512, DIV_1024, DIV_2048, DIV_4096, DIV_8192};

		int nHardwareChannels;
		int selectedChannels;
		int dataTransferSize;
		uint32_t sampleId;

		static const int FCLK=2000000;

		float realFreq;

		ADS1298();
	public:
		struct ECGBlock{
			uint32_t status:24;
			uint32_t channel1:24;
			uint32_t channel2:24;
			uint32_t channel3:24;
			uint32_t channel4:24;
			uint32_t channel5:24;
			uint32_t channel6:24;
			uint32_t channel7:24;
			uint32_t channel8:24;
		} __attribute__((packed));

		typedef CircularBuffer<uint8_t, 4096, true> EcgBuffer;
		static ADS1298& instance();

		bool start();
		void stop();

		EcgBuffer &getBuffer();

		void interrupt();
		uint32_t getSampleId();
		uint8_t getActiveChannels();
	private:
		void sendCommand(Command cmd);
		void writeReg(Register reg, uint8_t value);
		uint8_t readReg(Register reg);
		float setSpeed(SpeedDiv div, bool highRes=true);
		void enableIrq();
		void disableIrq();

		bool dmaRunning;

		EcgBuffer ecgBuffer;

};

#endif /* SRC_ADS1298_H_ */
