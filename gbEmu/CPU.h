#pragma once

#include "registers.h"
#include "types.h"
#include "MMU.h"
#include <iostream>
#include <string>

class CPU
{
private:
	Registers regs;
	unsigned int clock;
	//MMU mmu; TODO

public:
	CPU();
	
	void init();
	byte fetch();
	void execute(byte opcode);

	std::string instructionName;
	MMU mmu; //TODO
};