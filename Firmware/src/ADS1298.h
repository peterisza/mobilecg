#ifndef SRC_ADS1298_H_
#define SRC_ADS1298_H_

#include <GPIO.h>

class ADS1298 {
	private:
		GPIO reset;
		GPIO pwdn;
		GPIO pinStart;
		GPIO diffSel;

		enum Register {REG_ID=0};
		enum Command {CMD_WAKEUP = 0x02, CMD_RREG = 0x20, CMD_WREG = 0x40};
		int nHardwareChannels;
	public:
		ADS1298();
		virtual ~ADS1298();

		bool start();
		void stop();
	private:
		void sendCommand(Command cmd);
		void writeReg(Register reg, uint8_t value);
		uint8_t readReg(Register reg);
};

#endif /* SRC_ADS1298_H_ */
