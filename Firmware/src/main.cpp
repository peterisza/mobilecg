#include <OS.h>
#include <GPIO.h>
#include <Bluetooth.h>

GPIO led1('B', 6);
GPIO led2('B', 7);

Bluetooth bt("\x00\xB0\xC1\xFA\x52", "MobilECG");

void mainTaskCallback (OS::Task &task) {
	UNUSED(task);

	bt.init();

	while(1){
		led1.on();
		led2.off();

		OS::sleep(500);

		led1.off();
		led2.on();

		OS::sleep(500);
	}
}

TASK(mainTask,mainTaskCallback);


int main(){
	OS::run();
}
