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