#pragma once

#include "types.h"

// contiene tutti i registri della CPU
//	8+8 bit:
//	AF 
//	BC
//	DE
//	HL
//	16 bit:
//	SP (stack pointer)
//	PC (program counter)
// sono invertiti nelle struct perché siamo in little endian
struct Registers
{
	// AF
	union
	{
		struct 
		{
			// Flags:
			// 	- 0000
			// 	- carry			00010000 0x10
			// 	- half carry	00100000 0x20
			// 	- add/sub flag 	01000000 0x40
			// 	- zero flag 	10000000 0x80
			byte f;
			byte a;
		};
		word af;
	};

	// BC
	union
	{
		struct 
		{
			byte c;
			byte b;
		};
		word bc;
	};

	// DE
	union
	{
		struct 
		{
			byte e;
			byte d;
		};
		word de;
	};

	// HL
	union
	{
		struct 
		{
			byte l;
			byte h;
		};
		word hl;
	};

	word sp, pc;
};