#include "cpu.h"
#include <iostream>
using namespace std;

CPU::CPU(MMU* mmu) {
    this->mmu = mmu;

    pc = 0x0100;
    sp = 0xFFFE;

    opcodes.fill(nullptr);
    cbOpcodes.fill(nullptr);

    opcodes[0x00] = &CPU::OP_NOP;

    opcodes[0xC3] = &CPU::OP_JP_a16;
}

void CPU::step() {
    u8 opcode = mmu->read8(pc);
    pc++;

    Instruction instr;
    if (opcode == 0xCB) {
        opcode = mmu->read8(pc);
        pc++;
        instr = cbOpcodes[opcode];
    }
    else {
        instr = opcodes[opcode];
    }

    if (instr) {
        (this->*instr)();
    }
    else {
        cout << "Instruction not found." << endl;
    }
}