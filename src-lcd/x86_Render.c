/*
**	Author: zerico2005 (2023-2024)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

//#include "global.h"

#include "x86_Common_Def.h"
#include "x86_Render.h"
#include "x86_ti84ce.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// Integer Scaling
uint8_t scale = 2;

uint8_t darkMode = 0;
bool useMouseInGame = true;

bool columnMajorMode = false;

int32_t RESX_MINIMUM = LCD_RESX;
int32_t RESY_MINIMUM = LCD_RESY;
int32_t RESX_MAXIMUM = LCD_RESX * 32;
int32_t RESY_MAXIMUM = LCD_RESY * 32;

int32_t LCD_RESU = LCD_RESX; 
int32_t LCD_RESV = LCD_RESY;

uint8_t PreCalc_RGB1555[65536 * 3];
uint8_t PreCalc_BGR1555[65536 * 3];
uint8_t PreCalc_RGB565[65536 * 3];
uint8_t PreCalc_BGR565[65536 * 3];
uint8_t PreCalc_RGB555[65536 * 3];
uint8_t PreCalc_BGR555[65536 * 3];
uint8_t PreCalc_RGB444[65536 * 3];
uint8_t PreCalc_BGR444[65536 * 3];

void Calculate16BitColor() {
	{ // 1555
		size_t z = 0;
		for (uint32_t i = 0; i < 65536; i++) {
			uint16_t c = (uint16_t)i;
			uint8_t r = (uint8_t)(c & 0x1F);
			uint8_t g = (uint8_t)((c & 0x3E0) >> 4) + ((c & 0x8000) ? 1 : 0);
			uint8_t b = (uint8_t)((c & 0x7C00) >> 10);
			r *= 8; g *= 4; b *= 8;
			r += r / 32;
			g += g / 64;
			b += b / 32;
			PreCalc_RGB1555[z] = r; PreCalc_BGR1555[z] = b; z++;
			PreCalc_RGB1555[z] = g; PreCalc_BGR1555[z] = g; z++;
			PreCalc_RGB1555[z] = b; PreCalc_BGR1555[z] = r; z++;
		}
	}
	{ // 565
		size_t z = 0;
		for (uint32_t i = 0; i < 65536; i++) {
			uint16_t c = (uint16_t)i;
			uint8_t r = (uint8_t)(c & 0x1F);
			uint8_t g = (uint8_t)((c & 0x7E0) >> 4);
			uint8_t b = (uint8_t)((c & 0xF800) >> 11);
			r *= 8; g *= 4; b *= 8;
			r += r / 32;
			g += g / 64;
			b += b / 32;
			PreCalc_RGB565[z] = r; PreCalc_BGR565[z] = b; z++;
			PreCalc_RGB565[z] = g; PreCalc_BGR565[z] = g; z++;
			PreCalc_RGB565[z] = b; PreCalc_BGR565[z] = r; z++;
		}
	}
	{ // 555
		size_t z = 0;
		for (uint32_t i = 0; i < 65536; i++) {
			uint16_t c = (uint16_t)i;
			uint8_t r = (uint8_t)(c & 0x1F);
			uint8_t g = (uint8_t)((c & 0x3E0) >> 5);
			uint8_t b = (uint8_t)((c & 0x7C00) >> 10);
			r *= 8; g *= 8; b *= 8;
			r += r / 32;
			g += g / 32;
			b += b / 32;
			PreCalc_RGB555[z] = r; PreCalc_BGR555[z] = b; z++;
			PreCalc_RGB555[z] = g; PreCalc_BGR555[z] = g; z++;
			PreCalc_RGB555[z] = b; PreCalc_BGR555[z] = r; z++;
		}
	}
	{ // 444
		size_t z = 0;
		for (uint32_t i = 0; i < 65536; i++) {
			uint16_t c = (uint16_t)i;
			uint8_t r = (uint8_t)(c & 0xF);
			uint8_t g = (uint8_t)((c & 0xF0) >> 4);
			uint8_t b = (uint8_t)((c & 0xF00) >> 8);
			r *= 16; g *= 16; b *= 16;
			r += r / 16;
			g += g / 16;
			b += b / 16;
			PreCalc_RGB444[z] = r; PreCalc_BGR444[z] = b; z++;
			PreCalc_RGB444[z] = g; PreCalc_BGR444[z] = g; z++;
			PreCalc_RGB444[z] = b; PreCalc_BGR444[z] = r; z++;
		}
	}
}

/* Modern Code */

