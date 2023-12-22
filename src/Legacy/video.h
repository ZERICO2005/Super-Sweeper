#ifdef VIDEO
#ifndef VIDEO_H
#define VIDEO_H

#include <global.h>
#include <prime2D.h>
#include <stdint.h>


const uint16_t palette[1260] = {/*0*/3171,12684,12687,15855,18927,25266,31608,3,22098,25269,25368,25371,28440,31509,31512/*1*/,3171,12684,12687,15855,18927,25266,31608,3,22095,22098,25269,25368,25371,28440,31509/*2*/,3171,12684,12687,15855,18927,25266,31608,3,22095,22098,25269,25368,25371,28440,31509/*3*/,3171,12684,12687,15855,18927,25266,28437,3,31608,25368,25371,28440,31509,28536,31512/*4*/,3171,12684,12687,15855,18927,25266,28437,3,31608,25368,25371,28440,31509,28539,31512/*5*/,3171,12684,12687,15855,18927,25266,28437,3,31608,22200,25371,28440,31509,28539,31512/*6*/,3171,12684,12687,15855,18927,25266,28437,3,31608,25269,25368,25371,28440,31509,28539/*7*/,3171,12684,12687,15756,15855,25266,28437,3,22098,31608,25368,25467,28440,28539,31509/*8*/,3171,12684,12687,15756,15855,25266,28437,3,22098,25269,31608,25467,28539,31509,31512/*9*/,3171,12684,12687,15756,15855,25266,28437,3,31608,25368,22200,28539,31509,31512,31611/*10*/,3171,12684,12687,15756,15855,25266,31608,3,25269,28539,25368,25371,25467,31509,31512/*11*/,3171,12684,12687,15756,15855,25266,31608,3,28539,22095,22200,25368,25371,25467,31611/*12*/,3171,12684,15855,12687,31608,28437,28539,3,19029,22200,25368,31611,25467,28440,31512/*13*/,3171,12684,15855,12585,12687,31608,28539,3,15759,25368,25269,31509,31611,25371,28440/*14*/,3171,12684,6342,15756,15855,28539,31608,3,25269,19029,25368,22200,31509,31611,25170/*15*/,3171,3174,6342,12684,15756,15855,15858,3,28437,31608,31611,22200,31509,28542,31707/*16*/,3171,3174,12684,9513,15855,15858,28437,3,31608,28539,31611,28338,31707,25371,28341/*17*/,3171,3174,12684,15756,15855,15858,28437,3,31608,28539,31611,31509,28341,31707,31512/*18*/,3171,3174,12684,15756,15855,15858,31608,3,28539,22200,25368,31611,31509,31707,28341/*19*/,3171,3174,15855,15756,15858,18927,28437,3,31608,31707,28539,31611,31509,31710,31605/*20*/,3171,3174,15855,15858,12786,18927,28437,3,31707,31608,31611,31509,28638,31710,31212/*21*/,3171,3174,15756,15855,15858,18927,31707,3,28542,31608,31611,28440,28638,31509,31710/*22*/,3171,3174,15855,15858,18927,31707,31608,3,25266,25368,31611,28638,31710,31605,28515/*23*/,3171,3174,15858,15756,18927,28437,31707,31710,25368,25371,28440,28539,28638,31611,31605/*24*/,3171,3174,15858,18927,15855,28437,31608,31707,31710,25368,28638,28440,28539,31611,31614/*25*/,3171,3174,12786,15858,18927,28437,28542,31608,31707,31710,28638,31611,22299,29568,28672/*26*/,3171,12786,15855,15858,18927,28437,28542,31608,31707,31710,31611,22095,28341,29568,28672/*27*/,12786,15858,18927,28437,28542,31608,31707,31710,22299,25368,31611,31680,31509,29568,28672/*28*/,12786,15855,15858,18927,28437,28542,31608,31707,31710,25269,28638,31680,31614,29568,28672/*29*/,12786,15855,15858,18927,28437,28542,31608,31707,31710,25269,28638,30720,31680,29568,28672/*30*/,12786,15756,15855,15858,18927,28437,28542,31608,31707,31710,28638,31680,31512,29568,28672/*31*/,12786,15756,15858,18927,28437,28542,31608,31707,31611,31710,31512,28638,31680,29568,28672/*32*/,12786,15858,15855,18927,28437,28542,31608,31707,28539,31710,31512,31680,31509,29568,28672/*33*/,12786,15858,15855,18927,28437,28542,31608,28440,31707,31710,28638,31680,31512,29568,28672/*34*/,12786,15858,15855,28542,19128,31710,31707,31611,25368,25371,25470,28638,31512,29568,28672/*35*/,12786,15858,15855,18927,28437,28542,31710,31611,31707,28638,30720,31512,31680,29568,28672/*36*/,12786,15858,18927,19128,28437,28542,31710,31611,31707,28638,31512,31680,31017,29568,28672/*37*/,12786,15855,15858,19128,28437,28542,31608,31710,25470,28638,31509,31680,25272,29568,28672/*38*/,12786,15855,19128,28437,18927,28542,31608,28539,31710,31611,31509,30720,31680,29568,28672/*39*/,12786,15858,19128,28437,28542,31608,25266,25371,31707,31710,31509,31680,28341,29568,28672/*40*/,9615,12786,15858,28437,28542,31608,31707,28440,28539,31710,31611,31680,28434,29568,28672/*41*/,9615,12786,15855,28437,28542,31608,28539,31707,31710,31680,28638,31509,28341,29568,28672/*42*/,9615,12786,15855,28437,28542,31608,25371,28539,31611,31710,31509,25263,28341,29568,28672/*43*/,9615,15855,15756,28437,28542,31608,25371,28539,31710,31707,28536,31509,28638,29568,28672/*44*/,9615,15855,28437,31608,28539,28542,19029,25371,31707,31710,28440,30720,31680,29568,28672/*45*/,9615,15855,28437,31608,28539,28542,28338,31611,28434,31710,28440,31707,31680,29568,28672/*46*/,15855,15756,28437,31608,28539,28542,28338,25371,28434,31611,31707,31680,31710,29568,28672/*47*/,15855,15756,28437,25266,31608,22200,28542,19128,25368,25371,31611,30720,31680,29568,28672/*48*/,15855,9615,15756,12687,28437,28539,31608,28542,25371,28434,31611,31707,28440,29568,28672/*49*/,15756,15855,12585,12687,28437,25266,31608,28539,28542,31611,31707,31680,31605,29568,28672/*50*/,15756,15855,12684,28437,18927,25266,31608,28539,28542,31611,31707,25269,31605,29568,28672/*51*/,15756,9615,15855,12687,28437,28338,31608,28542,31611,30720,31707,31605,25263,29568,28672/*52*/,15756,9615,15855,12687,28437,25266,28539,31608,28434,28542,31611,31680,31707,29568,28672/*53*/,3171,15756,15855,12684,28437,28539,18927,25266,31608,28434,31611,31680,31707,29568,28672/*54*/,3171,15756,15855,12585,12684,28437,18927,28539,22200,25368,31608,28434,31611,29568,28672/*55*/,3171,15756,15855,12684,28437,15759,28539,25266,25368,31608,31611,31680,31707,29568,28672/*56*/,3171,15756,15855,12684,28437,28539,25266,25368,31608,31611,30720,31680,31707,29568,28672/*57*/,15756,12585,15855,28437,28338,28539,31608,25368,25371,28542,31611,31509,31707,29568,28672/*58*/,15756,15855,12684,28437,31608,22200,28539,25371,28542,31707,31680,31605,31611,29568,28672/*59*/,15756,15855,28338,28437,31608,25266,28539,28542,31707,31509,31680,31710,31704,29568,28672/*60*/,15756,12585,15855,22200,28437,31608,28542,31611,30720,31509,31680,31707,31710,29568,28672/*61*/,9615,15756,15855,28437,18927,28338,28542,31608,28440,31611,31707,28434,31710,29568,28672/*62*/,9615,12585,15756,15855,15858,28437,28338,28542,31608,28440,31707,31509,31710,31689,31017/*63*/,9615,15855,15756,28437,28338,25266,19128,28542,31608,31611,31707,31710,31605,25467,31614/*64*/,9615,15855,15756,28437,15858,28338,25266,28542,31608,31707,31710,31509,31605,31614,31512/*65*/,9615,15756,15855,28437,15858,22200,28338,28539,31608,31611,31710,28524,31707,31605,25467/*66*/,9615,12585,15756,15855,28437,22200,28338,28539,31608,25371,31611,31710,31707,31605,28443/*67*/,9615,12687,15756,15855,19029,28437,28338,28539,31608,31611,31710,25365,28341,31509,31707/*68*/,9615,12687,15855,19029,28338,28437,28539,31608,31611,28440,31710,25167,28434,25365,31707/*69*/,9615,12687,15855,19029,28338,28437,28539,31608,31611,31710,25272,28434,31707,31509,31605/*70*/,9615,12687,15855,22200,28338,28539,31608,31611,31710,25269,28434,31707,31605,25467,31614/*71*/,9615,12687,15855,22200,28338,28539,31608,28542,31611,31710,25269,31605,31509,31707,31614/*72*/,9615,12687,15855,19029,22200,28338,28539,31608,31611,31710,31605,28341,28536,31707,25365/*73*/,9615,12687,15855,19029,22200,28338,28437,28539,31608,31611,31710,31605,31707,31614,28536/*74*/,9615,12687,15855,22200,28338,28437,28539,31608,31611,25167,25269,31710,28440,31509,31605/*75*/,9615,12687,15756,15855,22200,28338,28437,28539,31608,31611,28341,31710,31605,28443,28536/*76*/,9615,12687,15756,15855,22200,28338,28437,28539,31608,31611,28341,28440,31509,31710,28335/*77*/,9615,12687,15756,15855,22200,28338,28437,28539,31608,31611,28341,28440,31509,28434,31710/*78*/,15756,12585,12687,15855,28338,28437,28539,31608,31611,28341,28440,31509,28434,31605,31710/*79*/,12687,9615,15756,25266,28437,25167,25371,28440,31608,25263,28338,28536,28341,28434,28539/*80*/,12684,22095,9513,25266,19029,22197,15954,22200,28437,25365,25272,18930,25170,25263,28341/*81*/,9513,9516,18924,19026,22095,22098,22194,3,22197,25266,21996,18828,21999,18921,25170/*82*/,6342,6345,9414,15753,15855,18927,15852,3,12585,12783,15858,19023,19026,32768,32768/*83*/,3171,3174,6243,6342,9513,12585,12681,12684,9612,32768,32768,32768,32768,32768,32768};
uint24_t data[3528];

