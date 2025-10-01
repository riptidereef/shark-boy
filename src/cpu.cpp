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
    opcodes[0x40] = {"LD B, B",      &CPU::OP_LD_B_B};
    opcodes[0x41] = {"LD B, C",      &CPU::OP_LD_B_C};
    opcodes[0x42] = {"LD B, D",      &CPU::OP_LD_B_D};
    opcodes[0x43] = {"LD B, E",      &CPU::OP_LD_B_E};
    opcodes[0x44] = {"LD B, H",      &CPU::OP_LD_B_H};
    opcodes[0x45] = {"LD B, L",      &CPU::OP_LD_B_L};
    opcodes[0x46] = {"LD B, (HL)",   &CPU::OP_LD_B_HL};
    opcodes[0x47] = {"LD B, A",      &CPU::OP_LD_B_A};
    opcodes[0x48] = {"LD C, B",      &CPU::OP_LD_C_B};
    opcodes[0x49] = {"LD C, C",      &CPU::OP_LD_C_C};
    opcodes[0x4A] = {"LD C, D",      &CPU::OP_LD_C_D};
    opcodes[0x4B] = {"LD C, E",      &CPU::OP_LD_C_E};
    opcodes[0x4C] = {"LD C, H",      &CPU::OP_LD_C_H};
    opcodes[0x4D] = {"LD C, L",      &CPU::OP_LD_C_L};
    opcodes[0x4E] = {"LD C, (HL)",   &CPU::OP_LD_C_HL};
    opcodes[0x4F] = {"LD C, A",      &CPU::OP_LD_C_A};
    opcodes[0x50] = {"LD D, B",      &CPU::OP_LD_D_B};
    opcodes[0x51] = {"LD D, C",      &CPU::OP_LD_D_C};
    opcodes[0x52] = {"LD D, D",      &CPU::OP_LD_D_D};
    opcodes[0x53] = {"LD D, E",      &CPU::OP_LD_D_E};
    opcodes[0x54] = {"LD D, H",      &CPU::OP_LD_D_H};
    opcodes[0x55] = {"LD D, L",      &CPU::OP_LD_D_L};
    opcodes[0x56] = {"LD D, (HL)",   &CPU::OP_LD_D_HL};
    opcodes[0x57] = {"LD D, A",      &CPU::OP_LD_D_A};
    opcodes[0x58] = {"LD E, B",      &CPU::OP_LD_E_B};
    opcodes[0x59] = {"LD E, C",      &CPU::OP_LD_E_C};
    opcodes[0x5A] = {"LD E, D",      &CPU::OP_LD_E_D};
    opcodes[0x5B] = {"LD E, E",      &CPU::OP_LD_E_E};
    opcodes[0x5C] = {"LD E, H",      &CPU::OP_LD_E_H};
    opcodes[0x5D] = {"LD E, L",      &CPU::OP_LD_E_L};
    opcodes[0x5E] = {"LD E, (HL)",   &CPU::OP_LD_E_HL};
    opcodes[0x5F] = {"LD E, A",      &CPU::OP_LD_E_A};
    opcodes[0x60] = {"LD H, B",      &CPU::OP_LD_H_B};
    opcodes[0x61] = {"LD H, C",      &CPU::OP_LD_H_C};
    opcodes[0x62] = {"LD H, D",      &CPU::OP_LD_H_D};
    opcodes[0x63] = {"LD H, E",      &CPU::OP_LD_H_E};
    opcodes[0x64] = {"LD H, H",      &CPU::OP_LD_H_H};
    opcodes[0x65] = {"LD H, L",      &CPU::OP_LD_H_L};
    opcodes[0x66] = {"LD H, (HL)",   &CPU::OP_LD_H_HL};
    opcodes[0x67] = {"LD H, A",      &CPU::OP_LD_H_A};
    opcodes[0x68] = {"LD L, B",      &CPU::OP_LD_L_B};
    opcodes[0x69] = {"LD L, C",      &CPU::OP_LD_L_C};
    opcodes[0x6A] = {"LD L, D",      &CPU::OP_LD_L_D};
    opcodes[0x6B] = {"LD L, E",      &CPU::OP_LD_L_E};
    opcodes[0x6C] = {"LD L, H",      &CPU::OP_LD_L_H};
    opcodes[0x6D] = {"LD L, L",      &CPU::OP_LD_L_L};
    opcodes[0x6E] = {"LD L, (HL)",   &CPU::OP_LD_L_HL};
    opcodes[0x6F] = {"LD L, A",      &CPU::OP_LD_L_A};
    opcodes[0x70] = {"LD (HL), B",   &CPU::OP_LD_HL_B};
    opcodes[0x71] = {"LD (HL), C",   &CPU::OP_LD_HL_C};
    opcodes[0x72] = {"LD (HL), D",   &CPU::OP_LD_HL_D};
    opcodes[0x73] = {"LD (HL), E",   &CPU::OP_LD_HL_E};
    opcodes[0x74] = {"LD (HL), H",   &CPU::OP_LD_HL_H};
    opcodes[0x75] = {"LD (HL), L",   &CPU::OP_LD_HL_L};
    opcodes[0x76] = {"HALT",         &CPU::OP_HALT};
    opcodes[0x77] = {"LD (HL), A",   &CPU::OP_LD_HL_A};
    opcodes[0x78] = {"LD A, B",      &CPU::OP_LD_A_B};
    opcodes[0x79] = {"LD A, C",      &CPU::OP_LD_A_C};
    opcodes[0x7A] = {"LD A, D",      &CPU::OP_LD_A_D};
    opcodes[0x7B] = {"LD A, E",      &CPU::OP_LD_A_E};
    opcodes[0x7C] = {"LD A, H",      &CPU::OP_LD_A_H};
    opcodes[0x7D] = {"LD A, L",      &CPU::OP_LD_A_L};
    opcodes[0x7E] = {"LD A, (HL)",   &CPU::OP_LD_A_HL};
    opcodes[0x7F] = {"LD A, A",      &CPU::OP_LD_A_A};
    opcodes[0x80] = {"ADD A, B",     &CPU::OP_ADD_A_B};
    opcodes[0x81] = {"ADD A, C",     &CPU::OP_ADD_A_C};
    opcodes[0x82] = {"ADD A, D",     &CPU::OP_ADD_A_D};
    opcodes[0x83] = {"ADD A, E",     &CPU::OP_ADD_A_E};
    opcodes[0x84] = {"ADD A, H",     &CPU::OP_ADD_A_H};
    opcodes[0x85] = {"ADD A, L",     &CPU::OP_ADD_A_L};
    opcodes[0x86] = {"ADD A, (HL)",  &CPU::OP_ADD_A_HL};
    opcodes[0x87] = {"ADD A, A",     &CPU::OP_ADD_A_A};
    opcodes[0x88] = {"ADC A, B",     &CPU::OP_ADC_A_B};
    opcodes[0x89] = {"ADC A, C",     &CPU::OP_ADC_A_C};
    opcodes[0x8A] = {"ADC A, D",     &CPU::OP_ADC_A_D};
    opcodes[0x8B] = {"ADC A, E",     &CPU::OP_ADC_A_E};
    opcodes[0x8C] = {"ADC A, H",     &CPU::OP_ADC_A_H};
    opcodes[0x8D] = {"ADC A, L",     &CPU::OP_ADC_A_L};
    opcodes[0x8E] = {"ADC A, (HL)",  &CPU::OP_ADC_A_HL};
    opcodes[0x8F] = {"ADC A, A",     &CPU::OP_ADC_A_A};
    opcodes[0x90] = {"SUB B",        &CPU::OP_SUB_B};
    opcodes[0x91] = {"SUB C",        &CPU::OP_SUB_C};
    opcodes[0x92] = {"SUB D",        &CPU::OP_SUB_D};
    opcodes[0x93] = {"SUB E",        &CPU::OP_SUB_E};
    opcodes[0x94] = {"SUB H",        &CPU::OP_SUB_H};
    opcodes[0x95] = {"SUB L",        &CPU::OP_SUB_L};
    opcodes[0x96] = {"SUB (HL)",     &CPU::OP_SUB_HL};
    opcodes[0x97] = {"SUB A",        &CPU::OP_SUB_A};
    opcodes[0x98] = {"SBC A, B",     &CPU::OP_SBC_A_B};
    opcodes[0x99] = {"SBC A, C",     &CPU::OP_SBC_A_C};
    opcodes[0x9A] = {"SBC A, D",     &CPU::OP_SBC_A_D};
    opcodes[0x9B] = {"SBC A, E",     &CPU::OP_SBC_A_E};
    opcodes[0x9C] = {"SBC A, H",     &CPU::OP_SBC_A_H};
    opcodes[0x9D] = {"SBC A, L",     &CPU::OP_SBC_A_L};
    opcodes[0x9E] = {"SBC A, (HL)",  &CPU::OP_SBC_A_HL};
    opcodes[0x9F] = {"SBC A, A",     &CPU::OP_SBC_A_A};
    opcodes[0xA0] = {"AND B",        &CPU::OP_AND_B};
    opcodes[0xA1] = {"AND C",        &CPU::OP_AND_C};
    opcodes[0xA2] = {"AND D",        &CPU::OP_AND_D};
    opcodes[0xA3] = {"AND E",        &CPU::OP_AND_E};
    opcodes[0xA4] = {"AND H",        &CPU::OP_AND_H};
    opcodes[0xA5] = {"AND L",        &CPU::OP_AND_L};
    opcodes[0xA6] = {"AND (HL)",     &CPU::OP_AND_HL};
    opcodes[0xA7] = {"AND A",        &CPU::OP_AND_A};
    opcodes[0xA8] = {"XOR B",        &CPU::OP_XOR_B};
    opcodes[0xA9] = {"XOR C",        &CPU::OP_XOR_C};
    opcodes[0xAA] = {"XOR D",        &CPU::OP_XOR_D};
    opcodes[0xAB] = {"XOR E",        &CPU::OP_XOR_E};
    opcodes[0xAC] = {"XOR H",        &CPU::OP_XOR_H};
    opcodes[0xAD] = {"XOR L",        &CPU::OP_XOR_L};
    opcodes[0xAE] = {"XOR (HL)",     &CPU::OP_XOR_HL};
    opcodes[0xAF] = {"XOR A",        &CPU::OP_XOR_A};
    opcodes[0xB0] = {"OR B",         &CPU::OP_OR_B};
    opcodes[0xB1] = {"OR C",         &CPU::OP_OR_C};
    opcodes[0xB2] = {"OR D",         &CPU::OP_OR_D};
    opcodes[0xB3] = {"OR E",         &CPU::OP_OR_E};
    opcodes[0xB4] = {"OR H",         &CPU::OP_OR_H};
    opcodes[0xB5] = {"OR L",         &CPU::OP_OR_L};
    opcodes[0xB6] = {"OR (HL)",      &CPU::OP_OR_HL};
    opcodes[0xB7] = {"OR A",         &CPU::OP_OR_A};
    opcodes[0xB8] = {"CP B",         &CPU::OP_CP_B};
    opcodes[0xB9] = {"CP C",         &CPU::OP_CP_C};
    opcodes[0xBA] = {"CP D",         &CPU::OP_CP_D};
    opcodes[0xBB] = {"CP E",         &CPU::OP_CP_E};
    opcodes[0xBC] = {"CP H",         &CPU::OP_CP_H};
    opcodes[0xBD] = {"CP L",         &CPU::OP_CP_L};
    opcodes[0xBE] = {"CP (HL)",      &CPU::OP_CP_HL};
    opcodes[0xBF] = {"CP A",         &CPU::OP_CP_A};


    // Example later instruction
    opcodes[0xC3] = {"JP a16",       &CPU::OP_JP_a16};
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