struct BufferBox {
	uint8_t* vram;
	int32_t resX;
	int32_t resY;
	size_t pitch;
}; typedef struct BufferBox BufferBox;

BufferBox Master;

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Texture* texture;

/* Mouse Handling */
	uint32_t getMouseState(int32_t* posX, int32_t* posY) {
		int32_t x;
		int32_t y;
		uint32_t state = SDL_GetMouseState(&x,&y);
		x = (x * LCD_RESX) / Master.resX;
		y = (y * LCD_RESY) / Master.resY;
		if (posX != NULL) { *posX = x; }
		if (posY != NULL) { *posY = y; }
		return state;
	}

/* Row and Column Major */

void resetResolutionValues(int32_t resU, int32_t resV) {
	LCD_RESU = resU;
	LCD_RESV = resV;
	RESX_MINIMUM = resU;
	RESY_MINIMUM = resV;
	RESX_MAXIMUM = resU * 32;
	RESY_MAXIMUM = resV * 32;
	SDL_SetWindowMinimumSize(window, RESX_MINIMUM, RESY_MINIMUM);
	SDL_SetWindowMaximumSize(window, RESX_MAXIMUM, RESY_MAXIMUM);
}

void internal_SPI_Row_Major() {
	columnMajorMode = false;
	// resetResolutionValues(LCD_RESX,LCD_RESY);
	// resizeWindow(Master.resX,Master.resY,NULL,NULL);
}

void internal_SPI_Column_Major() {
	columnMajorMode = true;
	// resetResolutionValues(LCD_RESY,LCD_RESX);
	// resizeWindow(Master.resY,Master.resX,NULL,NULL);
}

/* Pointers */

uint8_t _VRAM[153600];
void* VRAM = _VRAM + 0;
void* WRAM = _VRAM + 76800;
void* XRAM = _VRAM + 153600;

uint16_t paletteRAM[256];

volatile uint16_t _videoMode = 0x92D;
volatile uint16_t* videoMode = &_videoMode;

/* Pointers */

SDL_Event* grab_SDL2_event() {
	return &event;
}

int32_t pitch = LCD_RESX * 3;

uint8_t videoCopy[153600];
uint16_t color16[256];
uint8_t colorR[256];
uint8_t colorG[256];
uint8_t colorB[256];

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

void displayFrame();

/* Replacement File IO */

/* Replacement File IO */

/* Replacement Libary Functions */

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

// enum keyBit {
//     kb_Graph = 1    , kb_Trace = 2  , kb_Zoom = 4   , kb_Window = 8 , kb_Yequ = 16  , kb_2nd = 32   , kb_Mode = 64  , kb_Del = 128      ,
//                       kb_Sto = 2    , kb_Ln = 4     , kb_Log = 8    , kb_Square = 16, kb_Recip = 32 , kb_Math = 64  , kb_Alpha = 128    ,
//     kb_0 = 1        , kb_1 = 2      , kb_4 = 4      , kb_7 = 8      , kb_Comma = 16 , kb_Sin = 32   , kb_Apps = 64  , kb_GraphVar = 128 ,
//     kb_DecPnt = 1   , kb_2 = 2      , kb_5 = 4      , kb_8 = 8      , kb_LParen = 16, kb_Cos = 32   , kb_Prgm = 64  , kb_Stat = 128     ,
//     kb_Chs = 1      , kb_3 = 2      , kb_6 = 4      , kb_9 = 8      , kb_RParen = 16, kb_Tan = 32   , kb_Vars = 64  ,
//     kb_Enter = 1    , kb_Add = 2    , kb_Sub = 4    , kb_Mul = 8    , kb_Div = 16   , kb_Power = 32 , kb_Clear = 64 ,
//     kb_Down = 1     , kb_Left = 2   , kb_Right = 4  , kb_Up = 8
// };

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
	{SDL_SCANCODE_0,KB_0},{SDL_SCANCODE_1,KB_1},{SDL_SCANCODE_2,KB_2},{SDL_SCANCODE_3,KB_3},{SDL_SCANCODE_4,KB_4},
    {SDL_SCANCODE_5,KB_5},{SDL_SCANCODE_6,KB_6},{SDL_SCANCODE_7,KB_7},{SDL_SCANCODE_8,KB_8},{SDL_SCANCODE_9,KB_9},
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

void internal_kb_Reset() {
    for (uint8_t i = 0; i < 7; i++) {
        kb_Data[i] = 0;
    }
}

