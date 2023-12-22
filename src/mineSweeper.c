/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"

#include "mineSweeper.h"
#include "prime2D.h"
#include "primeKey.h"
#include "global.h"
#include "gameMenu.h"

#include "dataManager.h"

//#include <col.h>

#define borderIndexes 2
//Graphic numbers
#define gMine 25
#define gFlag 26
#define gQuestion 27

#define currentTime (systemTime - gameStartTime - gamePauseTime)

void gameControl(); //Temporary 2023 May 23rd

uint8_t alphaBind() {
    if (swapAlphaSecondBind == 0) {
        if ((kb_Data[2] & kb_Alpha)) {
            return 1;
        }
    } else {
        if ((kb_Data[1] & kb_2nd)) {
            return 1;
        }
    }
    return 0;
}
uint8_t secondBind() {
    if (swapAlphaSecondBind == 0) {
        if ((kb_Data[1] & kb_2nd)) {
            return 1;
        }
    } else {
        if ((kb_Data[2] & kb_Alpha)) {
            return 1;
        }
    }
    return 0;
}

struct dataSeg7 timeLCD;
struct dataSeg7 scoreLCD;
struct dataSeg7 flagLCD;

const uint8_t seg7[18] = {
	0b1011111,0b0000011,0b1110110,0b1110011,0b0101011,0b1111001,0b1111101,0b1000011,0b1111111,0b1111011,0b1101111,0b0111101,0b1011100,0b0110111,0b1111100,0b1101100,0b0000000,0b0100000
};
//Characters: HEX,_,-
void displaySeg7(uint24_t i, uint8_t b, struct dataSeg7* lcd) { //Number, Digits, X-2, Y-2
    //Colors: 24/25/26/27
    uint24_t x = lcd->x;
    uint24_t y = lcd->y;
    uint8_t d = lcd->digits;
    uint8_t hi = lcd->onC;
    uint8_t lo = lcd->offC;
    
    uint24_t pow = 1;
    uint24_t z = y * LCD_RESX; //Constant offset
    x += (d - 1) * 9;
    for (uint8_t n = 0; n < d; n++) { //Since d was decremented
        uint8_t j = seg7[(i / pow) % b];
        gColor = (j & 64) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (0 * LCD_RESX + 1)]) { // Checks for change in color
            horiz(x+1,y,6);
            horiz(x+2,y+1,4);
        }
        gColor = (j & 32) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (6 * LCD_RESX + 2)]) {
            horiz(x+2,y+6,4);
            horiz(x+1,y+7,6);
            horiz(x+2,y+8,4);
        }
        gColor = (j & 16) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (13 * LCD_RESX + 2)]) {
            horiz(x+2,y+13,4);
            horiz(x+1,y+14,6);
        }
        gColor = (j & 8) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (1 * LCD_RESX + 0)]) {
            vert(x,y+1,6);
            vert(x+1,y+2,4);
        }
        gColor = (j & 4) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (8 * LCD_RESX + 0)]) {
            vert(x,y+8,6);
            vert(x+1,y+9,4);
        }
        x += 6;
        gColor = (j & 2) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (2 * LCD_RESX + 0)]) {
            vert(x,y+2,4);
            vert(x+1,y+1,6);
        }
        gColor = (j & 1) ? hi : lo;
        if (gColor != lcd_Ram8[z + x + (9 * LCD_RESX + 0)]) {
            vert(x,y+9,4);
            vert(x+1,y+8,6);
        }
        x -= 15;
        pow *= b; //base
    }
}

void buildSeg7(uint24_t input, uint8_t base, struct dataSeg7* lcd, uint8_t digits, uint24_t x, uint24_t y,
uint8_t bgC, uint8_t borC, uint8_t offC, uint8_t onC) { //Number, Digits, Base, x, y, ptr, Colors: backGround, border, off, on
    gColor = borC; //27
    uint24_t u = digits * 9 + 2;
    horiz(x,y,u);
    horiz(x,y+18,u+1);
    vert(x,y,18);
    vert(x+u,y,18);
    gColor = bgC; //26
    fillRect(x+1,y+1,u-1,17);
    lcd->digits = digits;
    lcd->x = x + 2; //Offset of where the number graphic is
    lcd->y = y + 2;
    lcd->offC = (accessMode == 1) ? 0x00 : offC;
    lcd->onC = onC;
    displaySeg7(input,base,lcd);
}

void quake() {
	newFrame();
    if (accessMode == 0) { //Remove this
        delay32K(32768/15); //Waits 32768Hz / FPS
        uint24_t shake;
        int8_t amount = mineCount / 3;
        if (amount < 12) {
            amount = 12;
        }
        if (amount > 90 || mineCount > 255) {
            amount = 90;
        }
		srand(timer_Get(1));
        for (uint8_t i = 0; i < amount; i++) {
            shake = 0xD40000 - ((LCD_RESX * 8) * 3) - (8 * 3);
            shake += 8 * (rand() % 7);
            shake += (LCD_RESX * 8) * (rand() % 7);
            lcd_UpBase = shake;
			newFrame();
            delay32K(32768/20);
        }
        lcd_UpBase = 0xD40000;
		newFrame();
        delay32K(32768/2);
    } else {
        delay32K(24576); // 0.75 seconds
    }
}

