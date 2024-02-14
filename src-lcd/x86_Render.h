/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef X86_RENDER_H
#define X86_RENDER_H

void initLCDcontroller();
int terminateLCDcontroller();

uint32_t getMouseState(int32_t* posX, int32_t* posY);

bool resizeWindow(int32_t resX, int32_t resY, uint32_t* resizeX, uint32_t* resizeY);

void internal_kb_Reset();
void internal_kb_Scan();

void newFrame(); // Outputs the current vram

void blit16bpp(uint8_t* data);
void blit8bpp(uint8_t* data);
void blit4bpp(uint8_t* data);

void copyFrame(uint8_t* data);

extern uint8_t darkMode;
extern bool useMouseInGame;

void internal_SPI_Row_Major();

void internal_SPI_Column_Major();

#endif /* X86_RENDER_H */