/* Replacement Libary Functions */
uint8_t tempKey[56]; //Allows for the same key to be binded to more than one thing
void internal_kb_Scan() { 
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

void renderCursor(uint8_t* data) {
	size_t posX = lcd_CrsrX;
	size_t posY = lcd_CrsrY;
	for (size_t i = 0; i < lcd_CrsrImageLen64; i++) {

	}
}

void blit16bpp(uint8_t* data) {
	uint8_t* PreCalc16;
	uint8_t colorMode = (lcd_VideoMode & 0b1110) >> 1;
	switch (colorMode) {
		case 0b100:
			PreCalc16 = (lcd_VideoMode & 0x100) ? PreCalc_BGR1555 : PreCalc_RGB1555;
		break;
		case 0b110:
			PreCalc16 = (lcd_VideoMode & 0x100) ? PreCalc_BGR565 : PreCalc_RGB565;
		break;
		case 0b111:
			PreCalc16 = (lcd_VideoMode & 0x100) ? PreCalc_BGR444 : PreCalc_RGB444;
		break;
		default:
			PreCalc16 = (lcd_VideoMode & 0x100) ? PreCalc_BGR555 : PreCalc_RGB555;
	};
	size_t w = 0;
	size_t z = 0;
	for (uint32_t y = 0; y < LCD_RESY; y++) {
		for (uint32_t x = 0; x < LCD_RESX; x++) {
			uint32_t c = (uint32_t)((uint16_t*)videoCopy)[z];
			c *= 3;
			uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
			for (uint8_t s = 0; s < lenX; s++) {
				data[w] = PreCalc16[c]; w++;
				data[w] = PreCalc16[c + 1]; w++;
				data[w] = PreCalc16[c + 2]; w++;
			}
			z += columnMajorMode ? LCD_RESY : 1;
		}
		z -= columnMajorMode ? ((LCD_RESX * LCD_RESY) - 1) : 0;
		uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * y) / LCD_RESY);
		//w += Master.pitch - (LCD_RESX * lenY * 3);
		for (uint8_t s = 0; s < lenY - 1; s++) {
			memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
			w += Master.pitch;
		}
	}
}

void blit8bpp(uint8_t* data) {
	size_t w = 0;
	size_t z = 0;
	for (uint32_t y = 0; y < (uint32_t)LCD_RESY; y++) {
		for (uint32_t x = 0; x < (uint32_t)LCD_RESX; x++) {
			uint8_t c = videoCopy[z];
			uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
			for (uint8_t s = 0; s < lenX; s++) {
				data[w] = colorR[c]; w++;
				data[w] = colorG[c]; w++;
				data[w] = colorB[c]; w++;
			}
			z += columnMajorMode ? LCD_RESY : 1;
		}
		z -= columnMajorMode ? ((LCD_RESX * LCD_RESY) - 1) : 0;
		uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * y) / LCD_RESY);
		//w += Master.pitch - (LCD_RESX * lenY * 3);
		for (uint8_t s = 0; s < lenY - 1; s++) {
			memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
			w += Master.pitch;
		}
	}
}

void blit4bpp(uint8_t* data) {
	const uint32_t PixelsPerByte = 2;
	size_t w = 0;
	size_t z = 0;
	if (columnMajorMode == false) {
		for (uint32_t y = 0; y < LCD_RESY; y++) {
			for (uint32_t x = 0; x < LCD_RESX / PixelsPerByte; x++) {
				uint8_t c = videoCopy[z];
				uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
				for (uint8_t s = 0; s < lenX; s++) {
					data[w] = colorR[c & 0xF]; w++;
					data[w] = colorG[c & 0xF]; w++;
					data[w] = colorB[c & 0xF]; w++;
					data[w] = colorR[(c >> 4) & 0xF]; w++;
					data[w] = colorG[(c >> 4) & 0xF]; w++;
					data[w] = colorB[(c >> 4) & 0xF]; w++;
				}
				z++;
			}
			uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * y) / LCD_RESY);
			//w += Master.pitch - (LCD_RESX * lenY * 3);
			for (uint8_t s = 0; s < lenY - 1; s++) {
				memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
				w += Master.pitch;
			}
		}
	} else {
		for (uint32_t x = 0; x < LCD_RESX; x++) {
			uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
			for (uint32_t y = 0; y < LCD_RESY; y += PixelsPerByte) {
				uint8_t c = videoCopy[z];
				for (uint32_t i = 0; i < PixelsPerByte; i++) {
					uint8_t lenY = ((Master.resY * (y + i + 1)) / LCD_RESY) - ((Master.resY * (y + i)) / LCD_RESY);
					for (uint32_t s = 0; s < lenX; s++) {
						data[w] = colorR[c & 0xF]; w++;
						data[w] = colorG[c & 0xF]; w++;
						data[w] = colorB[c & 0xF]; w++;
					}
					w += (Master.pitch - (3 * lenX));
					w += (Master.pitch * (lenY - 1));
					c >>= 4;
				}
				z++;
			}
			w -= Master.pitch * Master.resY;
			w += (3 * lenX);
		}
		// memcpy's lines
		w = 0;
		for (uint32_t y = 0; y < LCD_RESY; y++) {
			w += Master.pitch;
			uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * (y)) / LCD_RESY);
			for (uint8_t s = 0; s < lenY - 1; s++) {
				memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
				w += Master.pitch;
			}
		}
	}
}