void expression(unsigned char e) { //Updates the smiley face
	if (e < 4) { //0-3
		gColor = 2;
		fillRect(156, 12, 7, 3); //y2 = 3 because of chordCheck
		gColor = 0;
		if (e == eHAPPY) { //Happy
			horiz(157, 13, 5);
            plot(156, 12);
            plot(162, 12);
			return;
		}
		if (e == eSAD) { //Sad
			horiz(157, 12, 5);
			plot(156, 13);
			plot(162, 13);
			return;
		}
		if (e == eNULL) { //Null
			horiz(156, 13, 7);
			return;
		}
		if (e == eCHORD) { //Chord
			gColor = 2;
			fillRect(156,12,7,2);
			gColor = 0;
			fillRect(158,12,3,3);
			return;
		}
	} else if (e < 8) { //4-7
		// gColor = 10; // This is what was causing the odd dark yellow dot
		// plot(143,4); //Clears potential sunglasses
		gColor = 2;
		fillRect(156, 5, 7, 4);
		gColor = 0;
		if (e == eNORMAL) { //Normal
			vert(157, 7, 2);
			vert(161, 7, 2);
			return;
		}
		if (e == eSHADES) { //Sunglasses
			fillRect(156, 7, 7, 2);
			gColor = 2;
			plot(159, 8);
			gColor = 0;
			plot(162, 6);
			plot(163, 5);
			plot(156, 6);
			plot(157, 5);
			return;
		}
		if (e == eXX) { //XX
			plot(156,6);
			plot(156,8);
			plot(157,7);
			plot(158,6);
			plot(158,8);
			
			plot(160,6);
			plot(160,8);
			plot(161,7);
			plot(162,6);
			plot(162,8);
			return;
		}
		if (e == eSLEEP) { //Sleep
			horiz(156, 8, 2);
			horiz(161, 8, 2);
			return;
		}
	}
}

void flash() { //uint8_t x
    for (uint8_t j = 0; j <= 32; j++) {
        uint32_t flashTime = timer_Get(1);
        uint8_t i = 0;
        for (uint16_t *f = lcd_Palette; f < lcd_Palette + 0x100; f++) {
			#define flashLinear(y0,x) ((((y0) * (32 - (x))) + (31 * (x))) >> 5)
            *f = (
				(flashLinear((initialPalette[i] >> 10) & 31,j) << 10) +
				(flashLinear((initialPalette[i] >> 5) & 31,j) << 5) +
				flashLinear(initialPalette[i] & 31,j)
			);
            i++;
			#undef flashLinear
        }
		newFrame();
        while (deltaTime(timer_Get(1),flashTime) < 1472);
    }
}

void flagDraw(uint8_t symbol, uint24_t xP, uint24_t yP) {
    gColor = accessMode ? 0 : color[symbol];
    symbol <<= 1;
    uint16_t bitImage0 = char5x5[symbol];
    uint16_t bitImage1 = char5x5[symbol + 1];
    uint8_t* z = lcd_Ram8 + (yP * LCD_RESX + xP);
    for (uint8_t y = 0; y < 5; y++) {
        for (uint8_t x = 0; x < 5; x++) {
            if (bitImage0 & 1) {
                *z = gColor;
            }
            z += (LCD_RESX * 3);
            if (bitImage1 & 1) {
                *z = gColor;
            }
            bitImage0 >>= 1;
            bitImage1 >>= 1;
            z -= (LCD_RESX * 3) - 1;
        }
        z += (LCD_RESX - 5);
    }
}

/* 
// Legacy Flag Counter Code
void flagCount() {
    gColor = 15;
    for (int24_t z = 15; z <= 35; z += 10) { //Flag Counter
            fillRect(z, 5, 7, 7);
    }
    gColor = 0;
    if (flags >= 100) {
        flagDraw(flags / 100 % 10,17,7);
    } else if (flags <= -10){
        gColor = 0;
        horiz(17, 9, 5);
    }
    if (flags >= 10 || flags <= -10) {
        flagDraw(abs(flags) / 10 % 10,27,7);
    } else if (flags < 0 && flags >= -9) {
        gColor = 0;
        horiz(27, 9, 5);
    }
    flagDraw(abs(flags) % 10,37,7);
}
*/

//uint8_t lcdColor[20] = {0x60}; //0x70
//        flagLCD.onC = color[((plags / 100) % 10)] & 7;
//        flagLCD.offC = color[((plags / 100) % 10)] | 8;

// Slow, but its the only way to do signed flag counts for now
void flagCount() { //Add a color number mode for nostalga
    uint16_t plags = abs(flags);
    flagLCD.x = 11;
    if (flags >= 100) {
        displaySeg7((plags / 100) % 10, 10, &flagLCD);
    } else if (flags <= -10){
        displaySeg7(17, 18, &flagLCD);
    } else {
        displaySeg7(16, 17, &flagLCD);
    }
    flagLCD.x = 20;
    if (flags >= 10 || flags <= -10) {
        displaySeg7((plags / 10) % 10, 10, &flagLCD);
    } else if (flags < 0 && flags >= -9) {
        displaySeg7(17, 18, &flagLCD);
    } else {
        displaySeg7(16, 17, &flagLCD);
    }
    flagLCD.x = 29;
    displaySeg7(plags % 10, 10, &flagLCD);
}

