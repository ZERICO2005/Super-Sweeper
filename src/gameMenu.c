/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "gameMenu.h"

#include "prime2D.h"
#include "primeKey.h"
#include "global.h"

#include "mineSweeper.h"

void pause6x8(uint24_t xW, uint24_t yW, uint8_t lexicon) {
    uint8_t* bitImage = (uint8_t*)char6x8 + (lexicon * 6);
    uint8_t* fill = lcd_Ram8 + (yW * 320 + xW);
    uint8_t b = 1;
	uint8_t fColor = (gColor << 4) + gColor;
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 6; x++) {
            *fill = *bitImage & b ? fColor : *fill;
            fill += 160;
            *fill = *bitImage & b ? fColor : *fill;
            fill-= 159;
            bitImage++;
        }
        bitImage -= 6;
        fill += 314; // 320 - 6
        b <<= 1;
    }
}

void text6x8b4(uint24_t xW, uint24_t yW, uint8_t lexicon) { //Incompatibile with 0.70.Alpha and later
	uint24_t bitImage0 = char6x8[lexicon];
    uint24_t bitImage1 = char6x8[lexicon + 1];
    uint8_t* fill0 = lcd_Ram8 + (yW * 320 + xW);
    uint8_t* fill1 = fill0 + 1280;
    uint24_t b = 1;
	uint8_t fColor = gColor << 4;
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 3; x++) {
			*fill0 = bitImage0 & b ? gColor : 0;
			*fill1 = bitImage1 & b ? gColor : 0;
			b <<= 1;
			*fill0 += bitImage0 & b ? fColor : 0;
			*fill1 += bitImage1 & b ? fColor : 0;
            fill1++;
            fill0++;
        }
        fill0 += 157; //320 - 6
        fill1 += 157;
    }
}

uint8_t scoreSort() { //broken
    uint24_t off = gameMode * 6;
    for (uint8_t i = 0; i < 6; i++) {
        if (score > leaderboard[i + off]) {
            for (uint8_t j = i; j < 5; j++) {
                leaderboard[j + 1 + off] = leaderboard[j + off];
            }
            score = leaderboard[i + off];
            return i;
        }
    }
    return 99; //Probably Keys
}