void blit2bpp(uint8_t* data) {
	const uint32_t PixelsPerByte = 4;
	size_t w = 0;
	size_t z = 0;
	if (columnMajorMode == false) {
		for (uint32_t y = 0; y < LCD_RESY; y++) {
			for (uint32_t x = 0; x < LCD_RESX / PixelsPerByte; x++) {
				uint8_t c = videoCopy[z];
				uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
				for (uint8_t s = 0; s < lenX; s++) {
					data[w] = colorR[c & 0x3]; w++;
					data[w] = colorG[c & 0x3]; w++;
					data[w] = colorB[c & 0x3]; w++;
					data[w] = colorR[(c >> 2) & 0x3]; w++;
					data[w] = colorG[(c >> 2) & 0x3]; w++;
					data[w] = colorB[(c >> 2) & 0x3]; w++;
					data[w] = colorR[(c >> 4) & 0x3]; w++;
					data[w] = colorG[(c >> 4) & 0x3]; w++;
					data[w] = colorB[(c >> 4) & 0x3]; w++;
					data[w] = colorR[(c >> 6) & 0x3]; w++;
					data[w] = colorG[(c >> 6) & 0x3]; w++;
					data[w] = colorB[(c >> 6) & 0x3]; w++;
				}
				z++;
			}
			uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * y) / LCD_RESY);
			//w += Master.pitch - (LCD_RESX * lenY * 3);
			for (uint8_t s = 0; s < lenY - 1; s++) {
				memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
				w += Master.pitch;
			}
		}
	} else {
		for (uint32_t x = 0; x < LCD_RESX; x++) {
			uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
			for (uint32_t y = 0; y < LCD_RESY; y += PixelsPerByte) {
				uint8_t c = videoCopy[z];
				for (uint32_t i = 0; i < PixelsPerByte; i++) {
					uint8_t lenY = ((Master.resY * (y + i + 1)) / LCD_RESY) - ((Master.resY * (y + i)) / LCD_RESY);
					for (uint32_t s = 0; s < lenX; s++) {
						data[w] = colorR[c & 0x3]; w++;
						data[w] = colorG[c & 0x3]; w++;
						data[w] = colorB[c & 0x3]; w++;
					}
					w += (Master.pitch - (3 * lenX));
					w += (Master.pitch * (lenY - 1));
					c >>= 2;
				}
				z++;
			}
			w -= Master.pitch * Master.resY;
			w += (3 * lenX);
		}
		// memcpy's lines
		w = 0;
		for (uint32_t y = 0; y < LCD_RESY; y++) {
			w += Master.pitch;
			uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * (y)) / LCD_RESY);
			for (uint8_t s = 0; s < lenY - 1; s++) {
				memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
				w += Master.pitch;
			}
		}
	}
}

