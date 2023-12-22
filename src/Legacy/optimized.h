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