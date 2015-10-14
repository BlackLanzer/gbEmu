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

	while (true)
	{
		byte istruzione = 0x04;
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