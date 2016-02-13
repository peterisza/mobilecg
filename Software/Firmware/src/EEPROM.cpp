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
 
#include "EEPROM.h"
#include "Logger.h"
#include <cstring>

extern "C"{
	#include "libeeprom.h"
	extern int __eeprom_start;
	uint16_t VirtAddVarTab[NB_OF_VAR];
}

int EEPROM::variableSizes[]={
		22*5, //Link key storage size
		1
};

class FlashUnlocker{
	public:
		FlashUnlocker(){
			HAL_FLASH_Unlock();
		}

		virtual ~FlashUnlocker(){
			HAL_FLASH_Lock();
		}
};

EEPROM &EEPROM::instance(){
	static EEPROM eeprom;
	return eeprom;
}

EEPROM::EEPROM() {
	//Check if linker places EEPROM area to the same
	//address where the EEPROM lib excepts it.
	if  (&__eeprom_start != (int*)EEPROM_START_ADDRESS){
		Logger::panic("EEPROM address misaligned.");
	}

	FlashUnlocker unlocker;

	EE_Init();
}

void EEPROM::setValid(EEPROM::Variable var, bool valid){
	int offset = calcOffset(var);
	EE_WriteVariable(offset, valid ? 1 : 0);
}

bool EEPROM::read(int address, char *data){
	uint16_t tmp16;
	if (EE_ReadVariable(address, &tmp16)){
		return false;
	}

	data[0] = tmp16 & 0xFF;
	data[1] = tmp16 >> 8;

	return true;
}

bool EEPROM::write(int address, char *data){
	uint16_t tmp16;
	char *tmp=(char*)&tmp16;
	tmp[0]=data[0];
	tmp[1]=data[1];

	return !EE_WriteVariable(address, tmp16);
}

bool EEPROM::write(EEPROM::Variable eepromVar, int offset, void *vdata, int size){
	FlashUnlocker unlocker;

	char *data=(char*)vdata;
	checkSize(eepromVar, offset, size);

	int varOffset = calcOffset(eepromVar)+1+offset/2;

	setValid(eepromVar, false);

	if (offset & 1){
		char tmp[2];
		if (!read(varOffset, tmp)){
			tmp[0]=0;
		}
		tmp[1]=*data;

		if (!write(varOffset, tmp)){
			return false;
		}

		varOffset++;
		data++;
		size--;
	}

	while (size>=2){
		if (!write(varOffset, data)){
			return false;
		}

		varOffset++;
		data+=2;
		size-=2;
	}

	if (size){
		char tmp[2];
		if (!read(varOffset, tmp)){
			tmp[1]=0;
		}
		tmp[0]=*data;

		if (!write(varOffset, tmp)){
			return false;
		}
	}

	setValid(eepromVar, true);
	return true;
}

bool EEPROM::read(EEPROM::Variable eepromVar, int offset, void *vdata, int size){
	char *data=(char*)vdata;
	checkSize(eepromVar, offset, size);

	int varOffset = calcOffset(eepromVar)+1+offset/2;

	if (!isValid(eepromVar)){
		return false;
	}

	if (offset & 1){
		char tmp[2];
		if (!read(varOffset, tmp)){
			return false;
		}
		*data=tmp[1];

		varOffset++;
		data++;
		size--;
	}

	while (size>=2){
		if (!read(varOffset, data)){
			return false;
		}

		varOffset++;
		data+=2;
		size-=2;
	}

	if (size){
		char tmp[2];
		if (!read(varOffset, tmp)){
			return false;
		}
		*data=tmp[0];
	}

	return true;
}

bool EEPROM::isValid(EEPROM::Variable var){
	uint16_t valid;
	int offset = calcOffset(var);
	if (EE_ReadVariable(offset, &valid))
		return false;

	return valid ? true : false;
}

EEPROM::~EEPROM() {

}

int EEPROM::calcOffset(Variable eepromVar){
	int offset=0;
	for (int a=0; a!=(int)eepromVar; a++){
		offset+=(variableSizes[a]+1)/2+1;
	}

	return offset;
}

void EEPROM::checkSize(Variable eepromVar, int offset, int size){
	if ((offset+size) > variableSizes[eepromVar]){
		Logger::panic("EEPROM access out of bounds.");
	}
}
