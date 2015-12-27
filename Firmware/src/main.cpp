#include <OS.h>
#include <GPIO.h>
#include <Bluetooth.h>

GPIO led1('B', 6);
GPIO led2('B', 7);

Bluetooth bluetooth("MobilECG");

extern "C" UART_HandleTypeDef huart2;

void mainTaskCallback (OS::Task &task) {
	UNUSED(task);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	OS::sleep(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	OS::sleep(100);

//	while(1);

	/*while(1){
		HAL_UART_DMAStop(&huart2);
		HAL_UART_Transmit_DMA(&huart2, (uint8_t*)"PINA", 4);
		OS::sleep(100);
	}*/

	bluetooth.init();

	while(1){
		led1.on();
		led2.off();

		for (int a=0; a<5; a++)
			bluetooth.send("pina");
		bluetooth.send("\r\n");
		OS::sleep(500);

		led1.off();
		led2.on();

		for (int a=0; a<5; a++)
			bluetooth.send("fasz");
		bluetooth.send("\r\n");
		OS::sleep(500);
	}
}

TASK(mainTask,mainTaskCallback,2048);


int main(){
	OS::run();


}