void CPU::add16(u16& r1, u16 r2) {
    u32 res = static_cast<u32>(r1) + static_cast<u32>(r2);
    
    setN(0);
    setH(((r1 & 0x0FFF) + (r2 & 0x0FFF)) > 0x0FFF);
    setC(res > 0xFFFF);
    
    r1 = static_cast<u16>(res);
}

void CPU::add8(u8& r1, u8 r2) {
    u16 res = static_cast<u16>(r1) + static_cast<u16>(r2);

    setZ(static_cast<u8>(res) == 0);
    setN(0);
    setH(((r1 & 0xF) + (r2 & 0xF)) > 0xF);
    setC(res > 0xFF);

    r1 = static_cast<u8>(res);
}

void CPU::adc8(u8& r1, u8 r2) {
    u8 carry = getC();
    u16 res = static_cast<u16>(r1) + static_cast<u16>(r2) + carry;

    setZ(static_cast<u8>(res) == 0);
    setN(0);
    setH(((r1 & 0xF) + (r2 & 0xF) + carry) > 0xF);
    setC(res > 0xFF);

    r1 = static_cast<u8>(res);
}

void CPU::sub8(u8& r1, u8 r2) {
    u16 res = static_cast<u16>(r1) - static_cast<u16>(r2);

    setZ(static_cast<u8>(res) == 0);
    setN(1);
    setH((r1 & 0xF) < (r2 & 0xF));
    setC(r1 < r2);

    r1 = static_cast<u8>(res);
}

