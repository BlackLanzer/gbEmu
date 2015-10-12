#pragma once

#include "types.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class MMU
{
private:
	byte memory[0xFFFF];
	std::vector<byte> rom;

public:
	MMU();
	
	byte readByte(word address);
	word readWord(word address);

	void writeByte(word address, byte value);
	void writeWord(word address, word value);

	void loadRom(std::string path);
	void dumpMemory(std::string path);
};