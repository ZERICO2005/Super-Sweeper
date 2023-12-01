/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

//#include "global.h"
#ifndef X86RENDER_H
#define X86RENDER_H

#include <stdint.h>
//#include <int24_type.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef uint32_t uint24_t;
typedef int32_t int24_t;
typedef uint32_t u24;
typedef int32_t i24;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/* Pointers */

uint8_t _VRAM[153600];
void* VRAM = _VRAM + 0;
void* WRAM = _VRAM + 76800;
void* XRAM = _VRAM + 153600;

uint32_t _frameBase = 0xD40000;
uint32_t* frameBase = &_frameBase;

uint16_t _paletteRAM[256];
uint16_t* paletteRAM = _paletteRAM;

volatile uint16_t _videoMode = 0x92D;
volatile uint16_t* videoMode = &_videoMode;

uint32_t _LCDTiming0 = 0x1F0A0338;
uint32_t* LCDTiming0 = &_LCDTiming0;
uint32_t _LCDTiming1 = 0x0402093F;
uint32_t* LCDTiming1 = &_LCDTiming1;
uint32_t _LCDTiming2 = 0x00EF7802;
uint32_t* LCDTiming2 = &_LCDTiming2;
uint32_t _LCDTiming3 = 0x00000000;
uint32_t* LCDTiming3 = &_LCDTiming3;

uint32_t _lcd_CrsrImage;
uint32_t* lcd_CrsrImage = &_lcd_CrsrImage;
uint32_t _lcd_CrsrCtrl;
uint32_t* lcd_CrsrCtrl = &_lcd_CrsrCtrl;
uint32_t _lcd_CrsrConfig;
uint32_t* lcd_CrsrConfig = &_lcd_CrsrConfig;
uint32_t _lcd_CrsrPalette0;
uint32_t* lcd_CrsrPalette0 = &_lcd_CrsrPalette0;
uint32_t _lcd_CrsrPalette1;
uint32_t* lcd_CrsrPalette1 = &_lcd_CrsrPalette1;
uint32_t _lcd_CrsrXY;
uint32_t* const lcd_CrsrXY = &_lcd_CrsrXY;
uint16_t* lcd_CrsrX = (uint16_t*)lcd_CrsrXY;
uint16_t* lcd_CrsrY = (uint16_t*)((uint8_t*)lcd_CrsrXY + 2);
uint32_t _lcd_CrsrClip;
uint32_t* lcd_CrsrClip = &_lcd_CrsrClip;

/* Pointers */

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Texture* texture;
SDL_Texture* buffer;

#define resX 320
#define resY 240
int32_t pitch = resX * 3;

uint8_t videoCopy[153600];
uint16_t color16[256];
uint8_t colorR[256];
uint8_t colorG[256];
uint8_t colorB[256];
uint8_t scale = 2;

#define keyBindSelection keyBind2

struct bound {
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;
};
struct bound expandedPos[56] = {
    {1,1,4,2},{6,1,4,2},{11,1,4,2},{16,1,4,2},{21,1,4,2}, //F1-F5
    {19,4,3,3},{19,10,3,3},{16,7,3,3},{22,7,3,3},//Orthagonal UDLR
    {22,4,3,3},{16,10,3,3},{16,4,3,3},{22,10,3,3},//Diagonal Shift Clockwise
    {1,5,4,3},{6,5,4,3},{11,5,4,3}, //2nd
    {1,9,4,3},{6,9,4,3},{11,9,4,3}, //Alpha
    {1,14,4,2},{6,14,4,2},{11,14,4,2},{16,14,4,2},{21,14,4,2},
    {1,17,4,2},{6,17,4,2},{11,17,4,2},{16,17,4,2},{21,17,4,2},
    {1,20,4,2},{6,20,4,2},{11,20,4,2},{16,20,4,2},{21,20,4,2},

