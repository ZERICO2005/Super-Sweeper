/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

//#ifndef COL_H
#ifdef COL_H //Lol
#define COL_H

#include <prime2D.h>
#include <stdint.h>
#include <prime2D.h>

/*
Took me long enough to make this .h file
Previously, I would use my knuckles to find the color I needed,
my first knuckle was color 1 or Red, then 2 Yellow, 3 Green, 4 Teal
5 Blue, 6 Magenta, and 7 White. Adding 8 to the number to set the Alpha Bit
*/

enum COLORS {
    Black,Red,Yellow,Lime,Teal,Blue,Magenta,White,
    Grey,Maroon,Brown,Green,Cyan,Navy,Purple,Silver
};

#ifdef DEVBUILD

// If I am ever to lazy to find a color, should be fixed by release
/*
uint8_t findColor1555(uint16_t c);
uint8_t findColor888(uint8_t r, uint8_t g, uint8_t b);
uint8_t findColor565(uint16_t c);

uint8_t findColor1555(uint16_t c) {
    uint8_t r = (c & 0x7C00) >> 10;
    uint8_t g = (c & 0x03E0) >> 4;
    g += (c & 0x8000) ? 1 : 0;
    uint8_t b = (c & 0x001F);

    u8 best = 0x00;
    u16 low = 0xFFFF;
    for (u8 i = 0; i < 0xF0; i++) { //Avoids temp color zone
        u16 col = paletteRAM[i];
        uint8_t r0 = (col & 0x7C00) >> 10;
        uint8_t g0 = (col & 0x03E0) >> 4;
        g0 += (c & 0x8000) ? 1 : 0;
        uint8_t b0 = (col & 0x001F);
        u16 dif = (r - r0) * (r - r0) + (g - g0) * (g - g0) + (b - b0) * (b - b0);
        if (dif < low) {
            low = dif;
            best = i;
        }
    }
    return best;
}
uint8_t findColor888(uint8_t r, uint8_t g, uint8_t b) {
    u8 i = (g & 0x04) >> 2;
    r >>= 3;
    g >>= 2;
    b >>= 3;
    return findColor1555((i << 15) + (r << 10) + (g << 5) + b);
}
uint8_t findColor565(uint16_t c) {
    uint8_t r = (c & 0xF800) >> 11;
    uint8_t g = (c & 0x07C0) >> 6;
    uint8_t b = (c & 0x001F);
    uint8_t i = (c & 0x0020) >> 5;
    return findColor1555((i << 15) + (r << 10) + (g << 5) + b);
}
*/
//WHAT? WHY IT NO WORKY!?!?!?!?!?!? :(

#endif

#endif /* COL_H */