void glyph(int16_t space, uint8_t symbol) {
    gColor = color[symbol];
    if (symbol == gFlag) {
        if (~fontSize & 1 || fontSize == 0) { //0,1,3,5
            gColor = 22; //Changes flag pole color to be more readable
        }
    }
    if (font == 2) { //6x8 Font
        uint8_t* bitImage = (uint8_t*)char6x8 + (symbol * 6);
        uint8_t* z = lcd_Ram8 + ((space / marX * disY + posY + padY) * LCD_RESX + (space % marX * disX + posX + padX));
        uint8_t b = 1;
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 6; x++) {
                *z = *bitImage & b ? gColor : *z;
                bitImage++;
                z++;
            }
            bitImage -= 6;
            z += (LCD_RESX - 6);
            b <<= 1;
        }
        
        if (symbol == gFlag) {
            gColor = flagColor;
            fillRect(space % marX * disX + posX + padX, space / marX * disY + posY + padY + 1, 3, 3);
        } else if (symbol == gMine) {
            //gColor = 7;
            z -= (LCD_RESX * 6) - 2;
            *z = 7; // 2,2 // White
            z += (LCD_RESX - 1);
            *z = 7; // 1,3 // White
        }
        return;
    } else if (font == 1) { //5x5 Font
        symbol <<= 1;
        uint16_t bitImage0 = char5x5[symbol];
        uint16_t bitImage1 = char5x5[symbol + 1];
        // uint24_t z1 = z0 + 960;
        uint8_t* z = lcd_Ram8 + ((space / marX * disY + posY + padY) * LCD_RESX + (space % marX * disX + posX + padX));
        for (uint8_t y = 0; y < 5; y++) {
            for (uint8_t x = 0; x < 5; x++) {
                if (bitImage0 & 1) {
                    *z = gColor;
                }
                z += (LCD_RESX * 3);
                if (bitImage1 & 1) {
                    *z = gColor;
                }
                bitImage0 >>= 1;
                bitImage1 >>= 1;
                z -= (LCD_RESX * 3) - 1;
            }
            z += LCD_RESX - 5;
        }
        if (symbol == 2 * gFlag) {
            gColor = flagColor;
            fillRect(space % marX * disX + posX + padX, space / marX * disY + posY + padY, 2, 2);
        } else if (symbol == 2 * gMine) {
            //gColor = 7;
            z -= (LCD_RESX * 4) - 1;
            *z = 7; // 1,1 // White
        }
        return;
    }
    //3x5 Font
    uint16_t bitImage = char3x5[symbol];
    uint8_t* z = lcd_Ram8 + ((space / marX * disY + posY + padY) * LCD_RESX + (space % marX * disX + posX + padX));
    for (uint8_t y = 0; y < 5; y++) {
        for (uint8_t x = 0; x < 3; x++) {
            if (bitImage & 1) {
                *z = gColor;
            }
            bitImage >>= 1;
            z++;
        }
        z += (LCD_RESX - 3);
    }
    if (symbol == gFlag) {
        gColor = flagColor;
        fillRect(space % marX * disX + posX + padX, space / marX * disY + posY + padY, 2, 2);
    }
    return;
}

void fillTile(int16_t space, int8_t mode) {
	gColor = 15; //grey
	if (state[space] == 0) {
		
		if (mode == tSELECT) { gColor = 16; }
		fillRect(space % marX * disX + 1 + posX, space / marX * disY + 1 + posY, disX - 3, disY - 3);
		if (flag[space] == 1) {glyph(space, gFlag);} else if (flag[space] == 2) {glyph(space, gQuestion);}
		
	} else {
		
		if (board[space] == gMine) {
            autoLoss = 1;
			gColor = mode == tCLEAR ? 0x17 : 0x01; //Dark red if mine is not highlighted, Bright red if mine is highlighted
		} else {
            gColor = mode == tSELECT ? 0x10 : 0x0F;
        }
		fillRect(space % marX * disX + posX, space / marX * disY + posY, disX - 1, disY - 1);
		//fillRect(tile % marX * disX + posX, tile / marX * disY + posY, disX - 1, disY - 1);
		if (board[space] > 0) { glyph(space, board[space]); }
		
	}
}

uint24_t item = 0; //U16
uint24_t max = 0; //U16
void floodFill() {
    search[item] = tile;
    max++;
    do {
        uint24_t target = search[item];
        int24_t u;
        int24_t v;
        for (uint8_t i = 0; i < offLen; i += 2) {
            u = order[offPos + i];
            v = order[offPos + i + 1];
            const uint24_t square = target + (v * marX) + u;
			
            if (board[square] != 255 && state[square] != sCLEARED) { //If tile is not out of bounds and not cleared yet
                state[square] = sCLEARED;
                cleared++;
                score += 12;
                if (board[square] == 0) {
                    search[max] = square;
                    max++;
                }
                fillTile(square, 0);
                if (flag[square] == fFLAG) {
                    flags++;
                    score -= 10;
                    flag[square] = fBLANK;
                }
            }
        }
        item++;
    } while (search[item] != 0);
}