    {1,23,4,2},{6,24,4,2},{11,24,4,2},{16,24,4,2},{21,23,4,2},
    {1,26,4,2},{6,27,4,2},{11,27,4,2},{16,27,4,2},{21,26,4,2},
    {1,29,4,2},{6,30,4,2},{11,30,4,2},{16,30,4,2},{21,29,4,2},
    {1,32,4,2},{6,33,4,2},{11,33,4,2},{16,33,4,2},{21,32,4,2},
    {1,35,4,2},{1,36,4,1} //On
};

void outputVRAM();
void initLCDcontroller();
void copyFrame();
int terminateLCDcontroller();
void displayFrame();

/* Replacement File IO */
uint8_t ti_Open(const char* name, const char* mode) {
    return 0;
}
uint8_t ti_Close(uint8_t handle) {
    return 0;
}
uint8_t ti_Seek(int offset, unsigned int origin, uint8_t handle) {
    return 0;
}
size_t ti_Read(void *data, size_t size, size_t count, uint8_t handle) {
    return 0;
}
/* Replacement File IO */

/* Replacement Libary Functions */

uint24_t timer_Get(uint8_t timer) {
    outputVRAM();
    double c = ( (double)clock() ) / ( (double)CLOCKS_PER_SEC ); //Time in seconds
    c *= 32768.0;
    uint32_t t = ((uint32_t)c) % 16777216;
    uint24_t g = t;
    return g;
}

const uint8_t* KEYS;
int KEYCOUNT;
enum keyCode {
    KB_Graph        , KB_Trace  , KB_Zoom   , KB_Window , KB_Yequ   , KB_2nd    , KB_Mode   , KB_Del        ,
                      KB_Sto = 9, KB_Ln     , KB_Log    , KB_Square , KB_Recip  , KB_Math   , KB_Alpha      ,
    KB_0            , KB_1      , KB_4      , KB_7      , KB_Comma  , KB_Sin    , KB_Apps   , KB_GraphVar   ,
    KB_DecPnt       , KB_2      , KB_5      , KB_8      , KB_LParen , KB_Cos    , KB_Prgm   , KB_Stat       ,
    KB_Chs          , KB_3      , KB_6      , KB_9      , KB_RParen , KB_Tan    , KB_Vars   ,
    KB_Enter = 40   , KB_Add    , KB_Sub    , KB_Mul    , KB_Div    , KB_Power  , KB_Clear  ,
    KB_Down = 48    , KB_Left   , KB_Right  , KB_Up    
};

uint8_t kb_Data[8];

enum keyBit {
    kb_Graph = 1    , kb_Trace = 2  , kb_Zoom = 4   , kb_Window = 8 , kb_Yequ = 16  , kb_2nd = 32   , kb_Mode = 64  , kb_Del = 128      ,
                      kb_Sto = 2    , kb_Ln = 4     , kb_Log = 8    , kb_Square = 16, kb_Recip = 32 , kb_Math = 64  , kb_Alpha = 128    ,
    kb_0 = 1        , kb_1 = 2      , kb_4 = 4      , kb_7 = 8      , kb_Comma = 16 , kb_Sin = 32   , kb_Apps = 64  , kb_GraphVar = 128 ,
    kb_DecPnt = 1   , kb_2 = 2      , kb_5 = 4      , kb_8 = 8      , kb_LParen = 16, kb_Cos = 32   , kb_Prgm = 64  , kb_Stat = 128     ,
    kb_Chs = 1      , kb_3 = 2      , kb_6 = 4      , kb_9 = 8      , kb_RParen = 16, kb_Tan = 32   , kb_Vars = 64  ,
    kb_Enter = 1    , kb_Add = 2    , kb_Sub = 4    , kb_Mul = 8    , kb_Div = 16   , kb_Power = 32 , kb_Clear = 64 ,
    kb_Down = 1     , kb_Left = 2   , kb_Right = 4  , kb_Up = 8
};

