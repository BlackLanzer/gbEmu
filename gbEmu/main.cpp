#include <iostream>

#include "CPU.h"

int main(int argc, char const *argv[])
{
	
	CPU cpu = CPU();
	cpu.init();
	
	/* 
		while(0)
		{
			byte istruzione = CPU.fetch(dal pc)
			CPU.esegui(istruzione)
			
		}
	*/

	// NOTE TESTING
	byte test = 0x82;
	char test2 = ((char) test);
	test--;
	test2 = test;

	while (true)
	{
		byte istruzione = 0x80;
		cpu.execute(istruzione);
		istruzione = 0x27;
		cpu.execute(istruzione);
	}
	// cpu.mmu.loadRom(std::string("../roms/ttt.gb"));
	// cpu.mmu.dumpMemory(std::string("../roms/ttt.dump2"));

	// while(true)
	// {
	// 	byte istruzione = cpu.fetch();
	// 	cpu.execute(istruzione);

	// 	std::cout << cpu.instructionName;	
	// 	// cpu.mmu.dumpMemory(std::string("../roms/ttt.dump2"));
	// }


	system("PAUSE");
	return 0;
}