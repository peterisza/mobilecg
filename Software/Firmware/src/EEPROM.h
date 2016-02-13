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
 
#ifndef SRC_WRAPPERS_EEPROM_H_
#define SRC_WRAPPERS_EEPROM_H_

#include <cstdint>

class EEPROM {
public:
	//The Variable enum and the variableSizes
	//Array must have the same length (except VAR_END)
	enum Variable {VAR_LINKKEY=0, VAR_LAST_LINK_KEY, VAR_END};

	static EEPROM &instance();
	virtual ~EEPROM();

	bool write(Variable eepromVar, int offset, void *data, int size);
	bool read(Variable eepromVar, int offset, void *data, int size);
private:
	EEPROM();

	static int variableSizes[];
	int calcOffset(Variable eepromVar);

	bool read(int address, char *data);
	bool write(int address, char *data);

	void checkSize(Variable eepromVar, int offset, int size);

	void setValid(Variable var, bool valid);
	bool isValid(Variable var);
};

#endif