void setKey(uint8_t k) {
    if (k >= 64) { //Out of Bounds
        return;
    }
    uint8_t bit = 1 << (k % 8);
    uint8_t off = k / 8;
    kb_Data[off + 1] |= (bit); //+1 otherwise down becomes enter
}
void resetKey(uint8_t k) {
    if (k >= 64) { //Out of Bounds
        return;
    }
    uint8_t bit = 1 << (k % 8);
    uint8_t off = k / 8;
    kb_Data[off + 1] &= ~(bit);
}

struct keyBind {
    uint32_t SDL;
    uint8_t CE;
};

struct keyBind keyBind0[] = {
    /* Alpha Letters */
    {SDLK_a,KB_Math},{SDLK_b,KB_Apps},{SDLK_c,KB_Prgm},{SDLK_d,KB_Recip},{SDLK_e,KB_Sin},
    {SDLK_f,KB_Cos},{SDLK_g,KB_Tan},{SDLK_h,KB_Power},{SDLK_i,KB_Square},{SDLK_j,KB_Comma},
    {SDLK_k,KB_LParen},{SDLK_l,KB_RParen},{SDLK_m,KB_Div},{SDLK_n,KB_Log},{SDLK_o,KB_7},
    {SDLK_p,KB_8},{SDLK_q,KB_9},{SDLK_r,KB_Mul},{SDLK_s,KB_Ln},{SDLK_t,KB_4},{SDLK_u,KB_5},
    {SDLK_v,KB_6},{SDLK_w,KB_Sub},{SDLK_x,KB_Sto},{SDLK_y,KB_1},{SDLK_z,KB_2},
    /* Numbers */
    {SDLK_0,KB_0},{SDLK_1,KB_1},{SDLK_2,KB_2},{SDLK_3,KB_3},{SDLK_4,KB_4},
    {SDLK_5,KB_5},{SDLK_6,KB_6},{SDLK_7,KB_7},{SDLK_8,KB_8},{SDLK_9,KB_9},
    /* Keypad Numbers */
    {SDLK_KP_0,KB_0},{SDLK_KP_1,KB_1},{SDLK_KP_2,KB_2},{SDLK_KP_3,KB_3},{SDLK_KP_4,KB_4},
    {SDLK_KP_5,KB_5},{SDLK_KP_6,KB_6},{SDLK_KP_7,KB_7},{SDLK_KP_8,KB_8},{SDLK_KP_9,KB_9},
    /* Function */
    {SDLK_F1,KB_Yequ},{SDLK_F2,KB_Window},{SDLK_F3,KB_Zoom},{SDLK_F4,KB_Trace},{SDLK_F5,KB_Graph},
    /* Other */
    {SDLK_RETURN,KB_Enter},{SDLK_BACKSPACE,KB_Del},{SDLK_DELETE,KB_Del},{SDLK_CAPSLOCK,KB_Alpha},{SDLK_LSHIFT,KB_2nd},
    {SDLK_COMMA,KB_Comma},{SDLK_COLON,KB_DecPnt},{SDLK_SEMICOLON,KB_DecPnt},{SDLK_QUESTION,KB_Chs},{SDLK_CLEAR,KB_Clear},
    {SDLK_UNDERSCORE,KB_0},{SDLK_SPACE,KB_0},{SDLK_QUOTEDBL,KB_Add},{SDLK_QUOTE,KB_Add},{SDLK_PERIOD,KB_DecPnt},
    /* Math */
    {SDLK_PLUS,KB_Add},{SDLK_MINUS,KB_Sub},{SDLK_ASTERISK,KB_Mul},
    {SDLK_SLASH,KB_Div},{SDLK_CARET,KB_Power},{SDLK_EQUALS,KB_Enter},
    /* Parathesis */
    {SDLK_LEFTPAREN,KB_LParen},{SDLK_RIGHTPAREN,KB_RParen},{SDLK_LEFTBRACKET,KB_Mul},{SDLK_RIGHTBRACKET,KB_Div},
    /* Arrows */
    {SDLK_UP,KB_Up},{SDLK_DOWN,KB_Down},{SDLK_LEFT,KB_Left},{SDLK_RIGHT,KB_Right},
    /* Arbitrary */
    {SDLK_AT,KB_GraphVar},{SDLK_HASH,KB_Stat},{SDLK_DOLLAR,KB_Vars},
    {SDLK_ESCAPE,KB_Clear},{SDLK_HOME,KB_Mode},{SDLK_BACKQUOTE,KB_Mode},{SDLK_BACKQUOTE,KB_Mode}
};