void blit1bpp(uint8_t* data) {
	const uint32_t PixelsPerByte = 8;
	size_t w = 0;
	size_t z = 0;
	if (columnMajorMode == false) {
		for (uint32_t y = 0; y < LCD_RESY; y++) {
			for (uint32_t x = 0; x < LCD_RESX / PixelsPerByte; x++) {
				uint8_t c = videoCopy[z];
				uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
				for (uint8_t s = 0; s < lenX; s++) {
					for (uint8_t b = 0; b < 8; b++) {
						data[w] = colorR[(c >> b) & 0x1]; w++;
						data[w] = colorG[(c >> b) & 0x1]; w++;
						data[w] = colorB[(c >> b) & 0x1]; w++;
					}
				}
				z++;
			}
			uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * y) / LCD_RESY);
			//w += Master.pitch - (LCD_RESX * lenY * 3);
			for (uint8_t s = 0; s < lenY - 1; s++) {
				memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
				w += Master.pitch;
			}
		}
	} else {
		for (uint32_t x = 0; x < LCD_RESX; x++) {
			uint8_t lenX = ((Master.resX * (x + 1)) / LCD_RESX) - ((Master.resX * x) / LCD_RESX);
			for (uint32_t y = 0; y < LCD_RESY; y += PixelsPerByte) {
				uint8_t c = videoCopy[z];
				for (uint32_t i = 0; i < PixelsPerByte; i++) {
					uint8_t lenY = ((Master.resY * (y + i + 1)) / LCD_RESY) - ((Master.resY * (y + i)) / LCD_RESY);
					for (uint32_t s = 0; s < lenX; s++) {
						data[w] = colorR[c & 0x1]; w++;
						data[w] = colorG[c & 0x1]; w++;
						data[w] = colorB[c & 0x1]; w++;
					}
					w += (Master.pitch - (3 * lenX));
					w += (Master.pitch * (lenY - 1));
					c >>= 1;
				}
				z++;
			}
			w -= Master.pitch * Master.resY;
			w += (3 * lenX);
		}
		// memcpy's lines
		w = 0;
		for (uint32_t y = 0; y < LCD_RESY; y++) {
			w += Master.pitch;
			uint8_t lenY = ((Master.resY * (y + 1)) / LCD_RESY) - ((Master.resY * (y)) / LCD_RESY);
			for (uint8_t s = 0; s < lenY - 1; s++) {
				memcpy(&data[w],&data[w - Master.pitch],Master.pitch);
				w += Master.pitch;
			}
		}
	}
}

void copyFrame(uint8_t* data) {
    if (data == NULL) {
        printf("ERROR | Buffer Pointer is Void \n"); fflush(stdout);
    }
	memcpy(color16,lcd_Palette,256 * sizeof(uint16_t));
	memcpy(paletteRAM,lcd_Palette,256 * sizeof(uint16_t));
	size_t copyAmount = 0;
	uint8_t colorMode = (lcd_VideoMode & 0b1110) >> 1;
	switch (colorMode) {
		case 0b000: // 1bpp
			copyAmount = (LCD_RESX * LCD_RESY) / 8;
		break;
		case 0b001: // 2bpp
			copyAmount = (LCD_RESX * LCD_RESY) / 4;
		break;
		case 0b010: // 4bpp
			copyAmount = (LCD_RESX * LCD_RESY) / 2;
		break;
		case 0b011: // 8bpp
			copyAmount = (LCD_RESX * LCD_RESY);
		break;
		case 0b100: // 16bpp
			copyAmount = (LCD_RESX * LCD_RESY) * 2;
		break;
		case 0b110: // 16bpp
			copyAmount = (LCD_RESX * LCD_RESY) * 2;
		break;
		case 0b111: // 16bpp
			copyAmount = (LCD_RESX * LCD_RESY) * 2;
		break;
		default:
			copyAmount = (LCD_RESX * LCD_RESY) * 2;
	};

	memcpy(videoCopy,((uint8_t*)&simulated_ram[0xD00000 | (lcd_UpBase & 0x7FFF8)]),copyAmount);
    if (lcd_VideoMode & 0x100) {
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
	switch (colorMode) {
		case 0b000:
			blit1bpp(data);
		break;
		case 0b001:
			blit2bpp(data);
		break;
		case 0b010:
			blit4bpp(data);
		break;
		case 0b011:
			blit8bpp(data);
		break;
		case 0b100:
			blit16bpp(data);
		break;
		case 0b110:
			blit16bpp(data);
		break;
		case 0b111:
			blit16bpp(data);
		break;
		default:
			blit16bpp(data);
	};
    if ((lcd_VideoMode & 0xF) == 0x5) {
        blit4bpp(data);
    }
    if ((lcd_VideoMode & 0xF) == 0x7) {
        blit8bpp(data);
    }
    if ((lcd_VideoMode & 0xF) == 0xD) {
        blit16bpp(data);
    }
}

/*
**	===========
**	Modern Code
**	===========
*/

int terminateLCDcontroller() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void initLCDcontroller(const char* windowTitle) {
	Master.resX = LCD_RESX * scale;
	Master.resY = LCD_RESY * scale;
	Master.vram = NULL;
	Master.pitch = Master.resX * 3;
	Master.vram = calloc((size_t)Master.resY * Master.pitch, sizeof(uint8_t));
	if (Master.vram == NULL) { printf("\nMaster.vram is NULL"); fflush(stdout); return; }
    SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LCD_RESX * scale, LCD_RESY * scale,SDL_WINDOW_RESIZABLE);
    SDL_SetWindowMinimumSize(window, RESX_MINIMUM, RESY_MINIMUM);
	SDL_SetWindowMaximumSize(window, RESX_MAXIMUM, RESY_MAXIMUM);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_STREAMING, LCD_RESX * scale, LCD_RESY * scale);
	Calculate16BitColor();
}