void fadeIn() { //Fade in after setup
    for (uint8_t k = 0; k <= 32; k++) {
        uint32_t flashTime = timer_Get(1);
        uint8_t i = 0;
		uint8_t j = 32 - k;
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

void printStat(uint24_t n) { //Proprietary
    if (n > 999) {
        pause6x8(127, 324, ((n / 1000) % 10));
    }
    if (n > 99) {
        pause6x8(134, 324, ((n / 100) % 10));
    }
    if (n > 9) {
        pause6x8(141, 324, ((n / 10) % 10));
    }
    pause6x8(148, 324, (n % 10));
}


void scoreScreen() { //broken //I shall fix the sorting now that I can code insertion sort
    return;
    /*
    uint16_t *fP = lcd_Palette; //Fade in after setup
    for (uint8_t k = 0; k < 32; k++) {
        uint8_t j = 31 - k;
        for (uint16_t i = 0; i < 256; i++) {
            *fP = (linear((initialPalette[i] >> 10) & 31, 31, 0, 31, j) << 10) | (linear((initialPalette[i] >> 5) & 31, 31, 0, 31, j) << 5) | (linear(initialPalette[i] & 31, 31, 0, 31, j));
            fP++;
        }
        fP -= 256;
    }
    uint8_t name[3] = {33,33,33};
    gColor = 0;
    fillRect(0,240,320,120); //Clears the screen
    gColor = 7;
    {
        uint24_t x = 8;
        uint24_t y = 248;
        uint8_t i = 0;
        for (uint24_t j = section[9]; j < section[10]; j++) { //Set to Win Screen text for temporary measures
            if (text[j] == 146) {
                x = 8;
                y += 12;
                if (i == 0 || i == 4) {
                    y += 8;
                }
                i++;
                if (i > 0 && i < 5) {
                    x = 15;
                }
            } else {
                pause6x8(x, y, text[j]);
                x += 7;
            }
        }
    }

    gColor = 7;
    pause6x8(148, 268, (scoreSort() % 10));
    pause6x8(148, 280, (score % 10));
    pause6x8(148, 292, (timer % 10));
    gColor = 0;
    pause6x8(50, 304, 66);
    pause6x8(57, 304, 66);
    pause6x8(64, 304, 66);
    option = 0;
    while (!(kb_Data[1] & (kb_Graph | kb_Del))) {
        do {
            keyPress();
            
        } while(key == 0);
        if (kb_Data[7] & kb_Up) {
            if (name[option] == 58) {
            } else {
                name[option] = 33;
                name[option]++;
            }
            gColor = 7;
            fillRect(50 + (option * 7),304,6,8);
            gColor = 0;
            pause6x8(50 + (option * 7), 304, name[option]);
        }
        if (kb_Data[7] & kb_Down) {
            if (name[option] == 33) {
                name[option] = 58;
            } else {
                name[option]--;
            }
            gColor = 7;
            fillRect(50 + (option * 7),304,6,8);
            gColor = 0;
            pause6x8(50 + (option * 7), 304, name[option]);
        }
        if (kb_Data[7] & kb_Left) {
            if (option == 0) {
                option = 2;
            } else {
                option--;
            }
        }
        if (kb_Data[7] & kb_Right) {
            if (option == 2) {
                option = 0;
            } else {
                option++;
            }
        }
        if ((kb_Data[6] & kb_Enter) || (kb_Data[2] & kb_Alpha)) {
            break;
        }
    }
    */
}

void timeDisplay(uint32_t input) { //systemTime - gameStartTime - gamePauseTime
    uint32_t _1000mili = 0;
    uint32_t _100mili = 0;
    uint32_t _10mili = 0;
    //uint32_t _1mili;
    //uint32_t _100micro;
    if (cleared != 0) {
        _1000mili = (input / 32768); // Time to nearest second, full accuracy
        _100mili = (input / 3277); // 100 mili Second, 16385/16384 ~6.104e-5 accuracy
        _10mili = (input / 328); // 10 mili Second, 1025/1024 ~9.766e-4 accuracy
        //_1mili = (input / 33); // 1 mili Second, 4125/4096 ~7.080e-3 accuracy
        //_100micro = (input / 3); // 100 micro Second, 1875/2048 ~8.447e-2 accuracy
    }
	if (_1000mili > 9999) { // ~2.8 Hours
        pause6x8(103, 336, ((_1000mili / 10000) % 10));
    }
	if (_1000mili > 999) { // ~16.7 minutes
        pause6x8(110, 336, ((_1000mili / 1000) % 10));
    }
    if (_1000mili > 99) { // 100 Seconds
        pause6x8(117, 336, ((_1000mili / 100) % 10));
    }
    if (_1000mili > 9) { // 10 Seconds
        pause6x8(124, 336, ((_1000mili / 10) % 10));
    }
    pause6x8(136, 336, 34); //Decimal Point
    pause6x8(131, 336, (_1000mili % 10)); // 1 Second
    pause6x8(141, 336, (_100mili % 10)); // 100 MiliSeconds
    pause6x8(148, 336, (_10mili % 10)); // 10 MiliSeconds
}

void pauseScroll() {
    if ((kb_Data[7] & (kb_Up | kb_Down)) && (keyReady & VERT)) {
        keyReset(vERT);
        gColor = 0;
        pause6x8(8, 268 + (option * 12), 29);
        pause6x8(141, 268 + (option * 12), 28);
        if ((kb_Data[7] & kb_Up)) {
            if (option == 0) {
                option = 3;
            } else {
                option--;
            }
        } else { //Must be Down
            if (option == 3) {
                option = 0;
            } else {
                option++;
            }
        }
        gColor = 7;
        pause6x8(8, 268 + (option * 12), 29);
        pause6x8(141, 268 + (option * 12), 28);
    }
}

void winScreen() {
    if (gameFinishTime == 0) {
        gameFinishTime = systemTime - gameStartTime - gamePauseTime;
    }
    pauseTime = systemTime;
	lcd_UpBase = 0xD40000 + (320 * 240 * 1);
    lcd_VideoBit = lcd_Video4bit; //4bit mode
    gColor = 0;
    fillRect(0,240,320,120); //Clears the screen

    // if (scoreSort() != 99 || 1) { //Force Debug Run
    //     scoreScreen();
    // } //Do not use for now please

    gColor = 7;
    {   
        uint24_t x = 8;
        uint24_t y = 248;
        uint8_t i = 0;
        uint24_t j = 0;
        if (cheater == 1) {
            j = 14; //Majic Number
            for (uint8_t j = 0; j < cheatTextLength; j++) {
                pause6x8(x, y, cheatText[j]);
                x += 7;
            }
        }
        for (; j < winTextLength; j++) {
            if (winText[j] == 33) {
                x = 8;
                y += 12;
                if (i == 0 || i == 4) {
                    y += 8;
                }
                i++;
                if (i > 0 && i < 5) {
                    x = 22;
                }
            } else {
                pause6x8(x, y, winText[j]);
                x += 7;
            }
        }
    }

    pause6x8(8, 268, 29);
    pause6x8(141, 268, 28);

    option = 0;
    printStat(score);

    timeDisplay(gameFinishTime);

    fadeIn();

    while (!(kb_Data[1] & (kb_Graph | kb_Del))) {
        keyPress();


        pauseScroll();

        if (((kb_Data[6] & kb_Enter) || (kb_Data[2] & kb_Alpha)) && (keyReady & ALPHA)) {
            keyReset(aLPHA);
            if (option == 0) { //Resume
                gamePauseTime += (systemTime - pauseTime); 
            } else if (option == 1) { //Restart
                //key = 90;
                status = RESTART;
            } else if (option == 2) { //Main Menu
                //key = 80;
                status = QUIT;
            } else if (option == 3) { //Quit
                //key = 49;
                status = FORCEQUIT;
            }
            lcd_UpBase = 0xD40000;
            lcd_VideoBit = lcd_Video8bit; //8bit mode
            break;
        }
    }
    lcd_UpBase = 0xD40000;
    lcd_VideoBit = lcd_Video8bit; //8bit mode
}

void gameOver() { //160x120 screen due to poor coding
    pauseTime = systemTime;

    lcd_UpBase = 0xD52C00;
    lcd_VideoBit = lcd_Video4bit; //4bit mode
    gColor = 0;
    fillRect(0,240,320,120); //Clears the screen

    gColor = 7;
    {   
        uint24_t x = 8;
        uint24_t y = 248;
        uint8_t i = 0;
        for (uint24_t j = 0; j < gameOverTextLength; j++) {
            if (gameOverText[j] == 33) {
                x = 8;
                y += 12;
                if (i == 0 || i == 4) {
                    y += 8;
                }
                i++;
                if (i > 0 && i < 5) {
                    x = 22;
                }
            } else {
                pause6x8(x, y, gameOverText[j]);
                x += 7;
            }
        }
    }
    pause6x8(8, 268, 29);
    pause6x8(141, 268, 28);
    

    option = 0;
    uint24_t clearTemp = ((sizeX) * (sizeY)) - mines - cleared + 1;
    printStat(clearTemp);
    
    timeDisplay(systemTime - gameStartTime - gamePauseTime);

    fadeIn();


    while (!(kb_Data[1] & (kb_Graph | kb_Del))) {
        keyPress();

        pauseScroll();

        if ((kb_Data[6] & kb_Enter) || (kb_Data[2] & kb_Alpha)) {
            if (option == 0) {
                //key = 90;
                status = RESTART;
            } else if (option == 1) {
                //key = 80;
                status = QUIT;
            } else if (option == 2) { //Resume
                gamePauseTime += (systemTime - pauseTime);
            } else if (option == 3) {
                //key = 49;
                status = FORCEQUIT;
            }
            lcd_UpBase = 0xD40000;
            lcd_VideoBit = lcd_Video8bit; //8bit mode
            break;
        }
    }
    lcd_UpBase = 0xD40000;
    lcd_VideoBit = lcd_Video8bit; //8bit mode
}

void pause() {
    pauseTime = systemTime;
    gColor = 0;
    fillRect(0,240,320,120); //Clears the screen

    gColor = 7;
    {   
        uint24_t x = 8;
        uint24_t y = 248;
        uint8_t i = 0;
        for (uint24_t j = 0; j < pauseTextLength; j++) {
            if (pauseText[j] == 33) {
                x = 8;
                y += 12;
                if (i == 0 || i == 4) {
                    y += 8;
                }
                i++;
                if (i > 0 && i < 5) {
                    x = 22;
                }
            } else {
                pause6x8(x, y, pauseText[j]);
                x += 7;
            }
        }
    }
    pause6x8(8, 268, 29);
    pause6x8(141, 268, 28);

    option = 0;
    uint24_t clearTemp = ((sizeX) * (sizeY)) - mines - cleared;
    printStat(clearTemp);

    timeDisplay(systemTime - gameStartTime - gamePauseTime);
    
    lcd_UpBase = 0xD52C00;
    lcd_VideoBit = lcd_Video4bit; //4bit mode
    
    while (!(kb_Data[1] & (kb_Graph | kb_Del))) {
        keyPress();

        pauseScroll();

        if ((kb_Data[6] & kb_Enter) || (kb_Data[2] & kb_Alpha)) {

            if (option == 0) { //Resume
                gamePauseTime += (systemTime - pauseTime);
            } else if (option == 1) {
                status = RESTART;
                //key = 90;
            } else if (option == 2) {
                status = QUIT;
                //key = 80;
            } else if (option == 3) {
                status = FORCEQUIT;
                //key = 49;
            }
            lcd_UpBase = 0xD40000;
            lcd_VideoBit = lcd_Video8bit; //8bit mode
            break;
        }
    }
    lcd_UpBase = 0xD40000;
    lcd_VideoBit = lcd_Video8bit; //8bit mode
}