struct keyBind keyBind1[] = {
    /* Alpha Letters */
    {SDL_SCANCODE_A,KB_Math},{SDL_SCANCODE_B,KB_Apps},{SDL_SCANCODE_C,KB_Prgm},{SDL_SCANCODE_D,KB_Recip},{SDL_SCANCODE_E,KB_Sin},
    {SDL_SCANCODE_F,KB_Cos},{SDL_SCANCODE_G,KB_Tan},{SDL_SCANCODE_H,KB_Power},{SDL_SCANCODE_I,KB_Square},{SDL_SCANCODE_J,KB_Comma},
    {SDL_SCANCODE_K,KB_LParen},{SDL_SCANCODE_L,KB_RParen},{SDL_SCANCODE_M,KB_Div},{SDL_SCANCODE_N,KB_Log},{SDL_SCANCODE_O,KB_7},
    {SDL_SCANCODE_P,KB_8},{SDL_SCANCODE_Q,KB_9},{SDL_SCANCODE_R,KB_Mul},{SDL_SCANCODE_S,KB_Ln},{SDL_SCANCODE_T,KB_4},{SDL_SCANCODE_U,KB_5},
    {SDL_SCANCODE_V,KB_6},{SDL_SCANCODE_W,KB_Sub},{SDL_SCANCODE_X,KB_Sto},{SDL_SCANCODE_Y,KB_1},{SDL_SCANCODE_Z,KB_2},
    /* Numbers */
    {SDL_SCANCODE_0,KB_0},{SDL_SCANCODE_1,KB_1},{SDL_SCANCODE_2,KB_2},{SDL_SCANCODE_3,KB_3},{SDL_SCANCODE_4,KB_4},
    {SDL_SCANCODE_5,KB_5},{SDL_SCANCODE_6,KB_6},{SDL_SCANCODE_7,KB_7},{SDL_SCANCODE_8,KB_8},{SDL_SCANCODE_9,KB_9},
    /* Keypad Numbers */
    {SDL_SCANCODE_KP_0,KB_0},{SDL_SCANCODE_KP_1,KB_1},{SDL_SCANCODE_KP_2,KB_2},{SDL_SCANCODE_KP_3,KB_3},{SDL_SCANCODE_KP_4,KB_4},
    {SDL_SCANCODE_KP_5,KB_5},{SDL_SCANCODE_KP_6,KB_6},{SDL_SCANCODE_KP_7,KB_7},{SDL_SCANCODE_KP_8,KB_8},{SDL_SCANCODE_KP_9,KB_9},
    /* Function */
    {SDL_SCANCODE_F1,KB_Yequ},{SDL_SCANCODE_F2,KB_Window},{SDL_SCANCODE_F3,KB_Zoom},{SDL_SCANCODE_F4,KB_Trace},{SDL_SCANCODE_F5,KB_Graph},
    /* Other */
    {SDL_SCANCODE_RETURN,KB_Enter},{SDL_SCANCODE_BACKSPACE,KB_Del},{SDL_SCANCODE_DELETE,KB_Del},{SDL_SCANCODE_CAPSLOCK,KB_Alpha},{SDL_SCANCODE_LSHIFT,KB_2nd},
    {SDL_SCANCODE_COMMA,KB_Comma},{SDL_SCANCODE_SEMICOLON,KB_DecPnt},
    {SDL_SCANCODE_SPACE,KB_0},{SDL_SCANCODE_APOSTROPHE,KB_Add},{SDL_SCANCODE_PERIOD,KB_DecPnt},
    /* Math */
    {SDL_SCANCODE_EQUALS,KB_Enter},{SDL_SCANCODE_KP_ENTER,KB_Enter},
    {SDL_SCANCODE_KP_PLUS,KB_Add},{SDL_SCANCODE_KP_MINUS,KB_Sub},{SDL_SCANCODE_KP_MULTIPLY,KB_Mul},{SDL_SCANCODE_KP_DIVIDE,KB_Div},{SDL_SCANCODE_KP_DECIMAL,KB_DecPnt},
    /* Parathesis */
    {SDL_SCANCODE_LEFTBRACKET,KB_Mul},{SDL_SCANCODE_RIGHTBRACKET,KB_Div},
    /* Arrows */
    {SDL_SCANCODE_UP,KB_Up},{SDL_SCANCODE_DOWN,KB_Down},{SDL_SCANCODE_LEFT,KB_Left},{SDL_SCANCODE_RIGHT,KB_Right},
    /* Arbitrary */
    {SDL_SCANCODE_ESCAPE,KB_Clear},{SDL_SCANCODE_HOME,KB_Mode},{SDL_SCANCODE_GRAVE,KB_Mode}
};
struct keyBind keyBind2[] = { //WASD
    /* Keypad Numbers */
    {SDL_SCANCODE_KP_0,KB_0},{SDL_SCANCODE_KP_1,KB_1},{SDL_SCANCODE_KP_2,KB_2},{SDL_SCANCODE_KP_3,KB_3},{SDL_SCANCODE_KP_4,KB_4},
    {SDL_SCANCODE_KP_5,KB_5},{SDL_SCANCODE_KP_6,KB_6},{SDL_SCANCODE_KP_7,KB_7},{SDL_SCANCODE_KP_8,KB_8},{SDL_SCANCODE_KP_9,KB_9},
    /* Arrows */
    {SDL_SCANCODE_W,KB_Up},{SDL_SCANCODE_S,KB_Down},{SDL_SCANCODE_A,KB_Left},{SDL_SCANCODE_D,KB_Right},
    {SDL_SCANCODE_UP,KB_Up},{SDL_SCANCODE_DOWN,KB_Down},{SDL_SCANCODE_LEFT,KB_Left},{SDL_SCANCODE_RIGHT,KB_Right},
    /* Primary */
    {SDL_SCANCODE_E,KB_Alpha},{SDL_SCANCODE_Q,KB_2nd},{SDL_SCANCODE_RETURN,KB_Enter},
    /* Other */
    {SDL_SCANCODE_Z,KB_Yequ},
    {SDL_SCANCODE_LSHIFT,KB_GraphVar},
    {SDL_SCANCODE_X,KB_Mode},
    {SDL_SCANCODE_C,KB_Power},
    {SDL_SCANCODE_P,KB_Del},
};