/*
// Attempt at making it faster
bool mineCheck(int24_t tileM) {
    if (tileM == tile) {
        return true;
    }
    if (safeGuess == 2) {
        int8_t* u = order + offPos;
        int8_t* v = order + offPos + 1;
        for (uint8_t i = 0; i < offLen; i += 2) {
            u += 2;
            v += 2;
            if ((tile + (*v * marX) + *u) == tileM) {
                return true;
            }
        }
        u = order;
        v = order + 1;
        if (gameMode == 3 || gameMode == 9) {
            for (uint8_t i = 0; i < 8; i++) {
                u += 2;
                v += 2;
                if ((tile + (*v * marX) + *u) == tileM) {
                    return true;
                }
            }
        }
        
    }
    return false;
}
*/


// Legacy
bool mineCheck(int24_t tileM) {
    if (tileM == tile) {
        return true;
    }
    if (safeGuess != 0) {
        int24_t u;
        int24_t v;
        for (uint8_t i = 0; i < offLen; i += 2) {
            u = order[offPos + i]; //Probably more memory effeicent than an algorithm
            v = order[offPos + i + 1];
            if ((tile + (v * marX) + u) == tileM) {
                return true;
            }
        }
        if ((gameMode == 3 || gameMode == 9) && safeGuess == 2) {
            for (uint8_t i = 0; i < 8; i++) {
                u = order[i]; //Probably more memory effeicent than an algorithm
                v = order[i + 1];
                if ((tile + (v * marX) + u) == tileM) {
                    return true;
                }
            }
        }
    }
    return false;
}

uint32_t currentGameSeed = 0;

void mineGenerate() {
	currentGameSeed = seed;
    srand(currentGameSeed);
    uint24_t z;
    for (uint24_t i = 0; i < mineCount; i++) {
        do {
            z = (((rand() % sizeY) + borderIndexes) * marX) + (rand() % sizeX) + borderIndexes;
        } while (board[z] == gMine || mineCheck(z));
        board[z] = gMine;
    }

    for (uint8_t y = borderIndexes; y < marY - borderIndexes; y++) {
        for (uint8_t x = borderIndexes; x < marX - borderIndexes; x++) {
            if (board[y * marX + x] != gMine) {
                uint8_t count = 0;
                int24_t u;
                int24_t v;
                for (uint8_t i = 0; i < offLen; i += 2) {
                    u = order[offPos + i];
                    v = order[offPos + i + 1];
                    if (board[(y + v) * marX + (x + u)] == gMine) {
                        count++;
                    }
                }
                board[y * marX + x] = count;
            }
        }
    }
}


/*
// Attempt at making it constant time O(1)
void mineGenerate() {

    srand(seed);
    const uint24_t sizeZ = sizeX * sizeY;

    //fillMemory(25,flag,mineCount); //ASM LDIR

    uint8_t* fill = flag; //Address of flag array
    for (uint24_t i = 0; i < mineCount; i++) { //Slower because Clang is unware of LDIR
        *fill = 25;
        fill++;
    }

    uint8_t temp;
    uint24_t swap;

    for (uint24_t i = 0; i < sizeZ; i++) { //Random Shuffle
        swap = rand() % sizeZ;
        temp = flag[i];
        flag[i] = flag[swap];
        flag[swap] = temp;
    }

    uint8_t* aux = flag;
    uint8_t* grid = board + border + (marX * border);
    for (uint8_t y = 0; y < sizeY; y++) {
        for (uint8_t x = 0; x < sizeX; x++) {
            if (*grid != 30) {
                *grid = *aux;
                aux++;
            } else {
                printUInt(grid - board,6,16,2,72);
                printUInt(*grid,4,10,2,81);
                printUInt(aux - flag,6,16,2,99);
                printUInt(*aux,4,10,2,108);
            }
            grid++;
        }
        grid += (border * 2);
    }

    fill = flag;
    for (uint24_t i = 0; i < 52*27; i++) { // Resets flag array
        *fill = 0;
        fill++;
    }

    for (uint8_t y = border; y < marY - border; y++) {
        for (uint8_t x = border; x < marX - border; x++) {
            if (board[y * marX + x] != 25) {
                uint8_t count = 0;
                int24_t u;
                int24_t v;
                for (uint8_t i = 0; i < offLen; i += 2) {
                    u = order[offPos + i];
                    v = order[offPos + i + 1];
                    if (board[(y + v) * marX + (x + u)] == 25) {
                        count++;
                    }
                }
                board[y * marX + x] = count;
            }
        }
    }
}
*/

