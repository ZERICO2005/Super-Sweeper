/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/* Only include this if targetting Ti84CE/eZ80 */

#include <stdint.h>
void fillRect(uint24_t x1, uint24_t y1, uint24_t x2, uint8_t y2); // y2 < 256
//void fillText(uint24_t x1, uint24_t y1, uint24_t x2, uint8_t y2); // y2 < 256
void horiz(uint24_t x1, uint24_t y, uint24_t x2);
void vert(uint24_t x, uint24_t y1, uint24_t y2);
//void plot(uint24_t x, uint24_t y);
//void plotFast(uint8_t* z);
void fillMemory(uint8_t value, uint24_t base, uint24_t len);
//void addPointer(uint24_t x, uint24_t y);
//void fillScreen();