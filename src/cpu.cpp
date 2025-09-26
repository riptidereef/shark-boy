#include "cpu.h"

CPU::CPU(MMU* mmu) {
    this->mmu = mmu;

    pc = 0x0100;
    sp = 0xFFFE;
}

void CPU::step() {
    u8 opcode = mmu->read8(pc);
    pc++;

    
}