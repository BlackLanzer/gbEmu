#include "MMU.h"

MMU::MMU()
{
	// TODO RIMUOVERE TESTING
	memory[0] = 0x08;
	memory[1] = 0x00;
	memory[2] = 0x10;
}

byte MMU::readByte(word address)
{
	return memory[address];
}

word MMU::readWord(word address)
{
	return memory[address] + (memory[address+1] << 8);
}

void MMU::writeByte(word address, byte value)
{
	memory[address] = value;
}

// TODO controllare l'ordine dei byte
void MMU::writeWord(word address, word value)
{
	memory[address] = value;
	memory[address+1] = value >> 8;
}

void MMU::loadRom(std::string path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		int size = file.tellg();
		rom.reserve(size);
		file.seekg(0,std::ios::beg);
		file.read((char*) rom.data(), size);

		// NOTE funziona solo se non c'è il bank switching
		file.seekg(0,std::ios::beg);
		file.read((char*) memory, 0x7FFF);
		file.close();

		std::cout << "File " << path << " aperto correttamente" << std::endl;
	}
	else
	{
		std::cout << "Impossibile aprire " << path << std::endl;
	}
}

void MMU::dumpMemory(std::string path)
{
	std::ofstream file(path, std::ios::out | std::ios::binary);
	file.write((char*)memory, 0xFFFF);
}