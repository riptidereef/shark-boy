#include "cpu.h"
#include <iostream>
#include <iomanip>
using namespace std;

CPU::CPU(MMU* mmu) {
    this->mmu = mmu;

    regs.af = 0x01B0;
    regs.bc = 0x0013;
    regs.de = 0x00D8;
    regs.hl = 0x014D;
    sp = 0xFFFE;
    pc = 0x0100;

    opcodes[0x00] = {"NOP",          &CPU::OP_NOP};
    opcodes[0x01] = {"LD BC, d16",   &CPU::OP_LD_BC_d16};
    opcodes[0x02] = {"LD (BC), A",   &CPU::OP_LD_BC_A};
    opcodes[0x03] = {"INC BC",       &CPU::OP_INC_BC};
    opcodes[0x04] = {"INC B",        &CPU::OP_INC_B};
    opcodes[0x05] = {"DEC B",        &CPU::OP_DEC_B};
    opcodes[0x06] = {"LD B, d8",     &CPU::OP_LD_B_d8};
    opcodes[0x07] = {"RLCA",         &CPU::OP_RLCA};
    opcodes[0x08] = {"LD (a16), SP", &CPU::OP_LD_a16_SP};
    opcodes[0x09] = {"ADD HL, BC",   &CPU::OP_ADD_HL_BC};
    opcodes[0x0A] = {"LD A, (BC)",   &CPU::OP_LD_A_BC};
    opcodes[0x0B] = {"DEC BC",       &CPU::OP_DEC_BC};
    opcodes[0x0C] = {"INC C",        &CPU::OP_INC_C};
    opcodes[0x0D] = {"DEC C",        &CPU::OP_DEC_C};
    opcodes[0x0E] = {"LD C, d8",     &CPU::OP_LD_C_d8};
    opcodes[0x0F] = {"RRCA",         &CPU::OP_RRCA};
    opcodes[0x10] = {"STOP",         &CPU::OP_STOP};
    opcodes[0x11] = {"LD DE, d16",   &CPU::OP_LD_DE_d16};
    opcodes[0x12] = {"LD (DE), A",   &CPU::OP_LD_DE_A};
    opcodes[0x13] = {"INC DE",       &CPU::OP_INC_DE};
    opcodes[0x14] = {"INC D",        &CPU::OP_INC_D};
    opcodes[0x15] = {"DEC D",        &CPU::OP_DEC_D};
    opcodes[0x16] = {"LD D, d8",     &CPU::OP_LD_D_d8};
    opcodes[0x17] = {"RLA",          &CPU::OP_RLA};
    opcodes[0x18] = {"JR r8",        &CPU::OP_JR_r8};
    opcodes[0x19] = {"ADD HL, DE",   &CPU::OP_ADD_HL_DE};
    opcodes[0x1A] = {"LD A, (DE)",   &CPU::OP_LD_A_DE};
    opcodes[0x1B] = {"DEC DE",       &CPU::OP_DEC_DE};
    opcodes[0x1C] = {"INC E",        &CPU::OP_INC_E};
    opcodes[0x1D] = {"DEC E",        &CPU::OP_DEC_E};
    opcodes[0x1E] = {"LD E, d8",     &CPU::OP_LD_E_d8};
    opcodes[0x1F] = {"RRA",          &CPU::OP_RRA};
    opcodes[0x20] = {"JR NZ, r8",    &CPU::OP_JR_NZ_r8};
    opcodes[0x21] = {"LD HL, d16",   &CPU::OP_LD_HL_d16};
    opcodes[0x22] = {"LD (HL+), A",  &CPU::OP_LD_HLp_A};
    opcodes[0x23] = {"INC HL",       &CPU::OP_INC_HL};
    opcodes[0x24] = {"INC H",        &CPU::OP_INC_H};
    opcodes[0x25] = {"DEC H",        &CPU::OP_DEC_H};
    opcodes[0x26] = {"LD H, d8",     &CPU::OP_LD_H_d8};
    opcodes[0x27] = {"DAA",          &CPU::OP_DAA};
    opcodes[0x28] = {"JR Z, r8",     &CPU::OP_JR_Z_r8};
    opcodes[0x29] = {"ADD HL, HL",   &CPU::OP_ADD_HL_HL};
    opcodes[0x2A] = {"LD A, (HL+)",  &CPU::OP_LD_A_HLp};
    opcodes[0x2B] = {"DEC HL",       &CPU::OP_DEC_HL};
    opcodes[0x2C] = {"INC L",        &CPU::OP_INC_L};
    opcodes[0x2D] = {"DEC L",        &CPU::OP_DEC_L};
    opcodes[0x2E] = {"LD L, d8",     &CPU::OP_LD_L_d8};
    opcodes[0x2F] = {"CPL",          &CPU::OP_CPL};
    opcodes[0x30] = {"JR NC, r8",    &CPU::OP_JR_NC_r8};
    opcodes[0x31] = {"LD SP, d16",   &CPU::OP_LD_SP_d16};
    opcodes[0x32] = {"LD (HL-), A",  &CPU::OP_LD_HLm_A};
    opcodes[0x33] = {"INC SP",       &CPU::OP_INC_SP};
    opcodes[0x34] = {"INC (HL)",     &CPU::OP_INC_aHL};
    opcodes[0x35] = {"DEC (HL)",     &CPU::OP_DEC_aHL};
    opcodes[0x36] = {"LD (HL), d8",  &CPU::OP_LD_HL_d8};
    opcodes[0x37] = {"SCF",          &CPU::OP_SCF};
    opcodes[0x38] = {"JR C, r8",     &CPU::OP_JR_C_r8};
    opcodes[0x39] = {"ADD HL, SP",   &CPU::OP_ADD_HL_SP};
    opcodes[0x3A] = {"LD A, (HL-)",  &CPU::OP_LD_A_HLm};
    opcodes[0x3B] = {"DEC SP",       &CPU::OP_DEC_SP};
    opcodes[0x3C] = {"INC A",        &CPU::OP_INC_A};
    opcodes[0x3D] = {"DEC A",        &CPU::OP_DEC_A};
    opcodes[0x3E] = {"LD A, d8",     &CPU::OP_LD_A_d8};
    opcodes[0x3F] = {"CCF",          &CPU::OP_CCF};

    // Example later instruction
    opcodes[0xC3] = {"JP a16",      &CPU::OP_JP_a16};
}

