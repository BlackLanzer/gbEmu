#include "CPU.h"

CPU::CPU()
{
	regs = {};
	clock = 0;
	mmu = MMU();
}

void CPU::init()
{
	regs.pc = 0x100;
}

byte CPU::fetch()
{
	byte instruction = mmu.readByte(regs.pc++);
	return instruction;
}

void CPU::execute(byte opcode)
{
	switch(opcode)
	{
		#include "instructions.h"
	}
}