void kb_Reset() {
    for (uint8_t i = 0; i < 7; i++) {
        kb_Data[i] = 0;
    }
}



/* Replacement Libary Functions */
uint8_t tempKey[56]; //Allows for the same key to be binded to more than one thing
void kb_Scan() { 
    SDL_PollEvent(&event);
    KEYS = SDL_GetKeyboardState(&KEYCOUNT);
    uint32_t length = sizeof(keyBindSelection)/sizeof(keyBindSelection[0]);
    for (uint32_t i = 0; i < length; i++) {
        if (KEYS[keyBindSelection[i].SDL] == 1) {
            //printf("%s\n",SDL_GetKeyName(keyBindSelection[i].SDL));
            //printf("%d %d,",q,keyBindSelection[i].CE); fflush(stdout);
            setKey(keyBindSelection[i].CE);
            tempKey[keyBindSelection[i].CE] = 1;
        }
    }
    for (uint8_t i = 0; i < 56; i++) {
        if (tempKey[i] == 0) {
            resetKey(i);
        }
        tempKey[i] = 0;
    }
}

void panFrame() {
    uint32_t lcdBase = 0xD00000 | (*frameBase & 0x7FFF8);
    if (lcdBase > 0xD65800 || lcdBase < 0xD40000 - (resX * resY)) {
        for (u32 r = 0; r < 153600; r++) {
            videoCopy[r] = 0x00;
        }
        return;
    }
    if (lcdBase == 0xD40000) { //Fast Case
        for (u32 r = 0; r < 153600; r++) {
            videoCopy[r] = _VRAM[r];
        }
    } else if (lcdBase < 0xD40000) { //Above
        u32 dif = 0xD40000 - lcdBase;
        for (u32 r = 0; r < dif; r++) {
            videoCopy[r] = 0x00;
        }
        for (u32 r = 0; r < 153600 - dif; r++) {
            if (r + dif >= 0 && r + dif < 153600 - 1) {
                videoCopy[r + dif] = _VRAM[r];
            } else {
                videoCopy[r + dif] = 0x00;
            }
        }
    } else if (lcdBase > 0xD40000) { //Below
        u32 dif = lcdBase - 0xD40000;
        for (u32 r = 0; r < 153600 - dif; r++) {
            if (r + dif >= 0 && r + dif < 153600 - 1) {
                videoCopy[r] = _VRAM[r + dif];
            } else {
                videoCopy[r] = 0x00;
            }
        }
        for (u32 r = 153600 - dif; r < 153600; r++) {
            videoCopy[r] = 0x00;
        }
    }
}

