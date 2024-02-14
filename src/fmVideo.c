/*
**	Author: zerico2005 (2023-2024)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "fmVideo.h"
#include "prime2D.h"
#include "primeKey.h"


int8_t playIntroVideo() {
	/*
	lcd_UpBase = 0xD40000;
	lcd_VideoMode = lcd_BGR4bit;

	uint8_t prgm;
	char blockName[6] = {'V','O','D','0','0','\0'};

    while (1) {

        kb_Scan(); //Scans Keys
        if (kb_Data[1] & kb_Del) {
            return 1; //Quit
        } //Force Quit
        if ((kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd) || (kb_Data[2] & kb_Alpha) || (kb_Data[7])) {
            return 2; //Quit
        } //Skip Cutscene

        //Load AppVar
		
		for (uint8_t block = 0; block < 20; block++) {
			blockName[4]++;
			if (blockName[4] == ('9' + 1)) {
				blockName[3]++;
				blockName[4] = '0';
			}
			prgm = ti_Open(fileName, "r");
			ti_GetDataPtr(prgm);
			uint8_t blockFrameCount = 
			ti_Seek(offSET, SEEK_SET, prgm); //Seeks to the required data
			ti_Read(&data, 3, 10584, prgm);
		}
        ti_Close(prgm);
    }

    prgm = 0;
    *frameBase = VRAM;
    // *videoMode = 0x92D; //16 bit
	*/
    return 0; //Quits program
}