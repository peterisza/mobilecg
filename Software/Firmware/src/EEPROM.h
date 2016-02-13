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
