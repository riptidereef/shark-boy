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
    opcodes[0xC0] = {"RET NZ",       &CPU::OP_RET_NZ};
    opcodes[0xC1] = {"POP BC",       &CPU::OP_POP_BC};
    opcodes[0xC2] = {"JP NZ, a16",   &CPU::OP_JP_NZ_a16};
    opcodes[0xC3] = {"JP a16",       &CPU::OP_JP_a16};
    opcodes[0xC4] = {"CALL NZ, a16", &CPU::OP_CALL_NZ_a16};
    opcodes[0xC5] = {"PUSH BC",      &CPU::OP_PUSH_BC};
    opcodes[0xC6] = {"ADD A, d8",    &CPU::OP_ADD_A_d8};
    opcodes[0xC7] = {"RST 00H",      &CPU::OP_RST_00H};
    opcodes[0xC8] = {"RET Z",        &CPU::OP_RET_Z};
    opcodes[0xC9] = {"RET",          &CPU::OP_RET};
    opcodes[0xCA] = {"JP Z, a16",    &CPU::OP_JP_Z_a16};
    opcodes[0xCB] = {"PREFIX CB",    &CPU::OP_CB_prefix};
    opcodes[0xCC] = {"CALL Z, a16",  &CPU::OP_CALL_Z_a16};
    opcodes[0xCD] = {"CALL a16",     &CPU::OP_CALL_a16};
    opcodes[0xCE] = {"ADC A, d8",    &CPU::OP_ADC_A_d8};
    opcodes[0xCF] = {"RST 08H",      &CPU::OP_RST_08H};
    opcodes[0xD0] = {"RET NC",       &CPU::OP_RET_NC};
    opcodes[0xD1] = {"POP DE",       &CPU::OP_POP_DE};
    opcodes[0xD2] = {"JP NC, a16",   &CPU::OP_JP_NC_a16};
    opcodes[0xD3] = {"UND D3",       &CPU::OP_UNDEFINED_D3};
    opcodes[0xD4] = {"CALL NC, a16", &CPU::OP_CALL_NC_a16};
    opcodes[0xD5] = {"PUSH DE",      &CPU::OP_PUSH_DE};
    opcodes[0xD6] = {"SUB d8",       &CPU::OP_SUB_d8};
    opcodes[0xD7] = {"RST 10H",      &CPU::OP_RST_10H};
    opcodes[0xD8] = {"RET C",        &CPU::OP_RET_C};
    opcodes[0xD9] = {"RETI",         &CPU::OP_RETI};
    opcodes[0xDA] = {"JP C, a16",    &CPU::OP_JP_C_a16};
    opcodes[0xDB] = {"UND DB",       &CPU::OP_UNDEFINED_DB};
    opcodes[0xDC] = {"CALL C, a16",  &CPU::OP_CALL_C_a16};
    opcodes[0xDD] = {"UND DD",       &CPU::OP_UNDEFINED_DD};
    opcodes[0xDE] = {"SBC A, d8",    &CPU::OP_SBC_A_d8};
    opcodes[0xDF] = {"RST 18H",      &CPU::OP_RST_18H};
    opcodes[0xE0] = {"LDH (a8), A",  &CPU::OP_LDH_a8_A};
    opcodes[0xE1] = {"POP HL",       &CPU::OP_POP_HL};
    opcodes[0xE2] = {"LD (C), A",    &CPU::OP_LD_aC_A};
    opcodes[0xE3] = {"UND E3",       &CPU::OP_UNDEFINED_E3};
    opcodes[0xE4] = {"UND E4",       &CPU::OP_UNDEFINED_E4};
    opcodes[0xE5] = {"PUSH HL",      &CPU::OP_PUSH_HL};
    opcodes[0xE6] = {"AND d8",       &CPU::OP_AND_d8};
    opcodes[0xE7] = {"RST 20H",      &CPU::OP_RST_20H};
    opcodes[0xE8] = {"ADD SP, r8",   &CPU::OP_ADD_SP_r8};
    opcodes[0xE9] = {"JP (HL)",      &CPU::OP_JP_HL};
    opcodes[0xEA] = {"LD (a16), A",  &CPU::OP_LD_a16_A};
    opcodes[0xEB] = {"UND EB",       &CPU::OP_UNDEFINED_EB};
    opcodes[0xEC] = {"UND EC",       &CPU::OP_UNDEFINED_EC};
    opcodes[0xED] = {"UND ED",       &CPU::OP_UNDEFINED_ED};
    opcodes[0xEE] = {"XOR d8",       &CPU::OP_XOR_d8};
    opcodes[0xEF] = {"RST 28H",      &CPU::OP_RST_28H};
    opcodes[0xF0] = {"LDH A, (a8)",  &CPU::OP_LDH_A_a8};
    opcodes[0xF1] = {"POP AF",       &CPU::OP_POP_AF};
    opcodes[0xF2] = {"LD A, (C)",    &CPU::OP_LD_A_aC};
    opcodes[0xF3] = {"DI",           &CPU::OP_DI};
    opcodes[0xF4] = {"UND F4",       &CPU::OP_UNDEFINED_F4};
    opcodes[0xF5] = {"PUSH AF",      &CPU::OP_PUSH_AF};
    opcodes[0xF6] = {"OR d8",        &CPU::OP_OR_d8};
    opcodes[0xF7] = {"RST 30H",      &CPU::OP_RST_30H};
    opcodes[0xF8] = {"LD HL, SP+r8", &CPU::OP_LD_HL_SP_r8};
    opcodes[0xF9] = {"LD SP, HL",    &CPU::OP_LD_SP_HL};
    opcodes[0xFA] = {"LD A, (a16)",  &CPU::OP_LD_A_a16};
    opcodes[0xFB] = {"EI",           &CPU::OP_EI};
    opcodes[0xFC] = {"UND FC",       &CPU::OP_UNDEFINED_FC};
    opcodes[0xFD] = {"UND FD",       &CPU::OP_UNDEFINED_FD};
    opcodes[0xFE] = {"CP d8",        &CPU::OP_CP_d8};
    opcodes[0xFF] = {"RST 38H",      &CPU::OP_RST_38H};

    extOpcodes[0x00] = {"RLC B",        &CPU::OP_RLC_B};
    extOpcodes[0x01] = {"RLC C",        &CPU::OP_RLC_C};
    extOpcodes[0x02] = {"RLC D",        &CPU::OP_RLC_D};
    extOpcodes[0x03] = {"RLC E",        &CPU::OP_RLC_E};
    extOpcodes[0x04] = {"RLC H",        &CPU::OP_RLC_H};
    extOpcodes[0x05] = {"RLC L",        &CPU::OP_RLC_L};
    extOpcodes[0x06] = {"RLC (HL)",     &CPU::OP_RLC_HL};
    extOpcodes[0x07] = {"RLC A",        &CPU::OP_RLC_A};
    extOpcodes[0x08] = {"RRC B",        &CPU::OP_RRC_B};
    extOpcodes[0x09] = {"RRC C",        &CPU::OP_RRC_C};
    extOpcodes[0x0A] = {"RRC D",        &CPU::OP_RRC_D};
    extOpcodes[0x0B] = {"RRC E",        &CPU::OP_RRC_E};
    extOpcodes[0x0C] = {"RRC H",        &CPU::OP_RRC_H};
    extOpcodes[0x0D] = {"RRC L",        &CPU::OP_RRC_L};
    extOpcodes[0x0E] = {"RRC (HL)",     &CPU::OP_RRC_HL};
    extOpcodes[0x0F] = {"RRC A",        &CPU::OP_RRC_A};
    extOpcodes[0x10] = {"RL B",         &CPU::OP_RL_B};
    extOpcodes[0x11] = {"RL C",         &CPU::OP_RL_C};
    extOpcodes[0x12] = {"RL D",         &CPU::OP_RL_D};
    extOpcodes[0x13] = {"RL E",         &CPU::OP_RL_E};
    extOpcodes[0x14] = {"RL H",         &CPU::OP_RL_H};
    extOpcodes[0x15] = {"RL L",         &CPU::OP_RL_L};
    extOpcodes[0x16] = {"RL (HL)",      &CPU::OP_RL_HL};
    extOpcodes[0x17] = {"RL A",         &CPU::OP_RL_A};
    extOpcodes[0x18] = {"RR B",         &CPU::OP_RR_B};
    extOpcodes[0x19] = {"RR C",         &CPU::OP_RR_C};
    extOpcodes[0x1A] = {"RR D",         &CPU::OP_RR_D};
    extOpcodes[0x1B] = {"RR E",         &CPU::OP_RR_E};
    extOpcodes[0x1C] = {"RR H",         &CPU::OP_RR_H};
    extOpcodes[0x1D] = {"RR L",         &CPU::OP_RR_L};
    extOpcodes[0x1E] = {"RR (HL)",      &CPU::OP_RR_HL};
    extOpcodes[0x1F] = {"RR A",         &CPU::OP_RR_A};
    extOpcodes[0x20] = {"SLA B",        &CPU::OP_SLA_B};
    extOpcodes[0x21] = {"SLA C",        &CPU::OP_SLA_C};
    extOpcodes[0x22] = {"SLA D",        &CPU::OP_SLA_D};
    extOpcodes[0x23] = {"SLA E",        &CPU::OP_SLA_E};
    extOpcodes[0x24] = {"SLA H",        &CPU::OP_SLA_H};
    extOpcodes[0x25] = {"SLA L",        &CPU::OP_SLA_L};
    extOpcodes[0x26] = {"SLA (HL)",     &CPU::OP_SLA_HL};
    extOpcodes[0x27] = {"SLA A",        &CPU::OP_SLA_A};
    extOpcodes[0x28] = {"SRA B",        &CPU::OP_SRA_B};
    extOpcodes[0x29] = {"SRA C",        &CPU::OP_SRA_C};
    extOpcodes[0x2A] = {"SRA D",        &CPU::OP_SRA_D};
    extOpcodes[0x2B] = {"SRA E",        &CPU::OP_SRA_E};
    extOpcodes[0x2C] = {"SRA H",        &CPU::OP_SRA_H};
    extOpcodes[0x2D] = {"SRA L",        &CPU::OP_SRA_L};
    extOpcodes[0x2E] = {"SRA (HL)",     &CPU::OP_SRA_HL};
    extOpcodes[0x2F] = {"SRA A",        &CPU::OP_SRA_A};
    extOpcodes[0x30] = {"SWAP B",       &CPU::OP_SWAP_B};
    extOpcodes[0x31] = {"SWAP C",       &CPU::OP_SWAP_C};
    extOpcodes[0x32] = {"SWAP D",       &CPU::OP_SWAP_D};
    extOpcodes[0x33] = {"SWAP E",       &CPU::OP_SWAP_E};
    extOpcodes[0x34] = {"SWAP H",       &CPU::OP_SWAP_H};
    extOpcodes[0x35] = {"SWAP L",       &CPU::OP_SWAP_L};
    extOpcodes[0x36] = {"SWAP (HL)",    &CPU::OP_SWAP_HL};
    extOpcodes[0x37] = {"SWAP A",       &CPU::OP_SWAP_A};
    extOpcodes[0x38] = {"SRL B",        &CPU::OP_SRL_B};
    extOpcodes[0x39] = {"SRL C",        &CPU::OP_SRL_C};
    extOpcodes[0x3A] = {"SRL D",        &CPU::OP_SRL_D};
    extOpcodes[0x3B] = {"SRL E",        &CPU::OP_SRL_E};
    extOpcodes[0x3C] = {"SRL H",        &CPU::OP_SRL_H};
    extOpcodes[0x3D] = {"SRL L",        &CPU::OP_SRL_L};
    extOpcodes[0x3E] = {"SRL (HL)",     &CPU::OP_SRL_HL};
    extOpcodes[0x3F] = {"SRL A",        &CPU::OP_SRL_A};
    extOpcodes[0x40] = {"BIT 0, B",     &CPU::OP_BIT_0_B};
    extOpcodes[0x41] = {"BIT 0, C",     &CPU::OP_BIT_0_C};
    extOpcodes[0x42] = {"BIT 0, D",     &CPU::OP_BIT_0_D};
    extOpcodes[0x43] = {"BIT 0, E",     &CPU::OP_BIT_0_E};
    extOpcodes[0x44] = {"BIT 0, H",     &CPU::OP_BIT_0_H};
    extOpcodes[0x45] = {"BIT 0, L",     &CPU::OP_BIT_0_L};
    extOpcodes[0x46] = {"BIT 0, (HL)",  &CPU::OP_BIT_0_HL};
    extOpcodes[0x47] = {"BIT 0, A",     &CPU::OP_BIT_0_A};
    extOpcodes[0x48] = {"BIT 1, B",     &CPU::OP_BIT_1_B};
    extOpcodes[0x49] = {"BIT 1, C",     &CPU::OP_BIT_1_C};
    extOpcodes[0x4A] = {"BIT 1, D",     &CPU::OP_BIT_1_D};
    extOpcodes[0x4B] = {"BIT 1, E",     &CPU::OP_BIT_1_E};
    extOpcodes[0x4C] = {"BIT 1, H",     &CPU::OP_BIT_1_H};
    extOpcodes[0x4D] = {"BIT 1, L",     &CPU::OP_BIT_1_L};
    extOpcodes[0x4E] = {"BIT 1, (HL)",  &CPU::OP_BIT_1_HL};
    extOpcodes[0x4F] = {"BIT 1, A",     &CPU::OP_BIT_1_A};
    extOpcodes[0x50] = {"BIT 2, B",     &CPU::OP_BIT_2_B};
    extOpcodes[0x51] = {"BIT 2, C",     &CPU::OP_BIT_2_C};
    extOpcodes[0x52] = {"BIT 2, D",     &CPU::OP_BIT_2_D};
    extOpcodes[0x53] = {"BIT 2, E",     &CPU::OP_BIT_2_E};
    extOpcodes[0x54] = {"BIT 2, H",     &CPU::OP_BIT_2_H};
    extOpcodes[0x55] = {"BIT 2, L",     &CPU::OP_BIT_2_L};
    extOpcodes[0x56] = {"BIT 2, (HL)",  &CPU::OP_BIT_2_HL};
    extOpcodes[0x57] = {"BIT 2, A",     &CPU::OP_BIT_2_A};
    extOpcodes[0x58] = {"BIT 3, B",     &CPU::OP_BIT_3_B};
    extOpcodes[0x59] = {"BIT 3, C",     &CPU::OP_BIT_3_C};
    extOpcodes[0x5A] = {"BIT 3, D",     &CPU::OP_BIT_3_D};
    extOpcodes[0x5B] = {"BIT 3, E",     &CPU::OP_BIT_3_E};
    extOpcodes[0x5C] = {"BIT 3, H",     &CPU::OP_BIT_3_H};
    extOpcodes[0x5D] = {"BIT 3, L",     &CPU::OP_BIT_3_L};
    extOpcodes[0x5E] = {"BIT 3, (HL)",  &CPU::OP_BIT_3_HL};
    extOpcodes[0x5F] = {"BIT 3, A",     &CPU::OP_BIT_3_A};
    extOpcodes[0x60] = {"BIT 4, B",     &CPU::OP_BIT_4_B};
    extOpcodes[0x61] = {"BIT 4, C",     &CPU::OP_BIT_4_C};
    extOpcodes[0x62] = {"BIT 4, D",     &CPU::OP_BIT_4_D};
    extOpcodes[0x63] = {"BIT 4, E",     &CPU::OP_BIT_4_E};
    extOpcodes[0x64] = {"BIT 4, H",     &CPU::OP_BIT_4_H};
    extOpcodes[0x65] = {"BIT 4, L",     &CPU::OP_BIT_4_L};
    extOpcodes[0x66] = {"BIT 4, (HL)",  &CPU::OP_BIT_4_HL};
    extOpcodes[0x67] = {"BIT 4, A",     &CPU::OP_BIT_4_A};
    extOpcodes[0x68] = {"BIT 5, B",     &CPU::OP_BIT_5_B};
    extOpcodes[0x69] = {"BIT 5, C",     &CPU::OP_BIT_5_C};
    extOpcodes[0x6A] = {"BIT 5, D",     &CPU::OP_BIT_5_D};
    extOpcodes[0x6B] = {"BIT 5, E",     &CPU::OP_BIT_5_E};
    extOpcodes[0x6C] = {"BIT 5, H",     &CPU::OP_BIT_5_H};
    extOpcodes[0x6D] = {"BIT 5, L",     &CPU::OP_BIT_5_L};
    extOpcodes[0x6E] = {"BIT 5, (HL)",  &CPU::OP_BIT_5_HL};
    extOpcodes[0x6F] = {"BIT 5, A",     &CPU::OP_BIT_5_A};
    extOpcodes[0x70] = {"BIT 6, B",     &CPU::OP_BIT_6_B};
    extOpcodes[0x71] = {"BIT 6, C",     &CPU::OP_BIT_6_C};
    extOpcodes[0x72] = {"BIT 6, D",     &CPU::OP_BIT_6_D};
    extOpcodes[0x73] = {"BIT 6, E",     &CPU::OP_BIT_6_E};
    extOpcodes[0x74] = {"BIT 6, H",     &CPU::OP_BIT_6_H};
    extOpcodes[0x75] = {"BIT 6, L",     &CPU::OP_BIT_6_L};
    extOpcodes[0x76] = {"BIT 6, (HL)",  &CPU::OP_BIT_6_HL};
    extOpcodes[0x77] = {"BIT 6, A",     &CPU::OP_BIT_6_A};
    extOpcodes[0x78] = {"BIT 7, B",     &CPU::OP_BIT_7_B};
    extOpcodes[0x79] = {"BIT 7, C",     &CPU::OP_BIT_7_C};
    extOpcodes[0x7A] = {"BIT 7, D",     &CPU::OP_BIT_7_D};
    extOpcodes[0x7B] = {"BIT 7, E",     &CPU::OP_BIT_7_E};
    extOpcodes[0x7C] = {"BIT 7, H",     &CPU::OP_BIT_7_H};
    extOpcodes[0x7D] = {"BIT 7, L",     &CPU::OP_BIT_7_L};
    extOpcodes[0x7E] = {"BIT 7, (HL)",  &CPU::OP_BIT_7_HL};
    extOpcodes[0x7F] = {"BIT 7, A",     &CPU::OP_BIT_7_A};
    extOpcodes[0x80] = {"RES 0, B",     &CPU::OP_RES_0_B};
    extOpcodes[0x81] = {"RES 0, C",     &CPU::OP_RES_0_C};
    extOpcodes[0x82] = {"RES 0, D",     &CPU::OP_RES_0_D};
    extOpcodes[0x83] = {"RES 0, E",     &CPU::OP_RES_0_E};
    extOpcodes[0x84] = {"RES 0, H",     &CPU::OP_RES_0_H};
    extOpcodes[0x85] = {"RES 0, L",     &CPU::OP_RES_0_L};
    extOpcodes[0x86] = {"RES 0, (HL)",  &CPU::OP_RES_0_HL};
    extOpcodes[0x87] = {"RES 0, A",     &CPU::OP_RES_0_A};
    extOpcodes[0x88] = {"RES 1, B",     &CPU::OP_RES_1_B};
    extOpcodes[0x89] = {"RES 1, C",     &CPU::OP_RES_1_C};
    extOpcodes[0x8A] = {"RES 1, D",     &CPU::OP_RES_1_D};
    extOpcodes[0x8B] = {"RES 1, E",     &CPU::OP_RES_1_E};
    extOpcodes[0x8C] = {"RES 1, H",     &CPU::OP_RES_1_H};
    extOpcodes[0x8D] = {"RES 1, L",     &CPU::OP_RES_1_L};
    extOpcodes[0x8E] = {"RES 1, (HL)",  &CPU::OP_RES_1_HL};
    extOpcodes[0x8F] = {"RES 1, A",     &CPU::OP_RES_1_A};
    extOpcodes[0x90] = {"RES 2, B",     &CPU::OP_RES_2_B};
    extOpcodes[0x91] = {"RES 2, C",     &CPU::OP_RES_2_C};
    extOpcodes[0x92] = {"RES 2, D",     &CPU::OP_RES_2_D};
    extOpcodes[0x93] = {"RES 2, E",     &CPU::OP_RES_2_E};
    extOpcodes[0x94] = {"RES 2, H",     &CPU::OP_RES_2_H};
    extOpcodes[0x95] = {"RES 2, L",     &CPU::OP_RES_2_L};
    extOpcodes[0x96] = {"RES 2, (HL)",  &CPU::OP_RES_2_HL};
    extOpcodes[0x97] = {"RES 2, A",     &CPU::OP_RES_2_A};
    extOpcodes[0x98] = {"RES 3, B",     &CPU::OP_RES_3_B};
    extOpcodes[0x99] = {"RES 3, C",     &CPU::OP_RES_3_C};
    extOpcodes[0x9A] = {"RES 3, D",     &CPU::OP_RES_3_D};
    extOpcodes[0x9B] = {"RES 3, E",     &CPU::OP_RES_3_E};
    extOpcodes[0x9C] = {"RES 3, H",     &CPU::OP_RES_3_H};
    extOpcodes[0x9D] = {"RES 3, L",     &CPU::OP_RES_3_L};
    extOpcodes[0x9E] = {"RES 3, (HL)",  &CPU::OP_RES_3_HL};
    extOpcodes[0x9F] = {"RES 3, A",     &CPU::OP_RES_3_A};
    extOpcodes[0xA0] = {"RES 4, B",     &CPU::OP_RES_4_B};
    extOpcodes[0xA1] = {"RES 4, C",     &CPU::OP_RES_4_C};
    extOpcodes[0xA2] = {"RES 4, D",     &CPU::OP_RES_4_D};
    extOpcodes[0xA3] = {"RES 4, E",     &CPU::OP_RES_4_E};
    extOpcodes[0xA4] = {"RES 4, H",     &CPU::OP_RES_4_H};
    extOpcodes[0xA5] = {"RES 4, L",     &CPU::OP_RES_4_L};
    extOpcodes[0xA6] = {"RES 4, (HL)",  &CPU::OP_RES_4_HL};
    extOpcodes[0xA7] = {"RES 4, A",     &CPU::OP_RES_4_A};
    extOpcodes[0xA8] = {"RES 5, B",     &CPU::OP_RES_5_B};
    extOpcodes[0xA9] = {"RES 5, C",     &CPU::OP_RES_5_C};
    extOpcodes[0xAA] = {"RES 5, D",     &CPU::OP_RES_5_D};
    extOpcodes[0xAB] = {"RES 5, E",     &CPU::OP_RES_5_E};
    extOpcodes[0xAC] = {"RES 5, H",     &CPU::OP_RES_5_H};
    extOpcodes[0xAD] = {"RES 5, L",     &CPU::OP_RES_5_L};
    extOpcodes[0xAE] = {"RES 5, (HL)",  &CPU::OP_RES_5_HL};
    extOpcodes[0xAF] = {"RES 5, A",     &CPU::OP_RES_5_A};
    extOpcodes[0xB0] = {"RES 6, B",     &CPU::OP_RES_6_B};
    extOpcodes[0xB1] = {"RES 6, C",     &CPU::OP_RES_6_C};
    extOpcodes[0xB2] = {"RES 6, D",     &CPU::OP_RES_6_D};
    extOpcodes[0xB3] = {"RES 6, E",     &CPU::OP_RES_6_E};
    extOpcodes[0xB4] = {"RES 6, H",     &CPU::OP_RES_6_H};
    extOpcodes[0xB5] = {"RES 6, L",     &CPU::OP_RES_6_L};
    extOpcodes[0xB6] = {"RES 6, (HL)",  &CPU::OP_RES_6_HL};
    extOpcodes[0xB7] = {"RES 6, A",     &CPU::OP_RES_6_A};
    extOpcodes[0xB8] = {"RES 7, B",     &CPU::OP_RES_7_B};
    extOpcodes[0xB9] = {"RES 7, C",     &CPU::OP_RES_7_C};
    extOpcodes[0xBA] = {"RES 7, D",     &CPU::OP_RES_7_D};
    extOpcodes[0xBB] = {"RES 7, E",     &CPU::OP_RES_7_E};
    extOpcodes[0xBC] = {"RES 7, H",     &CPU::OP_RES_7_H};
    extOpcodes[0xBD] = {"RES 7, L",     &CPU::OP_RES_7_L};
    extOpcodes[0xBE] = {"RES 7, (HL)",  &CPU::OP_RES_7_HL};
    extOpcodes[0xBF] = {"RES 7, A",     &CPU::OP_RES_7_A};
    extOpcodes[0xC0] = {"SET 0, B",     &CPU::OP_SET_0_B};
    extOpcodes[0xC1] = {"SET 0, C",     &CPU::OP_SET_0_C};
    extOpcodes[0xC2] = {"SET 0, D",     &CPU::OP_SET_0_D};
    extOpcodes[0xC3] = {"SET 0, E",     &CPU::OP_SET_0_E};
    extOpcodes[0xC4] = {"SET 0, H",     &CPU::OP_SET_0_H};
    extOpcodes[0xC5] = {"SET 0, L",     &CPU::OP_SET_0_L};
    extOpcodes[0xC6] = {"SET 0, (HL)",  &CPU::OP_SET_0_HL};
    extOpcodes[0xC7] = {"SET 0, A",     &CPU::OP_SET_0_A};
    extOpcodes[0xC8] = {"SET 1, B",     &CPU::OP_SET_1_B};
    extOpcodes[0xC9] = {"SET 1, C",     &CPU::OP_SET_1_C};
    extOpcodes[0xCA] = {"SET 1, D",     &CPU::OP_SET_1_D};
    extOpcodes[0xCB] = {"SET 1, E",     &CPU::OP_SET_1_E};
    extOpcodes[0xCC] = {"SET 1, H",     &CPU::OP_SET_1_H};
    extOpcodes[0xCD] = {"SET 1, L",     &CPU::OP_SET_1_L};
    extOpcodes[0xCE] = {"SET 1, (HL)",  &CPU::OP_SET_1_HL};
    extOpcodes[0xCF] = {"SET 1, A",     &CPU::OP_SET_1_A};
    extOpcodes[0xD0] = {"SET 2, B",     &CPU::OP_SET_2_B};
    extOpcodes[0xD1] = {"SET 2, C",     &CPU::OP_SET_2_C};
    extOpcodes[0xD2] = {"SET 2, D",     &CPU::OP_SET_2_D};
    extOpcodes[0xD3] = {"SET 2, E",     &CPU::OP_SET_2_E};
    extOpcodes[0xD4] = {"SET 2, H",     &CPU::OP_SET_2_H};
    extOpcodes[0xD5] = {"SET 2, L",     &CPU::OP_SET_2_L};
    extOpcodes[0xD6] = {"SET 2, (HL)",  &CPU::OP_SET_2_HL};
    extOpcodes[0xD7] = {"SET 2, A",     &CPU::OP_SET_2_A};
    extOpcodes[0xD8] = {"SET 3, B",     &CPU::OP_SET_3_B};
    extOpcodes[0xD9] = {"SET 3, C",     &CPU::OP_SET_3_C};
    extOpcodes[0xDA] = {"SET 3, D",     &CPU::OP_SET_3_D};
    extOpcodes[0xDB] = {"SET 3, E",     &CPU::OP_SET_3_E};
    extOpcodes[0xDC] = {"SET 3, H",     &CPU::OP_SET_3_H};
    extOpcodes[0xDD] = {"SET 3, L",     &CPU::OP_SET_3_L};
    extOpcodes[0xDE] = {"SET 3, (HL)",  &CPU::OP_SET_3_HL};
    extOpcodes[0xDF] = {"SET 3, A",     &CPU::OP_SET_3_A};
    extOpcodes[0xE0] = {"SET 4, B",     &CPU::OP_SET_4_B};
    extOpcodes[0xE1] = {"SET 4, C",     &CPU::OP_SET_4_C};
    extOpcodes[0xE2] = {"SET 4, D",     &CPU::OP_SET_4_D};
    extOpcodes[0xE3] = {"SET 4, E",     &CPU::OP_SET_4_E};
    extOpcodes[0xE4] = {"SET 4, H",     &CPU::OP_SET_4_H};
    extOpcodes[0xE5] = {"SET 4, L",     &CPU::OP_SET_4_L};
    extOpcodes[0xE6] = {"SET 4, (HL)",  &CPU::OP_SET_4_HL};
    extOpcodes[0xE7] = {"SET 4, A",     &CPU::OP_SET_4_A};
    extOpcodes[0xE8] = {"SET 5, B",     &CPU::OP_SET_5_B};
    extOpcodes[0xE9] = {"SET 5, C",     &CPU::OP_SET_5_C};
    extOpcodes[0xEA] = {"SET 5, D",     &CPU::OP_SET_5_D};
    extOpcodes[0xEB] = {"SET 5, E",     &CPU::OP_SET_5_E};
    extOpcodes[0xEC] = {"SET 5, H",     &CPU::OP_SET_5_H};
    extOpcodes[0xED] = {"SET 5, L",     &CPU::OP_SET_5_L};
    extOpcodes[0xEE] = {"SET 5, (HL)",  &CPU::OP_SET_5_HL};
    extOpcodes[0xEF] = {"SET 5, A",     &CPU::OP_SET_5_A};
    extOpcodes[0xF0] = {"SET 6, B",     &CPU::OP_SET_6_B};
    extOpcodes[0xF1] = {"SET 6, C",     &CPU::OP_SET_6_C};
    extOpcodes[0xF2] = {"SET 6, D",     &CPU::OP_SET_6_D};
    extOpcodes[0xF3] = {"SET 6, E",     &CPU::OP_SET_6_E};
    extOpcodes[0xF4] = {"SET 6, H",     &CPU::OP_SET_6_H};
    extOpcodes[0xF5] = {"SET 6, L",     &CPU::OP_SET_6_L};
    extOpcodes[0xF6] = {"SET 6, (HL)",  &CPU::OP_SET_6_HL};
    extOpcodes[0xF7] = {"SET 6, A",     &CPU::OP_SET_6_A};
    extOpcodes[0xF8] = {"SET 7, B",     &CPU::OP_SET_7_B};
    extOpcodes[0xF9] = {"SET 7, C",     &CPU::OP_SET_7_C};
    extOpcodes[0xFA] = {"SET 7, D",     &CPU::OP_SET_7_D};
    extOpcodes[0xFB] = {"SET 7, E",     &CPU::OP_SET_7_E};
    extOpcodes[0xFC] = {"SET 7, H",     &CPU::OP_SET_7_H};
    extOpcodes[0xFD] = {"SET 7, L",     &CPU::OP_SET_7_L};
    extOpcodes[0xFE] = {"SET 7, (HL)",  &CPU::OP_SET_7_HL};
    extOpcodes[0xFF] = {"SET 7, A",     &CPU::OP_SET_7_A};
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