void chord() {
	return;
    lcd_CrsrX = ((tile % marX) - 2) * disX + posX;
    lcd_CrsrY = ((tile / marX) - 2) * disY + posY;
}
uint8_t gridType[25];
void cursorSetup() { // Code may crash the calculator
	return; // Disabled for now
    //memcpy(lcd_CrsrImage, chordImage, 1024);
	//uint8_t* ci = (uint8_t*)lcd_CrsrImage;
    /* //Crashes calculator and maybe broken
    for (uint24_t i = 0; i < 1024; i++) { 
        *ci = 0b10101010; //Transparent
		ci++;
    }
    */
    for (uint8_t i = 0; i < offLen; i += 2) { //Generates fill grid from search pattern
        int8_t u = order[offPos + i];
        int8_t v = order[offPos + i + 1];
        gridType[12 + u + (v * 5)] = 0b00000011;
    }
    gridType[12] = 0b01;

    uint8_t dX = (disX * 5) - 1;
    uint8_t dY = (disY * 5) - 1;
    uint8_t* i = (uint8_t*)lcd_CrsrImage;
    uint8_t v = 0;
    for (uint8_t y = 0; y < dY; y++) { //Fills 2bit grid
        if (y % disY == disY - 1) {
            i += 16;
            v += 5;
        } else {
            uint8_t u = 0;
            for (uint8_t x = 0; x < 64; x += 4) {
                uint8_t g = 0;
                for (uint8_t z = 0; z < 4 && (z + x < dX); z++) {
                    if ((x + z) % disX != disX - 1) {
                        //g |= (gridType[((y / disY) * 5) + (x / disX)] << 5) >> z;
                        g |= (gridType[u + v] << 6) >> (z << 1);
                    } else {
                        u++;
                    }
                }
                *i |= g;
                i++;
            }
        }
    }

    lcd_CrsrCtrl = 0x00000000; // enable cursor
    lcd_CrsrPalette0 = 0x00FFBF00; //24bit 888 BGR
    lcd_CrsrPalette1 = 0x000000FF;
    // lcd_CrsrXY = 0; // reset cursor position
    chord();
    lcd_CrsrClip = 0; // reset clipping
    lcd_CrsrConfig = 0x00000001;
    lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(320 - 1) << 16; //Set CPL
}

void drawGame() {

    gColor = 17;
    //gColor = findColor888(0x00,0x70,0x70); //Failed test
    fillScreen(); //Cyan       
    if (fadeEffect > 0) {
        if (fadeEffect == 1) {
            uint16_t *fP = lcd_Palette;
            fP += 18;
            for (uint8_t i = 18; i < 22; i++) {
                *fP = 330;
                fP++;
                initialPalette[i] = 330;
            }
        }
        for (uint24_t rY = 4; rY < LCD_RESY; rY += 32) {
            for (uint24_t rX = 4; rX < LCD_RESX; rX += 32) {
                gColor = 18;
                text6x8(rX, rY, gMine);
                gColor = 19;
                text6x8(rX + 16, rY, gFlag);
                gColor = 20;
                text6x8(rX, rY + 16, 30);
                gColor = 21;
                text6x8(rX + 16, rY + 16, 31); //116 inverted flag
                vert(rX + 15, rY + 16, 8);
                vert(rX + 22, rY + 16, 8);
            }
        }
    }

    gColor = (15); //Fill Sqaures
    for (int24_t y = 2; y < marY - 2; y++) {
        for (int24_t x = 2; x < marX - 2; x++) {
            fillRect(x * disX + posX + 1, y * disY + posY + 1, disX - 2, disY - 2);
        }
    }
    /*for (uint24_t x = 5; x < 55; x += 10) { // Flag Squares
        fillRect(x, 5, 9, 9);
    }*/ //Don't delete me
    //Shaded Lines
    for (int24_t i = (disX * 2) + posX; i < disX * (marX - 2) + posX; i += disX) {
        gColor = (7);
        vert(i, (disY * 2) + posY, disY * (sizeY) - 1);
        gColor = (0);
        vert(i + disX - 2, (disY * 2) + posY, disY * (sizeY) - 1);
    }
    for (int24_t i = (disY * 2) + posY; i < disY * (marY - 2) + posY; i += disY) {
        gColor = (7);
        horiz((disX * 2) + posX, i, disX * (sizeX) - 1);
        gColor = (0);
        horiz((disX * 2) + posX, i + disY - 2, disX * (sizeX) - 1);
    }
    if (!(disX & 1)) { //% 2
        gColor = (darkMode != 0) ? 0x07 : 0x00; //Inverted Colors
        vert(LCD_RESX - 1, 0, LCD_RESY);
    }
    //Border Lines
    gColor = (8);
    for (int24_t i = (disY * 2) - 1 + posY; i <= disY * (marY - 2) - 1 + posY; i += disY) {
        horiz((disX * 2) - 1 + posX, i, disX * (sizeX) + 1);
    }
    for (int24_t i = (disX * 2) - 1 + posX; i <= disX * (marX - 2) - 1 + posX; i += disX) {
        vert(i, (disY * 2) - 1 + posY, disY * (sizeY) + 1);
    }

    /*
    //UI Lines //Don't delete this
    horiz(4, 4, 51);
    horiz(4, 14, 51);
    for (uint24_t i = 4; i < 64; i += 10) {
        vert(i, 5, 9);
    }
    */
    /*{//Manually Draw Flag UI (Don't delete me)
        uint16_t bitImage0 = char5x5[52];
        uint16_t bitImage1 = char5x5[53];
        uint16_t bitImage2 = char5x5[50];
        uint16_t bitImage3 = char5x5[51];
        uint24_t z0 = VRAM + (7 * LCD_RESX) + 7;
        uint24_t z1 = z0 + 960;
        uint24_t z2 = VRAM + (7 * LCD_RESX) + 47;
        uint24_t z3 = z2 + 960;
        gColor = 0;
        for (uint24_t y = 0; y < 1600; y += LCD_RESX) {
            for (uint24_t x = 0; x < 5; x++) {
                if (bitImage0 & 1) {
                    plotFast(z0 + y + x);
                }
                if (bitImage1 & 1) {
                    plotFast(z1 + y + x);
                }
                if (bitImage2 & 1) {
                    plotFast(z2 + y + x);
                }
                if (bitImage3 & 1) {
                    plotFast(z3 + y + x);
                }
                bitImage0 >>= 1;
                bitImage1 >>= 1;
                bitImage2 >>= 1;
                bitImage3 >>= 1;
            }
        }
        gColor = flagColor;
        fillRect(7, 7, 2, 2);
        gColor = 7;
        plotFast(VRAM + (LCD_RESX * 8) + 48); //x48 y8
    }*/

    for (uint24_t x = 154; x <= 164; x++) {
        for (uint24_t y = 5; y <= 15; y++) {
            if ((x - 159) * (x - 159) + (y - 10) * (y - 10) < 36) {
                gColor = 2;
				plot(x,y);
            }
        }
    }
	
	expression(eNORMAL);
	expression(eHAPPY);

    //GUI Counters
    flagCount();
    /* Color numbers */
    buildSeg7(4912,18,&flagLCD,3,9,0,0x00,0x1B,0x81,0x80); //Flags 17^3 - 1
    flagLCD.digits = 1;
    gColor = 0x1B;
    fillRect(0,0,9,19);
    fillRect(39,0,9,19);
    flagCount();
    //Manual Symbol Draw
    gColor = 0x00;
    text6x8(2,1,gMine);
    text6x8(40,1,gFlag);
    gColor = 0x01;
    fillRect(40,2,3,3);
    gColor = 0x07;
    plot(4,3);
    plot(3,4);
    /* Color numbers */

    buildSeg7(104975,18,&timeLCD,4,224,0,0x00,0x1B,0x83,0x82); //Time 18^4 - 1
    buildSeg7(1889567,18,&scoreLCD,5,272,0,0x00,0x1B,0x85,0x84); //Score 18^5 - 1

}

