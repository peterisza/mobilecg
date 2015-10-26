#include "printf.hpp"
#include <algorithm>
#include <string.h>
#include <stdarg.h>
#include "globals.hpp"

static char toChar(int val){
	if (val<10)
		return '0'+val;
	else
		return 'A'+val-10;
}

static int toString(char *dest, int maxlen, int value, int radix, int minLen, bool spacePad){
	if (maxlen==0)
		return 0;
	
	bool negative=false;
	if (value<0){
		value=-value;
		negative=true;
	}
	
	int len=1;
	uint32_t startDiv=1;
	for (uint32_t lenCnt=value/radix; lenCnt; lenCnt/=radix){
		len++;
		startDiv*=radix;
	}
			
	int realLen=std::min(std::max(minLen, len), maxlen);
			
	int pos=0;
	if (negative && spacePad==false){
		dest[pos++] = '-';
	}
	
	for (int a=0; a < realLen-len; a++)
		dest[pos++] = spacePad ? ' ' : '0';
	
			
	if (negative && spacePad==true){
		dest[pos++] = '-';
	}
		
	for (int a=0; a<len; a++){
		dest[pos++] = toChar(value / startDiv);
		value %= startDiv;
		startDiv /= radix;
	}
	
	return pos;
}

enum FormatType {FT_STRING, FT_INT, FT_HEX};

static int parseFormat(const char *formatString, FormatType &type, int &precision){
	precision=0;
	
	
	if (formatString[0]==0)
		return false;
	
	int pos=0;
	if (formatString[pos]=='.'){
		for (pos++; formatString[pos]>='0' && formatString[pos]<='9'; pos++){
			precision = precision*10 + formatString[pos] - '0';
		}
	}
	
	switch (formatString[pos]){
		case ('d'):
			type = FT_INT;
			break;
		case ('s'):
			type = FT_STRING;
			break;
		case ('X'):
		case ('x'):
			type = FT_HEX;
			break;
		default:
			return 0;
			break;
	}
	
	pos++;
	
	return pos;
}

int vsnprintf(char *dest, int maxlen, const char *format, va_list vl){
	int destpos=0;

	maxlen--;
	
	for (int formatpos=0; format[formatpos];){
		//stop if no more space in destination
		if (destpos>=maxlen)
			break;
		
		//Ordinary character
		if (format[formatpos]!='%'){
			dest[destpos++]=format[formatpos++];
			continue;
		}
		
		//handle %%
		formatpos++;
		if (format[formatpos]=='%'){
			dest[destpos++]='%';
			formatpos++;
			continue;
		}
		
		//handle format string
		FormatType type;
		int precision;
		
		int formatLen=parseFormat(&format[formatpos], type, precision);
		if (formatLen==0){
			//Invalid format
			dest[destpos++]='%';
			formatpos++;
			continue;
		}		
		
		formatpos+=formatLen;
		
		switch (type){
			case (FT_INT):
				destpos+=toString(&dest[destpos], maxlen-destpos,  va_arg(vl, int), 10, precision, true);
				break;
			case (FT_HEX):
				destpos+=toString(&dest[destpos], maxlen-destpos,  va_arg(vl, int), 16, precision, false);
				break;
			case (FT_STRING):{
					char *str = va_arg(vl, char*);
					int len=std::min(std::max(precision, (int)strlen(str)), maxlen-destpos);
					memcpy(&dest[destpos], str, len);
					destpos+=len;
				}
				break;
		}		
	}
	
	dest[destpos]=0;
	return destpos+1;
}


void printf(const char *format, ...){
	char buffer[64];
	
	va_list vl;
	va_start(vl, format);
	vsnprintf(buffer, sizeof(buffer), format, vl);
	va_end(vl);
	
	Globals::instance().uart.send(buffer);
}