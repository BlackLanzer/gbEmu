#pragma once

// 0x00 NOP
case 0x00:
{
	clock += 1;
	//instructionName = "NOP";
	break;
}
// 0x01 LD BC,nn
case 0x01:
{
	regs.bc = mmu.readWord(regs.pc);
	clock += 3;
	regs.pc += 2;
	//instructionName = std::string("LD BC, ") << regs.bc;
	break;
}
// 0x02 LD (BC), A
case 0x02:
{
	mmu.writeByte(regs.bc, regs.a);
	clock +=2;
	//instructionName = "LD (BC), A";
	break;
}
// 0x03 INC BC
case 0x03:
{
	regs.bc++;
	clock += 2;
	//instructionName = "INC BC";
	break;
}
// 0x04 INC B
case 0x04:
{
	regs.b++;
	// flags
	// zero flag
	if (regs.b == 0)
		regs.f |= 0x80;
	else
		regs.f &= ~0x80;
	// add/sub flag
	regs.f &= 0xBF;
	// half carry
	// non ho idea di come funziona
    byte hFlag = (regs.b & 0x0F) ? 0 : 1;
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "INC B";
	break;
}
// 0x05 DEC B
case 0x05:
{
	regs.b--;
	// flags
	// zero flag
	if (regs.b == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag
	regs.f |= 0x40;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = ((regs.b & 0x0F) == 0x0F) ? 1 : 0);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "DEC B";
	break;
}
// 0x06 LD B, n
case 0x06:
{
	regs.b = mmu.readByte(regs.pc++);
	clock += 2;
	//instructionName = std::string("LD B, ") << (int) regs.b;
	break;
}
// 0x07 RLCA 
case 0x07:
{
	// istruzione che fa una rotazione verso sinistra dei bit
	// e salva l'ultimo nel primo bit e nel carry flag
	byte lastBit = regs.a & 0x80;
	// flags 000c
	// azzero i flag
	regs.f = 0; 
	// aggiorno il carry flag
	regs.f = lastBit << 4;
	// rotazione di A
	regs.a = (regs.a << 1) + lastBit;
	clock++;
	//instructionName = "RLCA";
	break;
}
// 0x08 LD (nn), SP
case 0x08:
{
	word address = mmu.readWord(regs.pc);
	mmu.writeWord(address,regs.sp);
	clock += 5;
	regs.pc += 2;
	//instructionName = std::string("LD (") << address << std::string("), SP");
	break;
}
// 0x09 ADD HL, BC
case 0x09:
{
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (((regs.hl & 0x0FFF) + (regs.bc & 0x0FFF)) > 0x0FFF) ? 1 : 0;
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 

	int tmp = regs.hl + regs.bc;
	regs.hl = tmp;
	// flags: -0hc----
	// add/sub flag a 0
	regs.f &= 0xBF; // 0xBF = 10111111  
	// carry flag
	if (tmp > 0xFFFF)
	{	// set 1
		regs.f |= 0x10; // 0x10 = 00010000
	} 
	else
	{	// set 0
		regs.f &= 0xEF; // 0xEF = 11101111
	}
	clock += 2;
	//instructionName = "ADD HL, BC";
	break;
}
// 0x0A LD A, (BC)
case 0x0A:
{
	regs.a = mmu.readByte(regs.bc);
	clock += 2;
	//instructionName = "LD A, (BC)";
	break;
}
// 0x0B DEC BC
case 0x0B:
{
	regs.bc--;
	clock += 2;
	//instructionName = "DEC BC";
	break;
}
// 0x0C INC C
case 0x0C:
{
	regs.c++;
	// flags
	// zero flag
	if (regs.c == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag a 0
	regs.f &= 0xBF;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (regs.c & 0x0F) ? 0 : 1;
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "INC C";
	break;	
}
// 0x0D DEC C
case 0x0D:
{
	regs.c--;
	// flags
	// zero flag
	if (regs.c == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;	// add/sub flag a 1
	regs.f |= 0x40;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = ((regs.c & 0x0F) == 0x0F) ? 1 : 0);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "DEC C";
	break;
}
// 0x0E LD C, n
case 0x0E:
{
	regs.c = mmu.readByte(regs.pc++);
	clock += 2;
	//instructionName = std::string("LD C, ") << regs.c;
	break;
}
// 0x0F RRCA
case 0x0F:
{
	// istruzione che fa una rotazione verso destra dei bit
	// e salva il primo nell'ultimo bit e nel carry flag
	byte lastBit = regs.a & 1;
	// flags 000c
	// carry flag
	regs.f = lastBit << 4;
	// rotazione di A
	regs.a = (regs.a >> 1) + (lastBit << 7);
	clock++;
	//instructionName = "RRCA";
	break;
}
// 0x10 00 STOP 
case 0x10:
{
	// non so cosa faccia, quindi faccio solo andare avanti
	regs.pc++;
	clock++; // ???
	// instructionName = "STOP";
	break;
}
//0x11 LD DE, nn
case 0x11:
{
	regs.de = mmu.readWord(regs.pc);
	regs.pc += 2;
	clock += 3;
	// instructionName = "LD DE, " + nn;
	break;
}
// 0x12 LD (DE), A
case 0x12:
{
	mmu.writeBye(regs.de, regs.a);
	clock += 2;
	// instructioName = "LD (DE), A";
	break;
}
// 0x13 INC DE
case 0x13:
{
	regs.de++;
	clock += 2;
	// instructionName = "INC DE";
	break;
}
// 0x14 INC D
case 0x14:
{
	regs.d++;
	// flags
	// zero flag
	if (regs.d == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag a 0
	regs.f &= 0xBF;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (regs.d & 0x0F ? 0 : 1);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "INC D";
	break;
}
// 0x15 DEC D
case 0x15:
{
	regs.d--;
	// flags
	// zero flag
	if (regs.d == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag
	regs.f |= 0x40;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = ((regs.d & 0x0F) == 0x0F) ? 1 : 0);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	
	clock++;
	//instructionName = "DEC D";
	break;
}
// 0x16 LD D, n
case 0x16:
{
	regs.d = mmu.readByte(regs.pc++);
	clock += 2;
	//instructionName = std::string("LD D, ") << (int) regs.d;
	break;
}
// 0x17 RLA
case 0x17:
{
	// shift a sinistra dei bit con il carry che va nel primo bit
	byte lastBit = regs.a & 0x80;
	// rotazione di A
	regs.a = (regs.a << 1) + ((regs.f & 0x10) >> 4);
	// flags 000c
	// azzero i flag
	// aggiorno il carry flag
	regs.f = lastBit << 4;
	clock++;
	//instructionName = "RLA";
	break;
}
// 0x18 JR n
case 0x18:
{
	regs.pc += mmu.readByte(regs.pc++);
	clock += 3;
	// instructionName = "JR + " n;
	break;
}
// 0x19 ADD HL, DE
case 0x19:
{
	// half carry flag
	// non ho idea di come funziona
	byte hFlag = (((regs.hl & 0x0FFF) + (regs.de & 0x0FFF)) > 0x0FFF) ? 1 : 0;
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	int tmp = regs.hl + regs.de;
	regs.hl = tmp;
	// flags: -0hc----
	// add/sub flag a 0
	regs.f &= 0xBF; // 0xBF = 10111111  
	// carry flag
	if (tmp > 0xFFFF)
	{	// set 1
		regs.f |= 0x10; // 0x10 = 00010000
	} 
	else
	{	// set 0
		regs.f &= 0xEF; // 0xEF = 11101111
	}
	clock += 2;
	//instructionName = "ADD HL, DE";
	break;
}
// 0x1A LD A, (DE)
case 0x1A:
{
	regs.a = mmu.readByte(regs.de);
	clock += 2;
	//instructionName = "LD A, (DE)";
	break;
}
// 0x1B DEC DE
case 0x1B:
{
	regs.de--;
	clock += 2;
	//instructionName = "DEC DE";
	break;
}
// 0x1C INC E
case 0x1C:
{
	regs.e++;
	// flags
	// zero flag
	if (regs.e == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag a 0
	regs.f &= 0xBF;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (regs.e & 0x0F ? 0 : 1);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "INC e";
	break;
}
// 0x1D DEC E
case 0x1D:
{
	regs.e--;
	// flags
	// zero flag
	if (regs.e == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag
	regs.f |= 0x40;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = ((regs.e & 0x0F) == 0x0F) ? 1 : 0);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	
	clock++;
	//instructionName = "DEC E";
	break;
}
// 0x1E LD E, n
case 0x1E:
{
	regs.e = mmu.readByte(regs.pc++);
	clock += 2;
	//instructionName = std::string("LD E, ") << regs.c;
	break;
}
// 0x1F RRA
case 0x1F:
{
	// shift a destra dei bit con il carry che va nell'ultimo bit
	byte lastBit = regs.a & 0x01;
	// rotazione di A
	regs.a = (regs.a >> 1) + ((regs.f & 0x10) << 3);
	// flags 000c
	// carry flag
	regs.f = lastBit << 4;
	clock++;
	//instructionName = "RRA";
	break;
}
// 0x20 JR NZ, n
case 0x20:
{
	regs.pc++;
	if (regs.f & 0x80 == 0)
	{
		// jump
		regs.pc += mmu.readByte(regs.pc);
	}
	clock += 2;
	// instructionName = "JR NZ, " + n;
	break;
}
// 0x21 LD HL, nn
case 0x21:
{
	regs.hl = mmu.readWord(regs.pc);
	regs.pc += 2;
	clock += 3;
	// instructionName = "LD HL, " + nn;
	break;
}
// 0x22 LDI (HL), A
case 0x22:
{
	mmu.writeByte(regs.hl, regs.a);
	regs.hl++;
	clock += 2;
	// instructionName = "LDI (HL), A";
	break;
}
// 0x23 INC HL
case 0x23:
{
	regs.hl++;
	clock += 2;
	// instructionName = "INC HL";
	break;
}
// 0x24 INC H
case 0x24:
{
	regs.h++;
	// flags
	// zero flag
	if (regs.h == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag a 0
	regs.f &= 0xBF;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (regs.h & 0x0F ? 0 : 1);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "INC H";
	break;
}
// 0x25 DEC H
case 0x25:
{
	regs.h--;
	// flags
	// zero flag
	if (regs.h == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag
	regs.f |= 0x40;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = ((regs.h & 0x0F) == 0x0F) ? 1 : 0);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 	
	clock++;
	//instructionName = "DEC H";
	break;
}
// 0x26 LD H, n
case 0x26:
{
	regs.h = mmu.readByte(regs.pc++);
	clock += 2;
	//instructionName = std::string("LD H, ") << (int) regs.h;
	break;
}
// 0x27 DAA
case 0x27:
{
	// 	Description:
	// This instruction conditionally adjusts the accumulator for BCD addition
	// and subtraction operations. For addition (ADD, ADC, INC) or subtraction
	// (SUB, SBC, DEC, NEC), the following table indicates the operation performed:

	// --------------------------------------------------------------------------------
	// |           | C Flag  | HEX value in | H Flag | HEX value in | Number  | C flag|
	// | Operation | Before  | upper digit  | Before | lower digit  | added   | After |
	// |           | DAA     | (bit 7-4)    | DAA    | (bit 3-0)    | to byte | DAA   |
	// |------------------------------------------------------------------------------|
	// |           |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
	// |   ADD     |    0    |     0-8      |   0    |     A-F      |   06    |   0   |
	// |           |    0    |     0-9      |   1    |     0-3      |   06    |   0   |
	// |   ADC     |    0    |     A-F      |   0    |     0-9      |   60    |   1   |
	// |           |    0    |     9-F      |   0    |     A-F      |   66    |   1   |
	// |   INC     |    0    |     A-F      |   1    |     0-3      |   66    |   1   |
	// |           |    1    |     0-2      |   0    |     0-9      |   60    |   1   |
	// |           |    1    |     0-2      |   0    |     A-F      |   66    |   1   |
	// |           |    1    |     0-3      |   1    |     0-3      |   66    |   1   |
	// |------------------------------------------------------------------------------|
	// |   SUB     |    0    |     0-9      |   0    |     0-9      |   00    |   0   |
	// |   SBC     |    0    |     0-8      |   1    |     6-F      |   FA    |   0   |
	// |   DEC     |    1    |     7-F      |   0    |     0-9      |   A0    |   1   |
	// |   NEG     |    1    |     6-F      |   1    |     6-F      |   9A    |   1   |
// |------------------------------------------------------------------------------|

	// flags: z-0x
	// non ho idea di come funziona il tutto
	int a = regs.a;
	if ((regs.f &= 0x40) == 0)
    {
        if ((regs.f & 0x20) || ((a & 0xF) > 9))
            a += 0x06;
        
        if (regs.f & 0x10 || (a > 0x9F))
            a += 0x60;
    }
    else
    {
        if (regs.f & 0x20)
            a = (a - 6) & 0xFF;
        
        if (regs.f & 0x10)
            a -= 0x60;
    }
    
    regs.f &= ~0x20;
    
    if ((a & 0x100) == 0x100)
		regs.f |= 0x10;    

    a &= 0xFF;
    if (a == 0)
    	regs.f |= 0x80;
    else
    	regs.f &= ~0x80;

    regs.a = a;
	clock++;
	// instructionName = "DAA";
	break;
}
// 0x28 JR Z, n
case 0x28:
{
	regs.pc++;
	if (regs.f & 0x80 == 1)
	{
		// jump
		regs.pc += mmu.readByte(regs.pc);
	}
	clock += 2;
	// instructionName = "JR Z, " + n;
	break;
}
// 0x29 ADD HL, HL
case 0x29:
{
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (((regs.hl & 0x0FFF) + (regs.hl & 0x0FFF)) > 0x0FFF) ? 1 : 0;
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	int tmp = regs.hl + regs.hl;
	regs.hl = tmp;
	// flags: -0hc----
	// add/sub flag a 0
	regs.f &= 0xBF; // 0xBF = 10111111  
	// carry flag
	if (tmp > 0xFFFF)
	{	// set 1
		regs.f |= 0x10; // 0x10 = 00010000
	} 
	else
	{	// set 0
		regs.f &= 0xEF; // 0xEF = 11101111
	}
	
	clock += 2;
	//instructionName = "ADD HL, HL";
	break;
}
// 0x2A LD HL, (nn)
case 0x2A:
{
	regs.hl = mmu.readWord(mmu.readWord(regs.pc));
	regs.pc += 2;
	clock += 5;
	// instructionName = "LD HL, " + nn;
	break;
}
// 0x2B DEC HL
case 0x2B:
{
	regs.hl--;
	clock += 2;
	//instructionName = "DEC HL";
	break;	
}
// 0x2C INC L
case 0x2C:
{
	regs.l++;
	// flags
	// zero flag
	if (regs.l == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag a 0
	regs.f &= 0xBF;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = (regs.l & 0x0F ? 0 : 1);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 

	clock++;
	//instructionName = "INC L";
	break;
}
// 0x2D DEC L
case 0x2D:
{
	regs.l--;
	// flags
	// zero flag
	if (regs.l == 0)
		regs.f |= 0x80;
	else
		regs.f &= 0x7F;
	// add/sub flag
	regs.f |= 0x40;
	// half carry flag
	// non ho idea di come funziona
    byte hFlag = ((regs.l & 0x0F) == 0x0F) ? 1 : 0);
    if (hFlag == 0)
    	regs.f &= ~0x20;
    else
    	regs.f |= 0x20; 
	clock++;
	//instructionName = "DEC L";
	break;
}
// 0x2E LD L,n
case 0x2E:
{
	regs.l = mmu.readByte(regs.pc++);
	clock += 2;
	// instructionName = "LD L, " + n;
	break;
}
// 0x2F CPL
case 0x2F:
{
	// inverte tutti i bit di A
	regs.a = ~regs.a;
	// flags: -11-
	regs.f |= 0x40 | 0x20;
	clock++;
	// instructionName = "CPL";
	break;
}
// 0x30 JR NC, n
case 0x30:
{
	regs.pc++;
	if (regs.f & 0x10 == 0)
	{	// jump
		regs.pc += mmu.readByte(regs.pc);
	}
	clock += 2;
	// instructionName = "JR NC, " + n;
	break;
}
// 0x31 LD SP, nn
case 0x31:
{
	regs.sp = mmu.readWord(regs.pc);
	regs.pc += 2;
	clock += 3;
	// instructionName = "LD SP, " + nn;
	break;
}
// 0x32 LDD (HL), A
case 0x32:
{
	mmu.writeByte(regs.hl, regs.a);
	regs.hl--;
	clock += 2;
	instructionName = "LDD (HL), A";
	break;
} 

// 0xC3 JP nn
case 0xC3:
{
	word address = mmu.readWord(regs.pc);
	regs.pc = address;
	clock += 4;
	//instructionName = std::string("JP ") << address;
	break;
}