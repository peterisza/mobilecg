#ifndef SRC_ADS1298_H_
#define SRC_ADS1298_H_

#include <GPIO.h>

class ADS1298 {
	private:
		GPIO reset;
		GPIO pwdn;
		GPIO pinStart;
		GPIO diffSel;
	public:
		ADS1298();
		virtual ~ADS1298();
};

#endif /* SRC_ADS1298_H_ */