void CPU::rlc8(u8& reg) {
    u8 res = (reg << 1) | ((reg >> 7) & 0x01);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(((reg >> 7) & 0x01));
    reg = res;
}

void CPU::rrc8(u8& reg) {
    u8 res = ((reg & 0x01)) << 7 | (reg >> 1);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(reg & 0x01);
    reg = res;
}

void CPU::rl8(u8& reg) {
    u8 res = (reg << 1) | (getC() & 0x01);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(((reg >> 7) & 0x01));
    reg = res;
}

void CPU::rr8(u8& reg) {
    u8 res = ((getC() & 0x01) << 7) | (reg >> 1);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(reg & 0x01);
    reg = res;
}

void CPU::sla8(u8& reg) {
    u8 res = (reg << 1);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC((reg >> 7) & 0x01);
    reg = res;
}

void CPU::sra8(u8& reg) {
    u8 msb = reg & 0x80;
    u8 res = msb | (reg >> 1);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(reg & 0x01);
    reg = res;
}

void CPU::swap8(u8& reg) {
    u8 res = ((reg & 0x0F) << 4) | ((reg & 0xF0) >> 4);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(0);
    reg = res;
}

void CPU::srl8(u8& reg) {
    u8 res = (reg >> 1);
    setZ(res == 0);
    setN(0);
    setH(0);
    setC(reg & 0x01);
    reg = res;
}

void CPU::bit8(u8 bit, u8 val) {
    setZ((val & (1 << bit)) == 0);
    setN(0);
    setH(1);
}

void CPU::res8(u8 bit, u8& reg) {
    reg &= ~(1 << bit);
}

void CPU::set8(u8 bit, u8& reg) {
    reg |= (1 << bit);
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