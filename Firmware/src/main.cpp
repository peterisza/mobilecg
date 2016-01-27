#include <OS.h>
#include <GPIO.h>
#include <Bluetooth.h>
#include <ADS1298.h>
#include <Logger.h>
#include <Packetizer.h>
#include <ECGSender.h>

GPIO led1('B', 6);
GPIO led2('B', 7);

GPIO en2v8('C', 1);
GPIO bluetoothShutdown('C', 13, true);

extern "C" UART_HandleTypeDef huart2;

Packetizer dataPacketizer;
ECGSender ecgSender(dataPacketizer);

void mainTaskCallback (OS::Task &task) {
	UNUSED(task);

	OS::sleep(100);
	en2v8.on();
	OS::sleep(100);


	OS::sleep(100);
	bluetoothShutdown.off();
	OS::sleep(100);

	Bluetooth::instance().init("MobilECG");

	//Turn on ECG clock
	TIM_HandleTypeDef tim;
	tim.Instance = TIM1;
	HAL_TIM_PWM_Start(&tim, TIM_CHANNEL_3);


	if (!ADS1298::instance().start())
		Logger::panic("Failed to initialize ADS1298.");

	while(1){
		ADS1298::EcgBuffer& buffer = ADS1298::instance().getBuffer();
		if (!Bluetooth::instance().isConnected()){
			buffer.clear();
			OS::sleep(10);
			continue;
		}

		if (buffer.used()<0xFF){
			OS::sleep(10);
			continue;
		}

		ecgSender.send();
	}
}

TASK(mainTask,mainTaskCallback,4096);

void ledTaskCallback (OS::Task &task) {
	UNUSED(task);

	while(1){
		led1.on();
		led2.off();

		OS::sleep(500);

		led1.off();
		led2.on();

		OS::sleep(500);
	}
}

TASK(ledTask, ledTaskCallback,128);


int main(){
	bluetoothShutdown.on();
	en2v8.off();

	OS::run();
}
