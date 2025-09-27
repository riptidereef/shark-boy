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
    opcodes[0x01] = &CPU::OP_LD_BC_d16;
    opcodes[0x02] = &CPU::OP_LD_BC_A;
    opcodes[0x03] = &CPU::OP_INC_BC;
    opcodes[0x04] = &CPU::OP_INC_B;
    opcodes[0x05] = &CPU::OP_DEC_B;
    opcodes[0x06] = &CPU::OP_LD_B_d8;
    opcodes[0x07] = &CPU::OP_RLCA;
    opcodes[0x08] = &CPU::OP_LD_a16_SP;
    opcodes[0x09] = &CPU::OP_ADD_HL_BC;
    opcodes[0x0A] = &CPU::OP_LD_A_BC;
    opcodes[0x0B] = &CPU::OP_DEC_BC;
    opcodes[0x0C] = &CPU::OP_INC_C;
    opcodes[0x0D] = &CPU::OP_DEC_C;
    opcodes[0x0E] = &CPU::OP_LD_C_d8;
    opcodes[0x0F] = &CPU::OP_RRCA;
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