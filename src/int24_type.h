/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef INT24_TYPE
#define INT24_TYPE

/*
**	Version 1.0.2
**	2023/04/10
*/

class uint24_t {
	private:
		//Stored across 3 bytes
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		
		//Conversions
		uint24_t format24(uint32_t i) { //32bit to 24bit
			uint24_t z;
			z.b0 = i & 255;
			z.b1 = (i >> 8) & 255;
			z.b2 = (i >> 16) & 255;
			return z;
		}
		uint32_t format32(uint24_t z) { //24bit to 32bit
			return (z.b0) + (z.b1 << 8) + (z.b2 << 16);
		}
	
	public:
		//Constructors
		uint24_t() {}
		uint24_t(uint32_t i) {
			b0 = i & 255;
			b1 = (i >> 8) & 255;
			b2 = (i >> 16) & 255;
		}
		operator uint32_t () {
			return (b0) + (b1 << 8) + (b2 << 16);
		}
		
		//Bitwise Not
		uint24_t operator~() {
			uint32_t z = (b0) + (b1 << 8) + (b2 << 16);
			return format24(~z);
		}
		
		//Debug
		void print_uint24_t() {
			uint32_t w = (b0) + (b1 << 8) + (b2 << 16);
			printf("\n%8d | %d,%d,%d",w,b2,b1,b0);	
		}
};

class int24_t {
	private:
		//Stored across 3 bytes
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		
		//Conversions
		int24_t format24(int32_t i) { //32bit to 24bit
			int24_t z;
			z.b0 = (uint32_t)(i) & 255;
			z.b1 = ((uint32_t)(i) >> 8) & 255;
			z.b2 = ((uint32_t)(i) >> 16) & 255;
			return z;
		}
		int32_t format32(int24_t z) { //24bit to 32bit
			int32_t w = (z.b0) + (z.b1 << 8) + (z.b2 << 16);
			if (b2 & 128) { //If bit 23 is set
				w |= 0xFF000000;
			}
			return w;
		}
	
	public:
		//Constructors
		int24_t() {}
		int24_t(int32_t i) {
			b0 = (uint32_t)(i) & 255;
			b1 = ((uint32_t)(i) >> 8) & 255;
			b2 = ((uint32_t)(i) >> 16) & 255;
		}
		operator int32_t () {
			int32_t w = (b0) + (b1 << 8) + (b2 << 16);
			if (b2 & 128) { //If bit 23 is set
				w |= 0xFF000000;
			}
			return w;
		}
		
		//Bitwise Not
		int24_t operator~() {
			int32_t z = (b0) + (b1 << 8) + (b2 << 16);
			return format24(~z);
		}
		
		//Debug
		void print_int24_t() {
			int32_t w = (b0) + (b1 << 8) + (b2 << 16);
			if (b2 & 128) { //If bit 23 is set
				w |= 0xFF000000;
			}
			printf("\n%8d | %d,%d,%d",w,b2,b1,b0);	
		}
		void print_uint24_t() {
			uint32_t w = (b0) + (b1 << 8) + (b2 << 16);
			printf("\n%8d | %d,%d,%d",w,b2,b1,b0);	
		}
};

#endif /* INT24_TYPE */