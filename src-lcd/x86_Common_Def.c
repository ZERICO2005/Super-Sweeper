/*
**	Author: zerico2005 (2023)
**	Project: Endless-Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "x86_Common_Def.h"

fp64 getDecimalTime() {
	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp) == 0) {
		uint64_t nanoTime = tp.tv_sec * 1000000000 + tp.tv_nsec;
		return (fp64)nanoTime / 1.0e9;
	} else {
		perror("clock_gettime");
		return 0.0;
	}
}

int64_t getNanoTime() {
	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp) == 0) {
		int64_t nanoTime = tp.tv_sec * 1000000000 + tp.tv_nsec;
		return nanoTime;
	} else {
		perror("clock_gettime");
		return 0;
	}
}