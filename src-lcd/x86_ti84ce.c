/*
**	Author: zerico2005 (2023)
**	Project: Endless-Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	x86_ti84ce.h simulates libraries and functions from the CE Programming Toolchain.
**	Some functions may not be completely accurate or fully implemented.
*/

#include "x86_Common_Def.h"
#include "x86_ti84ce.h"
#include "x86_Render.h"

uint8_t simulated_ram[16777216];

void resetLCDcontroller() {
	lcd_UpBase = 0xD40000;
	lcd_VideoMode = lcd_BGR16bit;
}

/* <keypadc.h> */

	uint8_t kb_Data[8];

	void kb_Reset() { 
		internal_kb_Reset();
	}
	
	void kb_Scan() { 
		internal_kb_Scan();
	}

/* <sys/timers.h> */

	struct Simulated_Timer {
		uint8_t enabled;
		uint8_t rate;
		uint8_t inter;
		uint8_t dir;
	}; typedef struct Simulated_Timer Simulated_Timer;
	
	Simulated_Timer simulated_timer[3] = {
		{0,1,0,1},{1,1,0,1},{1,1,0,1}
	};

	void timer_Enable(uint8_t n, uint8_t rate, uint8_t inter, uint8_t dir) {
		if (n < 1 || n > 3) { return; }
		simulated_timer[n - 1].enabled = 1;
		simulated_timer[n - 1].rate = rate;
		simulated_timer[n - 1].inter = inter;
		simulated_timer[n - 1].dir = dir;
	}
	
	void timer_Disable(uint8_t n) {
		if (n < 1 || n > 3) { return; }
		simulated_timer[n - 1].enabled = 0;
	}

	// n is supposed to be a value between 1 and 3
	uint32_t timer_Get(uint8_t n) {
		if (n < 1 || n > 3) { return 0; }
		if (simulated_timer[n - 1].enabled == 0) {
			return 0;
		}
		if (simulated_timer[n - 1].rate == 0) {
			fp64 timerCPU = getDecimalTime(); //Time in seconds
			timerCPU *= 15000000.0;
			return (uint32_t)timerCPU;
		}
		fp64 timer32K = getDecimalTime(); //Time in seconds
		timer32K *= 32768.0;
		return (uint32_t)timer32K;
	}

/* <fileioc.h> */
	// Not implemented yet, everything returns 0

	uint8_t ti_Open(const char* name, const char* mode) { return 0; } // Does nothing. Returns 0
	int ti_Close(uint8_t handle) { return 0; } // Does nothing. Returns 0
	size_t ti_Read(void* data, size_t size, size_t count, uint8_t handle) { return 0; } // Does nothing. Returns 0
	int ti_Seek(int offset, unsigned int origin, uint8_t handle) { return 0; } // Does nothing. Returns 0