// Returns True if the window was resized. Optional: Returns new window size.
bool resizeWindow(int32_t resX, int32_t resY, uint32_t* resizeX, uint32_t* resizeY) {
	bool reVal = false;
	static int32_t rX = 0, rY = 0;
	if (rX != resX || rY != resY) {
		valueLimit(resX,RESX_MINIMUM,RESX_MAXIMUM);
		valueLimit(resY,RESY_MINIMUM,RESY_MAXIMUM);

		if (resX & 0x3) { resX = resX & ~0x3; }

		// const fp64 MaximumAspectRatio = 1.35;
		// fp64 aspectRatio = ((fp64)resX / (fp64)LCD_RESX) / ((fp64)resY / (fp64)LCD_RESY);
		// if (aspectRatio > MaximumAspectRatio) {
		// 	resX = (int32_t)(MaximumAspectRatio * ((fp64)resY / (fp64)LCD_RESY) * (fp64)LCD_RESX);
		// } else if (aspectRatio < 1.0 / MaximumAspectRatio) {
		// 	resY = (int32_t)(MaximumAspectRatio * ((fp64)resX / (fp64)LCD_RESX) * (fp64)LCD_RESY);
		// }

		fp64 scaleVal = MIN((fp64)resX / (fp64)LCD_RESX,(fp64)resY / (fp64)LCD_RESY);
		resX = (int32_t)(scaleVal * (fp64)LCD_RESX);
		resY = (int32_t)(scaleVal * (fp64)LCD_RESY);

		// Sets resX to a multiple of 4 so I don't have to deal with padded and unpadded image buffers
		if (resX & 0x3) { resX = resX & ~0x3; }

		// scale = MIN(resX / LCD_RESX, resY / LCD_RESY);
		// resX = LCD_RESX * scale;
		// resY = LCD_RESY * scale;

		Master.resX = resX;
		Master.resY = resY;
		Master.pitch = Master.resX * 3;
		Master.vram = (uint8_t*)realloc((void*)(Master.vram),Master.pitch * Master.resY);
		if (Master.vram == NULL) {
			if (texture == NULL) {
				printf("\nError: realloc Master.vram failed while resizing window");
				FREE(Master.vram);
				terminateLCDcontroller();
				return true;
			}
		}
		SDL_SetWindowSize(window,resX,resY);
		SDL_RenderSetLogicalSize(renderer, resX, resY);
		if (resizeX != NULL) { *resizeX = resX; }
		if (resizeY != NULL) { *resizeY = resY; }
		if (texture != NULL) {
			SDL_DestroyTexture(texture);
		}
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, (int)Master.resX, (int)Master.resY);
		if (texture == NULL) {
			printf("\nError: SDL_CreateTexture failed while resizing window");
			terminateLCDcontroller();
			return true;
		}
		memset(Master.vram,0,Master.pitch * Master.resY);
		reVal = true;
	}
	rX = resX;
	rY = resY;
	return reVal;
}

// Returns True if the window was resized. Optional: Returns new window size.
bool windowResizingCode(uint32_t* resX, uint32_t* resY) {
	int32_t x = 0, y = 0;
	SDL_GetWindowSize(window,&x,&y);
	return resizeWindow(x,y,resX,resY);
}


void newFrame() {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
        terminateLCDcontroller();
        exit(0);
    }
	windowResizingCode(NULL,NULL);
	copyFrame(Master.vram);
	SDL_UpdateTexture(texture, NULL, Master.vram, Master.pitch);
	{
		SDL_Rect srcRect = {0,0,(int)Master.resX,(int)Master.resY};
		SDL_Rect dstRect = {0,0,(int)Master.resX,(int)Master.resY};
		SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
	}
	SDL_RenderPresent(renderer);
}