/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
		if (!Bluetooth::instance().isConnected()){
			ADS1298::instance().clear();
			OS::sleep(10);
			continue;
		}

		if (ADS1298::instance().getAvailableData()<512){
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

extern "C" void vApplicationIdleHook( void ){
	asm("wfi");
}