void outputVRAM() {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
        exit(0);
    }

    //printf("%X,%X,%X\n",*frameBase,0xD40000,dif); fflush(stdout);
    panFrame();
    
    for (u16 s = 0; s < 256; s++) {
        color16[s] = _paletteRAM[s];
    }

    displayFrame();
}

void initLCDcontroller() {
    SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Super-Sweeper Windows Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX * scale, resY * scale,0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    buffer = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_STREAMING, resX * scale, resY * scale);
}
//#define videoCopyArray uint8_t c = ((uint8_t*)VRAM)[z]
#define videoCopyArray uint8_t c = videoCopy[z]

void blit16bpp(uint8_t* data) {
    return; //Real time conversion will be painful
}
void blit8bpp(uint8_t* data) {
    if (scale == 1) {
        uint32_t w = 0;
        uint32_t z = 0;
        for (uint32_t y = 0; y < resY; y++) {
            for (uint32_t x = 0; x < resX; x++) {
                videoCopyArray;
                data[w] = colorR[c]; w++;
                data[w] = colorG[c]; w++;
                data[w] = colorB[c]; w++;
                z++;
            }
        }
    } else {
        uint32_t w = 0;
        uint32_t z = 0;
        for (uint32_t y = 0; y < resY; y++) {
            for (uint8_t v = 0; v < scale; v++) {
                for (uint32_t x = 0; x < resX; x++) {
                    videoCopyArray;
                    for (uint8_t u = 0; u < scale; u++) {
                        data[w] = colorR[c]; w++;
                        data[w] = colorG[c]; w++;
                        data[w] = colorB[c]; w++;
                    }
                    z++;
                }
                z -= 320;
            }
            z += 320;
        }
    }
}
void blit4bpp(uint8_t* data) {
    if (scale == 1) {
        uint32_t w = 0;
        uint32_t z = 0;
        for (uint32_t y = 0; y < resY; y++) {
            for (uint32_t x = 0; x < resX / 2; x++) {
                videoCopyArray;
                data[w] = colorR[c & 15]; w++;
                data[w] = colorG[c & 15]; w++;
                data[w] = colorB[c & 15]; w++;
                data[w] = colorR[(c >> 4) & 15]; w++;
                data[w] = colorG[(c >> 4) & 15]; w++;
                data[w] = colorB[(c >> 4) & 15]; w++;
                z++;
            }
        }
    } else {
        uint32_t w = 0;
        uint32_t z = 0;
        for (uint32_t y = 0; y < resY; y++) {
            for (uint8_t v = 0; v < scale; v++) {
                for (uint32_t x = 0; x < resX / 2; x++) {
                    videoCopyArray;
                    for (uint8_t u = 0; u < scale; u++) {
                        data[w] = colorR[c & 15]; w++;
                        data[w] = colorG[c & 15]; w++;
                        data[w] = colorB[c & 15]; w++;
                        data[w] = colorR[(c >> 4) & 15]; w++;
                        data[w] = colorG[(c >> 4) & 15]; w++;
                        data[w] = colorB[(c >> 4) & 15]; w++;
                    }
                    z++;
                }
                z -= 160;
            }
            z += 160;
        }
    }
}