void CPU::sbc8(u8& r1, u8 r2) {
    u8 carry = getC();
    u16 res = static_cast<u16>(r1) - static_cast<u16>(r2) - carry;

    setZ(static_cast<u8>(res) == 0);
    setN(1);
    setH((r1 & 0xF) < (r2 & 0xF) + carry);
    setC((static_cast<u16>(r1) < static_cast<u16>(r2) + carry));

    r1 = static_cast<u8>(res);
}

void CPU::and8(u8& r1, u8 r2) {
    r1 &= r2;
    setZ(r1 == 0);
    setN(0);
    setH(1);
    setC(0);
}

void CPU::xor8(u8& r1, u8 r2) {
    r1 ^= r2;
    setZ(r1 == 0);
    setN(0);
    setH(0);
    setC(0);
}

void CPU::or8(u8& r1, u8 r2) {
    r1 |= r2;
    setZ(r1 == 0);
    setN(0);
    setH(0);
    setC(0);
}

void CPU::cp8(u8 r1, u8 r2) {
    u16 res = static_cast<u16>(r1) - static_cast<u16>(r2);

    setZ(static_cast<u8>(res) == 0);
    setN(1);
    setH((r1 & 0xF) < (r2 & 0xF));
    setC(r1 < r2);
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
        instr = extOpcodes[opcode];
    }
    else {
        instr = opcodes[opcode];
    }

    u32 cycles = instr.execute(this);
    cout << "0x" << right << uppercase << setfill('0') << setw(4) << hex << startPc << " ";
    cout << left << setw(14) << setfill(' ') << instr.name;
    cout << dec << ": " << cycles << "\n";
}