const uint8_t fontList[] = {24,16,6,  28,16,5,  35,19,4,  31,21,2,  39,27,2,  39,21,1,  39,27,0};
void fontCheck() { //Plus 4
    uint8_t i = 7;
    for (uint8_t j = 0; j < 24; j += 3) {
        if (fontSize == i && (sizeX > fontList[j] || sizeY > fontList[j + 1])) {
            fontSize = fontList[j + 2];
        }
        i--;
    }
    font = fontArray[fontSize];
    disX = fontArray[fontSize + 8];
    disY = fontArray[fontSize + 16];
    padX = fontArray[fontSize + 24];
    padY = fontArray[fontSize + 32];
}

void resetGame() {

    //1: Board
    marX = sizeX + 4;
    marY = sizeY + 4;
	fontSize = 7; // Resets font size to the largest available before doing the font check stuff
    fontCheck(); //Fits font to screen size

    posX = 160 - (disX >> 1) * marX; //Allign game board
    if (disX & 1) { //Special case of even distance X
        posX -= marX >> 1;
    }
    posY = 21 - (disY * 2);
 
    // for (int24_t i = 0; i < marX * marY; i++) { //Writes invalid spaces
    //     board[i] = 255;
    //     state[i] = 255;
    //     search[i] = 0;
    // }
	size_t marZ = (size_t)marX * (size_t)marY;
	memset(board,255,marZ * sizeof(board[0]));
	memset(state,255,marZ * sizeof(state[0]));
	memset(search,0,marZ * sizeof(search[0]));
	{
		size_t z = (borderIndexes * marX) + borderIndexes;
		for (uint8_t y = 0; y < sizeY; y++) { //Clears arrays
			for (uint8_t x = 0; x < sizeX; x++) {
				board[z] = 0;
				state[z] = 0;
				flag[z] = 0;
				z++;
			}
			z += 2 * borderIndexes;
		}
	}

    //2: Reset
    autoLoss = 0;
    cheater = 0;
    item = 0; //Resets the search pointer
    max = 0; //Resets the search max
    cleared = 0; //Resets the amount of cleared tiles
    win = 1; //Enables winning again
    score = 0;
    gamePauseTime = systemTime;
    offPos = orderPos[gameMode];
    offLen = orderPos[gameMode + 1] - orderPos[gameMode];
    if (mineCount > ((sizeX) * (sizeY)) / 2) { //Caps game at 50% mines
        mineCount = ((sizeX) * (sizeY)) / 2;
    }
    flags = mineCount;
    mines = mineCount;
    tile = (marX * 7) + 7; //Initial tile

    //3: Graphics
    drawGame();

    //4: Cursor 
    if (cursorAllow) {
        cursorSetup();
    }

    //5: Finalize
    fillTile(tile, 1); //Color in select tile to show that setup is finished
}

//8x8: 0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010
//New Line: ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010

