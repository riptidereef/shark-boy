#include "cpu.h"
#include <iostream>

void CPU::OP_NOP() {
    std::cout << "Executed NOP" << std::endl;
}

void CPU::OP_LD_BC_d16() {
    std::cout << "Executed LD BC, d16" << std::endl;
}

void CPU::OP_LD_BC_A() {
    std::cout << "Executed LD (BC), A" << std::endl;
}

void CPU::OP_INC_BC() {
    std::cout << "Executed INC BC" << std::endl;
}

void CPU::OP_INC_B() {
    std::cout << "Executed INC B" << std::endl;
}

void CPU::OP_DEC_B() {
    std::cout << "Executed DEC B" << std::endl;
}

void CPU::OP_LD_B_d8() {
    std::cout << "Executed LD B, d8" << std::endl;
}

void CPU::OP_RLCA() {
    std::cout << "Executed RLCA" << std::endl;
}

void CPU::OP_LD_a16_SP() {
    std::cout << "Executed LD (a16), SP" << std::endl;
}

void CPU::OP_ADD_HL_BC() {
    std::cout << "Executed ADD HL, BC" << std::endl;
}

void CPU::OP_LD_A_BC() {
    std::cout << "Executed LD A, (BC)" << std::endl;
}

void CPU::OP_DEC_BC() {
    std::cout << "Executed DEC BC" << std::endl;
}

void CPU::OP_INC_C() {
    std::cout << "Executed INC C" << std::endl;
}

void CPU::OP_DEC_C() {
    std::cout << "Executed DEC C" << std::endl;
}

void CPU::OP_LD_C_d8() {
    std::cout << "Executed LD C, d8" << std::endl;
}

void CPU::OP_RRCA() {
    std::cout << "Executed RRCA" << std::endl;
}

void CPU::OP_JP_a16() {
    std::cout << "Executed JP a16" << std::endl;
    u16 jpAddress = mmu->read16(pc);
    pc = jpAddress;
}