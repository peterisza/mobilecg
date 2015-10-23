#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdint.h>

#include "logo.h"



void setPix(uint8_t *buf, int x, int y){
	int offset=y*width+x;
	buf[offset >> 3] |= 1<< (offset & 7);
}


int main(){
	uint8_t buf[width*height/8];
	
	memset(buf, 0, sizeof(buf));
	
	for (int x=0; x<width; x++){
		for (int y=0; y<height; y++){
			if (header_data[y*width+x])
				setPix(buf, x,y);
		}
	}
	
	printf("#include \"image.hpp\"\n\n");
	
	printf("static const uint8_t image[] = {");
	for (int a=0; a<sizeof(buf); a++){
		if (a % 16==0)
			printf("\n\t");
		
		printf("0x%.2X, ", buf[a]);
	}
	
	printf("\n};\n\n");
	printf("const Image imgObject(image, %d, %d);\n\n", width, height);
}