uint8_t darkMode = 0;
void copyFrame(uint8_t* data) {
    if (data == NULL) {
        printf("ERROR | Buffer Pointer is Void \n"); fflush(stdout);
    }

    if (_videoMode & 0x100) {
        //Converts 1555 to 888 Color
        for (uint32_t i = 0; i < 256; i++) {
            uint16_t col = paletteRAM[i];
            colorB[i] = (col & 31) << 3;
            col >>= 5;
            colorG[i] = col & 1024 ? 4 : 0;
            colorG[i] += (col & 31) << 3;
            col >>= 5;
            colorR[i] = (col & 31) << 3;
        }
        //Scales color (Otherwise white is 248,252,248)
        for (uint32_t i = 0; i < 256; i++) { //Magic Numbers: 35,84 Floor 32,64 Round
            colorB[i] += (colorB[i] / 32);
            colorG[i] += (colorG[i] / 64);
            colorR[i] += (colorR[i] / 32);
        }
    } else {
        //Converts 1555 to 888 Color
        for (uint32_t i = 0; i < 256; i++) {
            uint16_t col = paletteRAM[i];
            colorR[i] = (col & 31) << 3;
            col >>= 5;
            colorG[i] = col & 1024 ? 4 : 0;
            colorG[i] += (col & 31) << 3;
            col >>= 5;
            colorB[i] = (col & 31) << 3;
        }
        //Scales color (Otherwise white is 248,252,248)
        for (uint32_t i = 0; i < 256; i++) { //Magic Numbers: 35,84 Floor 32,64 Round
            colorR[i] += (colorB[i] / 32);
            colorG[i] += (colorG[i] / 64);
            colorB[i] += (colorR[i] / 32);
        }
    }
    if (darkMode) {
        for (uint32_t i = 0; i < 256; i++) {
            colorB[i] ^= 0xFF;
            colorG[i] ^= 0xFF;
            colorR[i] ^= 0xFF;
        }
    }
    if ((*videoMode & 0xF) == 0x5) {
        blit4bpp(data);
    }
    if ((*videoMode & 0xF) == 0x7) {
        blit8bpp(data);
    }
    if ((*videoMode & 0xF) == 0xD) {
        blit16bpp(data);
    }
}

int terminateLCDcontroller() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void displayFrame() { 
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
        terminateLCDcontroller();
        exit(0);
    }

    uint8_t *frame = NULL;

    SDL_LockTexture(buffer,NULL,(void **) &frame,&pitch);

    copyFrame(frame);
    
    SDL_UnlockTexture(buffer);
    SDL_RenderCopy(renderer, buffer, NULL, NULL);

    SDL_RenderPresent(renderer);
}

#endif /* X86RENDER_H */