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

#include <process.h>
#include <dir.h>
#include <conio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef PLATFORM_WINDOWS
	#include <windows.h>
#endif

uint8_t simulated_ram[16777216];

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
	
	#define NameSize (8)
	#define RamFolderPath "./Ti-Ram"
	#define ArchiveFolderPath "./Ti-Archive"

	struct Ti_File_Handle {
		bool active;
		bool read;
		bool write;
		bool append;
		FILE* file;
		char name[NameSize + 1];
	}; typedef struct Ti_File_Handle Ti_File_Handle;
	
	Ti_File_Handle ti_File_Handle[256];

	bool validate_Ti_File_Handle(uint8_t handle) {
		if (handle == 0) {
			return false;
		}
		if (ti_File_Handle[handle].active == false) {
			return false;
		}
		if (ti_File_Handle[handle].file == NULL) {
			return false;
		}
		if (
			(ti_File_Handle[handle].read == false) &&
			(ti_File_Handle[handle].write == false) &&
			(ti_File_Handle[handle].append == false)
		) {
			return false;
		}
		return true;
	}

	void clear_Ti_File_Handle(uint8_t handle) {
		ti_File_Handle[handle].active = false;
		ti_File_Handle[handle].read = false;
		ti_File_Handle[handle].write = false;
		ti_File_Handle[handle].append = false;
		memset(ti_File_Handle[handle].name,'\0',sizeof(ti_File_Handle[handle].name));
	}

	uint8_t ti_Open(const char* name, const char* mode) {
		if (name == NULL || mode == NULL) {
			return 0;
		}
		uint8_t handle = 0;
		for (size_t i = 1; i < 256; i++) {
			if (ti_File_Handle[i].active == false) {
				handle = i;
				break;
			}
		}
		if (handle == 0) {
			return 0;
		}
		clear_Ti_File_Handle(handle);
		switch (mode[0]) {
			case 'r':
				ti_File_Handle[handle].read = true;
			break;
			case 'w':
				ti_File_Handle[handle].write = true;
			break;
			case 'a':
				ti_File_Handle[handle].append = true;
			break;
			default:
				return 0;
		};
		if (mode[1] == '+') {
			if (ti_File_Handle[handle].read == true) {
				ti_File_Handle[handle].write = true;
			} else {
				ti_File_Handle[handle].read = true;
			}
		}

		snprintf(ti_File_Handle[handle].name,NameSize + 1,"%s",name);
		for (size_t i = 0; i < NameSize; i++) { // Capitalizes
			if (ti_File_Handle[handle].name[i] >= 'a' && ti_File_Handle[handle].name[i] <= 'z') {
				ti_File_Handle[handle].name[i] -= ('a' - 'A');
			}
		}

		size_t filePathSize = snprintf(NULL,0,"%s/%s.dat",RamFolderPath,ti_File_Handle[handle].name);
		filePathSize++; // Null Terminator
		char* filePath = (char*)malloc(filePathSize + 1);
		snprintf(filePath,filePathSize,"%s/%s.dat",RamFolderPath,ti_File_Handle[handle].name);
		
		size_t fileModeSize = snprintf(NULL,0,"%sb",mode);
		fileModeSize++; // Null Terminator
		char* fileMode = (char*)malloc(fileModeSize + 1);
		snprintf(fileMode,fileModeSize,"%sb",mode);
		
		mkdir(RamFolderPath);
		ti_File_Handle[handle].file = fopen(filePath, fileMode);
		
		if (ti_File_Handle[handle].file == NULL) {
			printf_FileIOC("\nError: ti_Read() could not open: %s",filePath);
			FREE(fileMode);
			FREE(filePath);
			return 0;
		}
		ti_File_Handle[handle].active = true;
		FREE(fileMode);
		FREE(filePath);
		return handle;
	}

	int ti_Close(uint8_t handle) { 
		fclose(ti_File_Handle[handle].file);
		clear_Ti_File_Handle(handle);
		return handle;
	}

	size_t ti_Read(void* data, size_t size, size_t count, uint8_t handle) {
		if (data == NULL || size == 0 || count == 0)	{
			printf_FileIOC("\nError: ti_Read() NULL parameters");
			return 0;
		}
		if (validate_Ti_File_Handle(handle) == false) {
			printf_FileIOC("\nError: ti_Read() handle %d is invalid or NULL",handle);
			return 0;
		}
		if (ti_File_Handle[handle].read == false) {
			printf_FileIOC("\nError: ti_Read() handle %d does not have Read premissions",handle);
			return 0;
		}
		size_t readCount = fread(data, size, count, ti_File_Handle[handle].file);
		return readCount;
	}
	
	size_t ti_Write(const void* data, size_t size, size_t count, uint8_t handle) {
		if (data == NULL || size == 0 || count == 0)	{
			printf_FileIOC("\nError: ti_Write() NULL parameters");
			return 0;
		}
		if (validate_Ti_File_Handle(handle) == false) {
			printf_FileIOC("\nError: ti_Write() handle %d is invalid or NULL",handle);
			return 0;
		}
		if (ti_File_Handle[handle].write == false && ti_File_Handle[handle].append == false) {
			printf_FileIOC("\nError: ti_Write() handle %d does not have Write/Append premissions",handle);
			return 0;
		}
		size_t writeCount = fwrite(data,size,count,ti_File_Handle[handle].file);
		return writeCount;
	}

	int24_t ti_PutC(char ch, uint8_t handle) {
		if (validate_Ti_File_Handle(handle) == false) {
			printf_FileIOC("\nError: ti_Write() handle %d is invalid or NULL",handle);
			return '\0';
		}
		return putc(ch,ti_File_Handle[handle].file);
	}
	int24_t ti_GetC(uint8_t handle) {
		if (validate_Ti_File_Handle(handle) == false) {
			printf_FileIOC("\nError: ti_Write() handle %d is invalid or NULL",handle);
			return '\0';
		}
		return getc(ti_File_Handle[handle].file);
	}
	int24_t ti_Seek(int24_t offset, uint24_t origin, uint8_t handle) {
		if (validate_Ti_File_Handle(handle) == false) {
			printf_FileIOC("\nError: ti_Write() handle %d is invalid or NULL",handle);
			return 0;
		}
		return fseek(ti_File_Handle[handle].file,offset,origin);
	}

	uint16_t ti_GetSize(uint8_t handle) {
		if (validate_Ti_File_Handle(handle) == false) {
			printf_FileIOC("\nError: ti_Write() handle %d is invalid or NULL",handle);
			return 0;
		}
		fpos_t currentPos;
		fgetpos(ti_File_Handle[handle].file,&currentPos);
		fseek(ti_File_Handle[handle].file, 0, SEEK_END);
		long fileSize = ftell(ti_File_Handle[handle].file);
		fsetpos(ti_File_Handle[handle].file,&currentPos);
		valueLimit(fileSize,0,65535);
		return (uint16_t)fileSize;
	}

	int24_t ti_Rewind(uint8_t handle) {
		return ti_Seek(0, SEEK_SET, handle);
	}

	#undef RamFolderPath
	#undef NameSize

/* Setup */

void resetLCDcontroller() {
	lcd_UpBase = 0xD40000;
	lcd_VideoMode = lcd_BGR16bit;
}