void cycle();
void cycleFast();
void loadFrame(unsigned int b, unsigned int f);
unsigned int block = 0;
uint8_t prgm;
uint24_t* rom;
uint24_t* blit;
uint24_t* pDAT = palette; //Change to 24bit
uint24_t slide = 0;

uint24_t splashTimer;

void splash32K() { //32768hz, overflow resiliant
    while (deltaTime(timer_Get(1), splashTimer) < (32768/12));
    splashTimer = timer_Get(1);
}

uint8_t splashVideo() {
    *paletteRAM = 0;
    *frameBase = 0xD49600;
    pDAT = (void *)((uint8_t *)pDAT + 0);
    
    //cycle();

    while (1) {

        kb_Scan(); //Scans Keys
        if (kb_Data[1] & kb_Del) {
            return 1; //Quit
        } //Force Quit
        if ((kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd) || (kb_Data[2] & kb_Alpha) || (kb_Data[7])) {
            *frameBase = VRAM;
            return 2; //Quit
        } //Skip Cutscene

        //Load AppVar
        unsigned char txt[6] = "VOD";
        unsigned char num[3];
        sprintf(num, "%02d", block);
        prgm = ti_Open(strcat(txt, num), "r");
        
        uint24_t offSET = 0; // where in the data block to search

        for (uint8_t frame = 0; frame < 6; frame++) { // 6 frames per block

            ti_Seek(offSET, SEEK_SET, prgm); //Seeks to the required data
            ti_Read(&data, 3, 10584, prgm);
            rom = &data;
            blit = frame & 1 ? 0xD423C6 : 0xD4B9C6; // ((320 - 168) / 4) + ((240 - 126) * 80)

            for (uint8_t y = 0; y < 126; y++) {
                for (uint8_t x = 0; x < 28; x++) {
                    *blit = *rom;
                    blit++;
                    rom++;
                }
                blit = (void *)((uint8_t *)blit + 76); // (320 - 144) / 2 Bytes
            }

            *frameBase = frame & 1 ? 0xD40000 : 0xD49600;
            cycleFast();
            offSET += 10584;
            slide++;
            splash32K(); //Forces 12FPS
            if (slide == 84) {
                ti_Close(prgm);
                prgm = 0;
                *frameBase = VRAM;
                return 0;
            }
        }

        block++;
        ti_Close(prgm);
    }

    prgm = 0;
    *frameBase = VRAM;
    //*videoMode = 0x92D; //16 bit
    return 0; //Quits program
}

void cycle() {
    uint24_t* pRAM = paletteRAM; //Change to 24bit
    pRAM = (void *)((uint8_t *)pRAM + 2);
    for (uint8_t z = 0; z < 10; z++) { //Change to 24bit
        *pRAM = *pDAT;
        pDAT++;
        pRAM++;
    }
}

void cycleFast() { // Unrolling the loop
    uint24_t* pRAM = 0xE30202; //paletteRAM + 2
    *pRAM = *pDAT; /*0*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*1*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*2*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*3*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*4*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*5*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*6*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*7*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*8*/
    pDAT++;
    pRAM++;
    *pRAM = *pDAT; /*9*/
    pDAT++;
    pRAM++;
}


#endif /* VIDEO_H */
#endif /* VIDEO */