u8 CPU::fetch8() {
    u8 nextByte = mmu->read8(pc);
    pc += 1;
    return nextByte;
}

u16 CPU::fetch16() {
    u16 nextWord = mmu->read16(pc);
    pc += 2;
    return nextWord;
}

u8 CPU::peek8() {
    u8 nextByte = mmu->read8(pc);
    return nextByte;
}

u16 CPU::peek16() {
    u16 nextWord = mmu->read16(pc);
    return nextWord;
}

void CPU::inc8(u8& r) {
    setH((r & 0x0F) == 0x0F);
    r++;
    setZ(r == 0);
    setN(0);
}

void CPU::dec8(u8& r) {
    setH((r & 0x0F) == 0x00);
    r--;
    setZ(r == 0);
    setN(1);
}

void CPU::add8(u8& r1, u8& r2) {
    
}

void CPU::add16(u16& r1, u16 r2) {
    u32 res = static_cast<u32>(r1) + static_cast<u32>(r2);

    setN(0);
    setH(((r1 & 0x0FFF) + (r2 & 0x0FFF)) > 0x0FFF);
    setC(res > 0xFFFF);

    r1 = static_cast<u16>(res);
}

u32 CPU::Instruction::execute(CPU* cpu) const {
    if (op) {
        return (cpu->*op)();
    }
    else {
        return 0;
    }
}

void CPU::step() {
    u8 opcode = mmu->read8(pc);
    u16 startPc = pc;
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

    u32 cycles = instr.execute(this);
    cout << "0x" << right << uppercase << setfill('0') << setw(4) << hex << startPc << " ";
    cout << left << setw(14) << setfill(' ') << instr.name;
    cout << dec << ": " << cycles << "\n";
}