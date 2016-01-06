#include <OS.h>
#include <GPIO.h>
#include <Bluetooth.h>
#include <ADS1298.h>

GPIO led1('B', 6);
GPIO led2('B', 7);

GPIO en2v8('C', 1);
GPIO bluetoothShutdown('C', 13, true);

Bluetooth bluetooth("MobilECG");

extern "C" UART_HandleTypeDef huart2;

ADS1298 ad;

void mainTaskCallback (OS::Task &task) {
	UNUSED(task);

	OS::sleep(100);
	en2v8.on();
	OS::sleep(100);


	OS::sleep(100);
	bluetoothShutdown.off();
	OS::sleep(100);

	bluetooth.init();

	//Turn on ECG clock
	TIM_HandleTypeDef tim;
	tim.Instance = TIM1;
	HAL_TIM_PWM_Start(&tim, TIM_CHANNEL_3);


	ad.start();

	while(1){
		ad.start();
		/*led1.on();
		led2.off();

		for (int a=0; a<100; a++)
			bluetooth.send("pina");
		bluetooth.send("\r\n");
		OS::sleep(500);

		led1.off();
		led2.on();

		for (int a=0; a<100; a++)
			bluetooth.send("fasz");
		bluetooth.send("\r\n");
		OS::sleep(500);*/
	}
}

TASK(mainTask,mainTaskCallback,4096);


int main(){
	bluetoothShutdown.on();
	en2v8.off();

	OS::run();
}