uint8_t autoCheck = 0;
void autoChord() {

    if (state[tile] == 0) {
        return;
    }
    int24_t u;
    int24_t v;
    uint8_t bC = 0; //Blank Count
    uint8_t mC = 0; //Mine Count
    uint8_t fC = 0; //Flag Count
    uint24_t square;
    for (uint8_t i = 0; i < offLen; i += 2) {
        u = order[offPos + i];
        v = order[offPos + i + 1];
        square = tile + (v * marX) + u;
        if (board[square] != 255) { //If tile is in bounds
            if (board[square] == gMine) {
                mC++;
            }
            if (flag[square] == fFLAG || (board[square] == gMine && state[square] != sHIDDEN)) {
                fC++;
            }
            if (state[square] != sCLEARED || board[square] == gMine) { //== 0
                bC++;
            }
        }
    }


    if (fC == mC) { //Flag Chording, clears tiles
        for (uint8_t i = 0; i < offLen; i += 2) {
            u = order[offPos + i];
            v = order[offPos + i + 1];
            square = tile + (v * marX) + u;
            if (board[square] != 255 && state[square] != sCLEARED && flag[square] != fFLAG) { //If tile is not out of bounds and not cleared yet
                state[square] = sCLEARED;
                //Floodfill
                cleared++;
                if (board[square] == 0) {
                    uint24_t tileAC = tile;
                    tile = square;
                    floodFill();
                    tile = tileAC;
                }
                score += 10;
                fillTile(square, tCLEAR);
                autoCheck = 1;
            }
        }
    } else if (board[tile] == mC && bC == mC) { //fC != mC //Tile Chording, places flags
        for (uint8_t i = 0; i < offLen; i += 2) {
            u = order[offPos + i];
            v = order[offPos + i + 1];
            square = tile + (v * marX) + u;
            if (board[square] != 255 && state[square] != sCLEARED && flag[square] != fFLAG) { //If tile is not out of bounds and not cleared yet
                flag[square] = fFLAG;
                flags--;
                gColor = 15;
                fillRect(square % marX * disX + 1 + posX, square / marX * disY + 1 + posY, disX - 3, disY - 3);
			    glyph(square, gFlag);
                autoCheck = 1;
            }
        }
        flagCount();
    }
}

void autoSolve() {
    cheater = 1;
    uint24_t tileAS = tile;
    for (uint8_t i = 0; i < autoSolver; i++) { //Genius Right? 1 if manual, 2 if auto haha
        autoCheck = 0;
        tile = marX * borderIndexes + borderIndexes;
        for (uint8_t y = 0; y < sizeY; y++) {
            for (uint8_t x = 0; x < sizeX; x++) {
                autoChord();
                tile++;
            }
            tile += (borderIndexes * 2);
        }
        if (autoCheck != 0) {
            i = 0;
        }
    }
    tile = tileAS;
}

uint8_t chordCheck = 0;
void gameLoop() {
    //key = 99; //Prevents endless restart loop
    do {
        status = OKAY;
        resetGame();
	    gameControl();
    } while (status == RESTART);
    if (status == QUIT) {
        status = OKAY;
    }
    if (cursorAllow) { // Resets the cursor
        lcd_CrsrConfig = 0x00000000;
        lcd_CrsrCtrl = 0x00000000;
        lcd_Timing2 = (uint32_t)(lcd_Timing2 & ~(uint32_t)0x03FF0000) | (uint32_t)(240 - 1) << 16;
    }
}

