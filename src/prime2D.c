/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "prime2D.h"
#include "prime2D_Font6x8.h"

uint8_t gColor = 0; //Graphics color

const uint16_t char3x5[28] = {
	0x7B6F, 0x749A, 0x73E7, 0x79A7, 0x49ED, 0x79CF, 0x7BCF, 0x24A7, 0x2AAA, 0x79EF, 0x5BEF, 0x7AEF, 0x624E, 0x3B6B, 0x72CF, 0x12CF, 0x5AAD, 0,0,0,0,0,0,0,0, 0x55D5, 0x7480, 0x21A7
};
const uint16_t char5x5[56] = {
	22335,1011, 4292,452, 32287,993, 29215,1008, 31909,132, 31807,1008, 31807,1009, 28959,264, 14894,465, 32319,1008, 22205,949, 19314,594, 30269,933, 26173,945, 30389,561, 29885,945, 29885,949,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	32213,686, 4228,996, 8750,128
};

// const uint8_t char6x8[768]; // See prime2D_Font6x8.h

/* Debugging */

	const uint16_t num3x5[16] = {
		0x7B6F, 0x749A, 0x73E7, 0x79A7, 0x49ED, 0x79CF, 0x7BCF, 0x24A7, 0x7AAF, 0x79EF,
		0x5BEF, 0x7BC9, 0x724F, 0x7BE4, 0x72CF, 0x12CF
	}; //Used for the printInt functions

	// Integer to print, length, base 2-16 //Auto adjusts for signage
	void printInt(int24_t in, uint8_t len, uint8_t base, uint24_t xC, uint24_t yC) {
		uint8_t* off = lcd_Ram8 + xC + (320 * yC);
		uint8_t* v = off + 320;
		len <<= 2; //len * 4
		const uint24_t x2 = 5 + len;
		const uint24_t jump = 317 - x2;
		for (uint8_t dY = 1; dY < 6; dY++) {
			for (uint24_t dX = 0; dX < x2; dX += 4) {
				*v = 0;
				v += 4;
			}
			v += jump;
		}
		v = off;
		for (uint24_t dX = 0; dX < x2; dX++) {
			*v = 0;
			v++;
		}
		v = off + 1920; // 320 * 6
		for (uint24_t dX = 0; dX < x2; dX++) {
			*v = 0;
			v++;
		}

		uint24_t* negSign = 961 + (uint24_t*)off; //Fills three pixels //1 + (3 * 320)
		*negSign = in < 0 ? 460551 : 0; //If Negative
		uint24_t j = abs(in);
		uint24_t pow = 1;
		for (uint24_t k = 0; k < len; k += 4) {
			uint16_t bitImage = num3x5[(j / pow) % base];
			uint8_t *fill = off + 321 + len - k;
			for (uint8_t y = 0; y < 5; y++) {
				for (uint8_t x = 0; x < 3; x++) {
					*fill = bitImage & 1 ? 7 : 0; //White if true
					bitImage >>= 1;
					fill++;
				}
				fill += 317; //320 - 3
			}
			pow *= base;
		}
	}

	// Integer to print, length, base 2-16
	void printUInt(int24_t in, uint8_t len, uint8_t base, uint24_t xC, uint24_t yC) {
		uint8_t* off = lcd_Ram8 + xC + (320 * yC); //Something about casting off to uint8_t* adds 4 more bytes
		uint8_t* v = off + 320;
		len <<= 2; //len * 4
		const uint24_t x2 = 1 + len; //Can optomize out "1 + " for a saving of 8 bytes
		const uint24_t jump = 317 - x2;
		for (uint8_t dY = 1; dY < 6; dY++) {
			for (uint24_t dX = 0; dX < x2; dX += 4) {
				*v = 0;
				v += 4;
			}
			v += jump;
		}
		v = off;
		for (uint24_t dX = 0; dX < x2; dX++) {
			*v = 0;
			v++;
		}
		v = off + 1920; // 320 * 6
		for (uint24_t dX = 0; dX < x2; dX++) {
			*v = 0;
			v++;
		}
		uint24_t pow = 1;
		for (uint24_t k = 0; k < len; k += 4) {
			uint16_t bitImage = num3x5[(in / pow) % base];
			uint8_t* fill = off + 317 + len - k;
			for (uint8_t y = 0; y < 5; y++) {
				for (uint8_t x = 0; x < 3; x++) {
					*fill = bitImage & 1 ? 7 : 0; //White if true
					bitImage >>= 1;
					fill++;
				}
				fill += 317; //320 - 3
			}
			pow *= base;
		}
	}

//Primatives
void fillRect(uint24_t x1, uint24_t y1, uint24_t x2, uint24_t y2) { //x start, y start, x length, y length
    uint8_t* v = lcd_Ram8 + x1 + (y1 * 320);
    const uint24_t jump = 320 - x2;
    for (uint24_t dY = 0; dY < y2; dY++) {
        for (uint24_t dX = 0; dX < x2; dX++) {
            *v = gColor;
            v++;
        }
        v += jump;
    }
}
void horiz(uint24_t x1, uint24_t y, uint24_t x2) { //x start, y postion, x length
    uint8_t* z = lcd_Ram8 + (x1 + x2) + (y * 320);
    for (uint8_t* fill = lcd_Ram8 + x1 + (y * 320); fill < z; fill++) {
        *fill = gColor;
    }
}
void vert(uint24_t x, uint24_t y1, uint24_t y2) { //x postion, y start, y length
    uint8_t* z = lcd_Ram8 + x + ((y2 + y1) * 320);
    for (uint8_t* fill = lcd_Ram8 + (y1 * 320) + x; fill < z; fill += 320) {
        *fill = gColor;
    }
}

void fillScreen() { //Fills buffer 0
	memset(lcd_Ram8,gColor,320 * 240 * 1);
}

//Text Engine
void text6x8(uint24_t xW, uint24_t yW, uint8_t lexicon) { //x position, y position, letter index
    uint8_t* bitImage = (uint8_t*)char6x8 + (lexicon * 6);
    uint8_t* fill = lcd_Ram8 + (yW * 320 + xW);
    uint8_t b = 1;
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 6; x++) {
            *fill = *bitImage & b ? gColor : *fill;
            bitImage++;
            fill++;
        }
        bitImage -= 6;
        fill += 314; // 320 - 6
        b <<= 1;
    }
}

void fillText(uint24_t x1, uint24_t y1, uint24_t x2, uint24_t y2) { //x start, y start, x length, y length //fillRect() that does not overwrite text
    uint8_t* v = lcd_Ram8 + x1 + (y1 * 320);
    const uint24_t jump = 320 - x2;
    for (uint24_t dY = 0; dY < y2; dY++) {
        for (uint24_t dX = 0; dX < x2; dX++) {
            *v = *v ? gColor : 0;
            v++;
        }
        v += jump;
    }
}