void gameControl() {
	while (status == OKAY) {
        keyPress(); if (status != OKAY) { break; }

        if (cleared != 0) { //Time 
            displaySeg7(score,10,&scoreLCD); //Score
            if (currentTime < 327680000) { // <10000 seconds or <2.78 Hours
                displaySeg7(currentTime >> 15,10,&timeLCD);
            } else { //Blinks after 9999 seconds
                if (systemTime & 16384) {
                    displaySeg7(104975,18,&timeLCD); //Time ---- 18^4 - 1
                } else {
                    displaySeg7(9999,10,&timeLCD); //Time 9999
                }
            }
        } else if (currentTime >= 327680000) {
            displaySeg7(9999,10,&timeLCD); //Time 9999
        }
        
        if ((kb_Data[3] & kb_GraphVar) && cleared != 0 && keyReady & CHORD) {
            keyReset(cHORD);
            autoChord();
        }

        if (kb_Data[6] & kb_Power && cleared != 0 && keyReady & DEBUG && autoSolver) {
            keyReset(dEBUG);
            expression(eCHORD);
            autoSolve();
            if (win) {
                expression(eHAPPY);
            } else {
                expression(eSAD);
            }
        }

        if (cursorAllow) {
            if (keyReady & CHORD) {
                if ((kb_Data[3] & kb_GraphVar)) {
                    keyReset(cHORD);
                    //lcd_CrsrCtrl = 0x00000001;
					expression(eCHORD);
                    chordCheck = 1;
                } else if (chordCheck == 1) {
                    //lcd_CrsrCtrl = 0x00000000;
                    if (win) {
						expression(eHAPPY);
                    } else {
						expression(eSAD);
                    }
                    chordCheck = 0;
                }
            }
        }
			
        if (kb_Data[7] && (keyReady & ARROW)) { //Checks that an arrow key was pressed
            keyReset(aRROW);

            fillTile(tile, tCLEAR); //Clears Tile
			
            if (kb_Data[7] & kb_Up) {
                if (board[tile - marX] != 255) {
                    tile -= marX;
                } else {
                    tile += marX * (marY - 5);
                }
            }
            if (kb_Data[7] & kb_Down) {
                if (board[tile + marX] != 255) {
                    tile += marX;
                } else {
                    tile -= marX * (marY - 5);
                }
            }
            if (kb_Data[7] & kb_Left) {
                if (board[tile - 1] != 255) {
                    tile--;
                } else {
                    tile += (marX - 5);
                }
            }
            if (kb_Data[7] & kb_Right) {
                if (board[tile + 1] != 255) {
                    tile++;
                } else {
                    tile -= (marX - 5);
                }
            }
            if (cursorAllow) {
                chord();
            }
			
            fillTile(tile, tSELECT); //Draws Tile
        }
			
		if ((keyReady & ALPHA) && alphaBind()) {
			keyReset(aLPHA);

            if (flag[tile] == fFLAG) { //Removes flag from tile and updates flag counters
				flag[tile] = fBLANK;
				flags++;
                fillTile(tile, tSELECT);
				flagCount();
			} else {
                flag[tile] = fBLANK; //Clears fQUESTION to 0
                if (cleared == 0) {
                    // if (safeGuess == 1) {
                    //     board[tile] = 30;
                    // }
                    // if (safeGuess == 2) {
                    //     int24_t u;
                    //     int24_t v;
                    //     for (uint8_t i = 0; i < offLen; i += 2) {
                    //         u = order[offPos + i];
                    //         v = order[offPos + i + 1];
                    //         board[tile + (v * marX) + u] = 30;
                    //     }
                    //     if (gameMode == 3 || gameMode == 9) {
                    //         for (uint8_t i = 0; i < 8; i++) {
                    //             u = order[i];
                    //             v = order[i + 1];
                    //             board[tile + (v * marX) + u] = 30;
                    //         }
                    //     }
                    // }
                    mineGenerate();
                    gamePauseTime = 0;
                    gameStartTime = systemTime;
                }

                if (state[tile] == sHIDDEN) {
                    cleared++; //Add uncleared tile to cleared counter
                    score += 10;
                }
                state[tile] = sCLEARED;
                
                if (board[tile] == gMine) { //If tile contains mine
                
                    fillTile(tile, tFLAG);
                    //cleared--;
                } else {
                    fillTile(tile,tSELECT);
                    if (board[tile] == 0) { // ZERO MINES FLOODVILLE TIME!
                        floodFill();
                        flagCount();
                    }
                    if (((sizeX) * (sizeY)) - mines - cleared == 0 && win) { //Win
                        expression(eSHADES);
                        lcd_CrsrCtrl = 0x00000000;
                        flash();
                        winScreen();
                    }
                }
            }


		}

        if (autoLoss == 1 && win == true) {
            expression(eSAD);
            //lcd_CrsrCtrl = 0x00000000;
            quake();
            flash();
            gameOver();
            win = false;
        }
		
		if (((keyReady & SECOND) && secondBind()) && state[tile] != sCLEARED) { //2nd
			keyReset(sECOND);
			if (flag[tile] == fFLAG) { //If there is a flag remove it
				flag[tile] = fBLANK;
				flags++;
			} else if (flags > -99) { //I don't want to display -100 flags
				flag[tile] = fFLAG;
				flags--;
			}
			fillTile(tile, tSELECT);
			flagCount();
		}
		if (((keyReady & OTHER) && (kb_Data[1] & kb_Yequ)) && state[tile] != sCLEARED) { //Y=
			keyReset(oTHER);
			if (flag[tile] == fQUESTION) {
				flag[tile] = fBLANK;
			} else {
				if (flag[tile] == fFLAG) {
					flag[tile] = fBLANK; //Why must it be fBLANK?
					flags++;
					flagCount();
				}
				flag[tile] = fQUESTION;
			}
			fillTile(tile, tSELECT);
		}
		if ((keyReady & OTHER) && (kb_Data[1] & kb_Mode)) { //Mode
			keyReset(oTHER);
			pause();
		}

		// Game Saving doesn't currently work
			// if ((keyReady & OTHER) && (kb_Data[6] & kb_Add)) {
			// 	keyReset(oTHER);
			// 	loadGame(NULL,state,flag);
			// }
			// if ((keyReady & OTHER) && (kb_Data[6] & kb_Sub)) {
			// 	keyReset(oTHER);
			// 	printf("\nSaving Game");
			// 	GameSaveFile gameSaveFile;
			// 	gameSaveFile.Version[0] = PROGRAM_V_MAJOR;
			// 	gameSaveFile.Version[1] = PROGRAM_V_MINOR;
			// 	gameSaveFile.Version[2] = PROGRAM_V_PATCH;
			// 	gameSaveFile.Version[3] = 0;
			// 	gameSaveFile.TimeElapsed = systemTime - gameStartTime - gamePauseTime;
			// 	gameSaveFile.Score = score;
			// 	gameSaveFile.Seed = currentGameSeed;
			// 	gameSaveFile.SizeX = sizeX;
			// 	gameSaveFile.SizeY = sizeY;
			// 	gameSaveFile.CursorPos = tile;
			// 	gameSaveFile.GameState = ((cheater & 1) << 1) | (win & 1);
			// 	gameSaveFile.GameMode = gameMode;
			// 	saveGame(&gameSaveFile,state,flag) == false;
			// }
    }
}