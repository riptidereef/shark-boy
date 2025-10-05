#include "cpu.h"
#include <iostream>

void CPU::updateOpcodeTables() {
    opcodes[0x00] = {"NOP",             &CPU::OP_NOP};
    opcodes[0x01] = {"LD BC, d16",      &CPU::OP_LD_BC_d16};
    opcodes[0x02] = {"LD (BC), A",      &CPU::OP_LD_BC_A};
    opcodes[0x03] = {"INC BC",          &CPU::OP_INC_BC};
    opcodes[0x04] = {"INC B",           &CPU::OP_INC_B};
    opcodes[0x05] = {"DEC B",           &CPU::OP_DEC_B};
    opcodes[0x06] = {"LD B, d8",        &CPU::OP_LD_B_d8};
    opcodes[0x07] = {"RLCA",            &CPU::OP_RLCA};
    opcodes[0x08] = {"LD (a16), SP",    &CPU::OP_LD_a16_SP};
    opcodes[0x09] = {"ADD HL, BC",      &CPU::OP_ADD_HL_BC};
    opcodes[0x0A] = {"LD A, (BC)",      &CPU::OP_LD_A_BC};
    opcodes[0x0B] = {"DEC BC",          &CPU::OP_DEC_BC};
    opcodes[0x0C] = {"INC C",           &CPU::OP_INC_C};
    opcodes[0x0D] = {"DEC C",           &CPU::OP_DEC_C};
    opcodes[0x0E] = {"LD C, d8",        &CPU::OP_LD_C_d8};
    opcodes[0x0F] = {"RRCA",            &CPU::OP_RRCA};
    opcodes[0x10] = {"STOP",            &CPU::OP_STOP};
    opcodes[0x11] = {"LD DE, d16",      &CPU::OP_LD_DE_d16};
    opcodes[0x12] = {"LD (DE), A",      &CPU::OP_LD_DE_A};
    opcodes[0x13] = {"INC DE",          &CPU::OP_INC_DE};
    opcodes[0x14] = {"INC D",           &CPU::OP_INC_D};
    opcodes[0x15] = {"DEC D",           &CPU::OP_DEC_D};
    opcodes[0x16] = {"LD D, d8",        &CPU::OP_LD_D_d8};
    opcodes[0x17] = {"RLA",             &CPU::OP_RLA};
    opcodes[0x18] = {"JR r8",           &CPU::OP_JR_r8};
    opcodes[0x19] = {"ADD HL, DE",      &CPU::OP_ADD_HL_DE};
    opcodes[0x1A] = {"LD A, (DE)",      &CPU::OP_LD_A_DE};
    opcodes[0x1B] = {"DEC DE",          &CPU::OP_DEC_DE};
    opcodes[0x1C] = {"INC E",           &CPU::OP_INC_E};
    opcodes[0x1D] = {"DEC E",           &CPU::OP_DEC_E};
    opcodes[0x1E] = {"LD E, d8",        &CPU::OP_LD_E_d8};
    opcodes[0x1F] = {"RRA",             &CPU::OP_RRA};
    opcodes[0x20] = {"JR NZ, r8",       &CPU::OP_JR_NZ_r8};
    opcodes[0x21] = {"LD HL, d16",      &CPU::OP_LD_HL_d16};
    opcodes[0x22] = {"LD (HL+), A",     &CPU::OP_LD_HLp_A};
    opcodes[0x23] = {"INC HL",          &CPU::OP_INC_HL};
    opcodes[0x24] = {"INC H",           &CPU::OP_INC_H};
    opcodes[0x25] = {"DEC H",           &CPU::OP_DEC_H};
    opcodes[0x26] = {"LD H, d8",        &CPU::OP_LD_H_d8};
    opcodes[0x27] = {"DAA",             &CPU::OP_DAA};
    opcodes[0x28] = {"JR Z, r8",        &CPU::OP_JR_Z_r8};
    opcodes[0x29] = {"ADD HL, HL",      &CPU::OP_ADD_HL_HL};
    opcodes[0x2A] = {"LD A, (HL+)",     &CPU::OP_LD_A_HLp};
    opcodes[0x2B] = {"DEC HL",          &CPU::OP_DEC_HL};
    opcodes[0x2C] = {"INC L",           &CPU::OP_INC_L};
    opcodes[0x2D] = {"DEC L",           &CPU::OP_DEC_L};
    opcodes[0x2E] = {"LD L, d8",        &CPU::OP_LD_L_d8};
    opcodes[0x2F] = {"CPL",             &CPU::OP_CPL};
    opcodes[0x30] = {"JR NC, r8",       &CPU::OP_JR_NC_r8};
    opcodes[0x31] = {"LD SP, d16",      &CPU::OP_LD_SP_d16};
    opcodes[0x32] = {"LD (HL-), A",     &CPU::OP_LD_HLm_A};
    opcodes[0x33] = {"INC SP",          &CPU::OP_INC_SP};
    opcodes[0x34] = {"INC (HL)",        &CPU::OP_INC_aHL};
    opcodes[0x35] = {"DEC (HL)",        &CPU::OP_DEC_aHL};
    opcodes[0x36] = {"LD (HL), d8",     &CPU::OP_LD_HL_d8};
    opcodes[0x37] = {"SCF",             &CPU::OP_SCF};
    opcodes[0x38] = {"JR C, r8",        &CPU::OP_JR_C_r8};
    opcodes[0x39] = {"ADD HL, SP",      &CPU::OP_ADD_HL_SP};
    opcodes[0x3A] = {"LD A, (HL-)",     &CPU::OP_LD_A_HLm};
    opcodes[0x3B] = {"DEC SP",          &CPU::OP_DEC_SP};
    opcodes[0x3C] = {"INC A",           &CPU::OP_INC_A};
    opcodes[0x3D] = {"DEC A",           &CPU::OP_DEC_A};
    opcodes[0x3E] = {"LD A, d8",        &CPU::OP_LD_A_d8};
    opcodes[0x3F] = {"CCF",             &CPU::OP_CCF};
    opcodes[0x40] = {"LD B, B",         &CPU::OP_LD_B_B};
    opcodes[0x41] = {"LD B, C",         &CPU::OP_LD_B_C};
    opcodes[0x42] = {"LD B, D",         &CPU::OP_LD_B_D};
    opcodes[0x43] = {"LD B, E",         &CPU::OP_LD_B_E};
    opcodes[0x44] = {"LD B, H",         &CPU::OP_LD_B_H};
    opcodes[0x45] = {"LD B, L",         &CPU::OP_LD_B_L};
    opcodes[0x46] = {"LD B, (HL)",      &CPU::OP_LD_B_HL};
    opcodes[0x47] = {"LD B, A",         &CPU::OP_LD_B_A};
    opcodes[0x48] = {"LD C, B",         &CPU::OP_LD_C_B};
    opcodes[0x49] = {"LD C, C",         &CPU::OP_LD_C_C};
    opcodes[0x4A] = {"LD C, D",         &CPU::OP_LD_C_D};
    opcodes[0x4B] = {"LD C, E",         &CPU::OP_LD_C_E};
    opcodes[0x4C] = {"LD C, H",         &CPU::OP_LD_C_H};
    opcodes[0x4D] = {"LD C, L",         &CPU::OP_LD_C_L};
    opcodes[0x4E] = {"LD C, (HL)",      &CPU::OP_LD_C_HL};
    opcodes[0x4F] = {"LD C, A",         &CPU::OP_LD_C_A};
    opcodes[0x50] = {"LD D, B",         &CPU::OP_LD_D_B};
    opcodes[0x51] = {"LD D, C",         &CPU::OP_LD_D_C};
    opcodes[0x52] = {"LD D, D",         &CPU::OP_LD_D_D};
    opcodes[0x53] = {"LD D, E",         &CPU::OP_LD_D_E};
    opcodes[0x54] = {"LD D, H",         &CPU::OP_LD_D_H};
    opcodes[0x55] = {"LD D, L",         &CPU::OP_LD_D_L};
    opcodes[0x56] = {"LD D, (HL)",      &CPU::OP_LD_D_HL};
    opcodes[0x57] = {"LD D, A",         &CPU::OP_LD_D_A};
    opcodes[0x58] = {"LD E, B",         &CPU::OP_LD_E_B};
    opcodes[0x59] = {"LD E, C",         &CPU::OP_LD_E_C};
    opcodes[0x5A] = {"LD E, D",         &CPU::OP_LD_E_D};
    opcodes[0x5B] = {"LD E, E",         &CPU::OP_LD_E_E};
    opcodes[0x5C] = {"LD E, H",         &CPU::OP_LD_E_H};
    opcodes[0x5D] = {"LD E, L",         &CPU::OP_LD_E_L};
    opcodes[0x5E] = {"LD E, (HL)",      &CPU::OP_LD_E_HL};
    opcodes[0x5F] = {"LD E, A",         &CPU::OP_LD_E_A};
    opcodes[0x60] = {"LD H, B",         &CPU::OP_LD_H_B};
    opcodes[0x61] = {"LD H, C",         &CPU::OP_LD_H_C};
    opcodes[0x62] = {"LD H, D",         &CPU::OP_LD_H_D};
    opcodes[0x63] = {"LD H, E",         &CPU::OP_LD_H_E};
    opcodes[0x64] = {"LD H, H",         &CPU::OP_LD_H_H};
    opcodes[0x65] = {"LD H, L",         &CPU::OP_LD_H_L};
    opcodes[0x66] = {"LD H, (HL)",      &CPU::OP_LD_H_HL};
    opcodes[0x67] = {"LD H, A",         &CPU::OP_LD_H_A};
    opcodes[0x68] = {"LD L, B",         &CPU::OP_LD_L_B};
    opcodes[0x69] = {"LD L, C",         &CPU::OP_LD_L_C};
    opcodes[0x6A] = {"LD L, D",         &CPU::OP_LD_L_D};
    opcodes[0x6B] = {"LD L, E",         &CPU::OP_LD_L_E};
    opcodes[0x6C] = {"LD L, H",         &CPU::OP_LD_L_H};
    opcodes[0x6D] = {"LD L, L",         &CPU::OP_LD_L_L};
    opcodes[0x6E] = {"LD L, (HL)",      &CPU::OP_LD_L_HL};
    opcodes[0x6F] = {"LD L, A",         &CPU::OP_LD_L_A};
    opcodes[0x70] = {"LD (HL), B",      &CPU::OP_LD_HL_B};
    opcodes[0x71] = {"LD (HL), C",      &CPU::OP_LD_HL_C};
    opcodes[0x72] = {"LD (HL), D",      &CPU::OP_LD_HL_D};
    opcodes[0x73] = {"LD (HL), E",      &CPU::OP_LD_HL_E};
    opcodes[0x74] = {"LD (HL), H",      &CPU::OP_LD_HL_H};
    opcodes[0x75] = {"LD (HL), L",      &CPU::OP_LD_HL_L};
    opcodes[0x76] = {"HALT",            &CPU::OP_HALT};
    opcodes[0x77] = {"LD (HL), A",      &CPU::OP_LD_HL_A};
    opcodes[0x78] = {"LD A, B",         &CPU::OP_LD_A_B};
    opcodes[0x79] = {"LD A, C",         &CPU::OP_LD_A_C};
    opcodes[0x7A] = {"LD A, D",         &CPU::OP_LD_A_D};
    opcodes[0x7B] = {"LD A, E",         &CPU::OP_LD_A_E};
    opcodes[0x7C] = {"LD A, H",         &CPU::OP_LD_A_H};
    opcodes[0x7D] = {"LD A, L",         &CPU::OP_LD_A_L};
    opcodes[0x7E] = {"LD A, (HL)",      &CPU::OP_LD_A_HL};
    opcodes[0x7F] = {"LD A, A",         &CPU::OP_LD_A_A};
    opcodes[0x80] = {"ADD A, B",        &CPU::OP_ADD_A_B};
    opcodes[0x81] = {"ADD A, C",        &CPU::OP_ADD_A_C};
    opcodes[0x82] = {"ADD A, D",        &CPU::OP_ADD_A_D};
    opcodes[0x83] = {"ADD A, E",        &CPU::OP_ADD_A_E};
    opcodes[0x84] = {"ADD A, H",        &CPU::OP_ADD_A_H};
    opcodes[0x85] = {"ADD A, L",        &CPU::OP_ADD_A_L};
    opcodes[0x86] = {"ADD A, (HL)",     &CPU::OP_ADD_A_HL};
    opcodes[0x87] = {"ADD A, A",        &CPU::OP_ADD_A_A};
    opcodes[0x88] = {"ADC A, B",        &CPU::OP_ADC_A_B};
    opcodes[0x89] = {"ADC A, C",        &CPU::OP_ADC_A_C};
    opcodes[0x8A] = {"ADC A, D",        &CPU::OP_ADC_A_D};
    opcodes[0x8B] = {"ADC A, E",        &CPU::OP_ADC_A_E};
    opcodes[0x8C] = {"ADC A, H",        &CPU::OP_ADC_A_H};
    opcodes[0x8D] = {"ADC A, L",        &CPU::OP_ADC_A_L};
    opcodes[0x8E] = {"ADC A, (HL)",     &CPU::OP_ADC_A_HL};
    opcodes[0x8F] = {"ADC A, A",        &CPU::OP_ADC_A_A};
    opcodes[0x90] = {"SUB B",           &CPU::OP_SUB_B};
    opcodes[0x91] = {"SUB C",           &CPU::OP_SUB_C};
    opcodes[0x92] = {"SUB D",           &CPU::OP_SUB_D};
    opcodes[0x93] = {"SUB E",           &CPU::OP_SUB_E};
    opcodes[0x94] = {"SUB H",           &CPU::OP_SUB_H};
    opcodes[0x95] = {"SUB L",           &CPU::OP_SUB_L};
    opcodes[0x96] = {"SUB (HL)",        &CPU::OP_SUB_HL};
    opcodes[0x97] = {"SUB A",           &CPU::OP_SUB_A};
    opcodes[0x98] = {"SBC A, B",        &CPU::OP_SBC_A_B};
    opcodes[0x99] = {"SBC A, C",        &CPU::OP_SBC_A_C};
    opcodes[0x9A] = {"SBC A, D",        &CPU::OP_SBC_A_D};
    opcodes[0x9B] = {"SBC A, E",        &CPU::OP_SBC_A_E};
    opcodes[0x9C] = {"SBC A, H",        &CPU::OP_SBC_A_H};
    opcodes[0x9D] = {"SBC A, L",        &CPU::OP_SBC_A_L};
    opcodes[0x9E] = {"SBC A, (HL)",     &CPU::OP_SBC_A_HL};
    opcodes[0x9F] = {"SBC A, A",        &CPU::OP_SBC_A_A};
    opcodes[0xA0] = {"AND B",           &CPU::OP_AND_B};
    opcodes[0xA1] = {"AND C",           &CPU::OP_AND_C};
    opcodes[0xA2] = {"AND D",           &CPU::OP_AND_D};
    opcodes[0xA3] = {"AND E",           &CPU::OP_AND_E};
    opcodes[0xA4] = {"AND H",           &CPU::OP_AND_H};
    opcodes[0xA5] = {"AND L",           &CPU::OP_AND_L};
    opcodes[0xA6] = {"AND (HL)",        &CPU::OP_AND_HL};
    opcodes[0xA7] = {"AND A",           &CPU::OP_AND_A};
    opcodes[0xA8] = {"XOR B",           &CPU::OP_XOR_B};
    opcodes[0xA9] = {"XOR C",           &CPU::OP_XOR_C};
    opcodes[0xAA] = {"XOR D",           &CPU::OP_XOR_D};
    opcodes[0xAB] = {"XOR E",           &CPU::OP_XOR_E};
    opcodes[0xAC] = {"XOR H",           &CPU::OP_XOR_H};
    opcodes[0xAD] = {"XOR L",           &CPU::OP_XOR_L};
    opcodes[0xAE] = {"XOR (HL)",        &CPU::OP_XOR_HL};
    opcodes[0xAF] = {"XOR A",           &CPU::OP_XOR_A};
    opcodes[0xB0] = {"OR B",            &CPU::OP_OR_B};
    opcodes[0xB1] = {"OR C",            &CPU::OP_OR_C};
    opcodes[0xB2] = {"OR D",            &CPU::OP_OR_D};
    opcodes[0xB3] = {"OR E",            &CPU::OP_OR_E};
    opcodes[0xB4] = {"OR H",            &CPU::OP_OR_H};
    opcodes[0xB5] = {"OR L",            &CPU::OP_OR_L};
    opcodes[0xB6] = {"OR (HL)",         &CPU::OP_OR_HL};
    opcodes[0xB7] = {"OR A",            &CPU::OP_OR_A};
    opcodes[0xB8] = {"CP B",            &CPU::OP_CP_B};
    opcodes[0xB9] = {"CP C",            &CPU::OP_CP_C};
    opcodes[0xBA] = {"CP D",            &CPU::OP_CP_D};
    opcodes[0xBB] = {"CP E",            &CPU::OP_CP_E};
    opcodes[0xBC] = {"CP H",            &CPU::OP_CP_H};
    opcodes[0xBD] = {"CP L",            &CPU::OP_CP_L};
    opcodes[0xBE] = {"CP (HL)",         &CPU::OP_CP_HL};
    opcodes[0xBF] = {"CP A",            &CPU::OP_CP_A};
    opcodes[0xC0] = {"RET NZ",          &CPU::OP_RET_NZ};
    opcodes[0xC1] = {"POP BC",          &CPU::OP_POP_BC};
    opcodes[0xC2] = {"JP NZ, a16",      &CPU::OP_JP_NZ_a16};
    opcodes[0xC3] = {"JP a16",          &CPU::OP_JP_a16};
    opcodes[0xC4] = {"CALL NZ, a16",    &CPU::OP_CALL_NZ_a16};
    opcodes[0xC5] = {"PUSH BC",         &CPU::OP_PUSH_BC};
    opcodes[0xC6] = {"ADD A, d8",       &CPU::OP_ADD_A_d8};
    opcodes[0xC7] = {"RST 00H",         &CPU::OP_RST_00H};
    opcodes[0xC8] = {"RET Z",           &CPU::OP_RET_Z};
    opcodes[0xC9] = {"RET",             &CPU::OP_RET};
    opcodes[0xCA] = {"JP Z, a16",       &CPU::OP_JP_Z_a16};
    opcodes[0xCB] = {"PREFIX CB",       &CPU::OP_CB_prefix};
    opcodes[0xCC] = {"CALL Z, a16",     &CPU::OP_CALL_Z_a16};
    opcodes[0xCD] = {"CALL a16",        &CPU::OP_CALL_a16};
    opcodes[0xCE] = {"ADC A, d8",       &CPU::OP_ADC_A_d8};
    opcodes[0xCF] = {"RST 08H",         &CPU::OP_RST_08H};
    opcodes[0xD0] = {"RET NC",          &CPU::OP_RET_NC};
    opcodes[0xD1] = {"POP DE",          &CPU::OP_POP_DE};
    opcodes[0xD2] = {"JP NC, a16",      &CPU::OP_JP_NC_a16};
    opcodes[0xD3] = {"UND D3",          &CPU::OP_UNDEFINED_D3};
    opcodes[0xD4] = {"CALL NC, a16",    &CPU::OP_CALL_NC_a16};
    opcodes[0xD5] = {"PUSH DE",         &CPU::OP_PUSH_DE};
    opcodes[0xD6] = {"SUB d8",          &CPU::OP_SUB_d8};
    opcodes[0xD7] = {"RST 10H",         &CPU::OP_RST_10H};
    opcodes[0xD8] = {"RET C",           &CPU::OP_RET_C};
    opcodes[0xD9] = {"RETI",            &CPU::OP_RETI};
    opcodes[0xDA] = {"JP C, a16",       &CPU::OP_JP_C_a16};
    opcodes[0xDB] = {"UND DB",          &CPU::OP_UNDEFINED_DB};
    opcodes[0xDC] = {"CALL C, a16",     &CPU::OP_CALL_C_a16};
    opcodes[0xDD] = {"UND DD",          &CPU::OP_UNDEFINED_DD};
    opcodes[0xDE] = {"SBC A, d8",       &CPU::OP_SBC_A_d8};
    opcodes[0xDF] = {"RST 18H",         &CPU::OP_RST_18H};
    opcodes[0xE0] = {"LDH (a8), A",     &CPU::OP_LDH_a8_A};
    opcodes[0xE1] = {"POP HL",          &CPU::OP_POP_HL};
    opcodes[0xE2] = {"LD (C), A",       &CPU::OP_LD_aC_A};
    opcodes[0xE3] = {"UND E3",          &CPU::OP_UNDEFINED_E3};
    opcodes[0xE4] = {"UND E4",          &CPU::OP_UNDEFINED_E4};
    opcodes[0xE5] = {"PUSH HL",         &CPU::OP_PUSH_HL};
    opcodes[0xE6] = {"AND d8",          &CPU::OP_AND_d8};
    opcodes[0xE7] = {"RST 20H",         &CPU::OP_RST_20H};
    opcodes[0xE8] = {"ADD SP, r8",      &CPU::OP_ADD_SP_r8};
    opcodes[0xE9] = {"JP (HL)",         &CPU::OP_JP_HL};
    opcodes[0xEA] = {"LD (a16), A",     &CPU::OP_LD_a16_A};
    opcodes[0xEB] = {"UND EB",          &CPU::OP_UNDEFINED_EB};
    opcodes[0xEC] = {"UND EC",          &CPU::OP_UNDEFINED_EC};
    opcodes[0xED] = {"UND ED",          &CPU::OP_UNDEFINED_ED};
    opcodes[0xEE] = {"XOR d8",          &CPU::OP_XOR_d8};
    opcodes[0xEF] = {"RST 28H",         &CPU::OP_RST_28H};
    opcodes[0xF0] = {"LDH A, (a8)",     &CPU::OP_LDH_A_a8};
    opcodes[0xF1] = {"POP AF",          &CPU::OP_POP_AF};
    opcodes[0xF2] = {"LD A, (C)",       &CPU::OP_LD_A_aC};
    opcodes[0xF3] = {"DI",              &CPU::OP_DI};
    opcodes[0xF4] = {"UND F4",          &CPU::OP_UNDEFINED_F4};
    opcodes[0xF5] = {"PUSH AF",         &CPU::OP_PUSH_AF};
    opcodes[0xF6] = {"OR d8",           &CPU::OP_OR_d8};
    opcodes[0xF7] = {"RST 30H",         &CPU::OP_RST_30H};
    opcodes[0xF8] = {"LD HL, SP+r8",    &CPU::OP_LD_HL_SP_r8};
    opcodes[0xF9] = {"LD SP, HL",       &CPU::OP_LD_SP_HL};
    opcodes[0xFA] = {"LD A, (a16)",     &CPU::OP_LD_A_a16};
    opcodes[0xFB] = {"EI",              &CPU::OP_EI};
    opcodes[0xFC] = {"UND FC",          &CPU::OP_UNDEFINED_FC};
    opcodes[0xFD] = {"UND FD",          &CPU::OP_UNDEFINED_FD};
    opcodes[0xFE] = {"CP d8",           &CPU::OP_CP_d8};
    opcodes[0xFF] = {"RST 38H",         &CPU::OP_RST_38H};

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

u32 CPU::OP_NOP() {
    return 4;
}

u32 CPU::OP_LD_BC_d16() {
    regs.bc = fetch16();
    return 12;
}

u32 CPU::OP_LD_BC_A() {
    mmu->write8(regs.bc, regs.a);
    return 8;
}

u32 CPU::OP_INC_BC() {
    regs.bc++;
    return 8;
}

u32 CPU::OP_INC_B() {
    inc8(regs.b);
    return 4;
}

u32 CPU::OP_DEC_B() {
    dec8(regs.b);
    return 4;
}

u32 CPU::OP_LD_B_d8() {
    regs.b = fetch8();
    return 8;
}

u32 CPU::OP_RLCA() {
    u8 leftBit = (regs.a >> 7) & 0x1;
    regs.a = (regs.a << 1) | leftBit;
    setZ(0);
    setN(0);
    setH(0);
    setC(leftBit);
    return 4;
}

u32 CPU::OP_LD_a16_SP() {
    u16 a16 = fetch16();
    mmu->write16(a16, sp);
    return 20;
}

u32 CPU::OP_ADD_HL_BC() {
    add16(regs.hl, regs.bc);
    return 8;
}

u32 CPU::OP_LD_A_BC() {
    regs.a = mmu->read8(regs.bc);
    return 8;
}

u32 CPU::OP_DEC_BC() {
    regs.bc--;
    return 8;
}

u32 CPU::OP_INC_C() {
    inc8(regs.c);
    return 4;
}

u32 CPU::OP_DEC_C() {
    dec8(regs.c);
    return 4;
}

u32 CPU::OP_LD_C_d8() {
    regs.c = fetch8();
    return 8;
}

u32 CPU::OP_RRCA() {
    u8 rightBit = regs.a & 0x1;
    regs.a = (rightBit << 7) | (regs.a >> 1);
    setZ(0);
    setN(0);
    setH(0);
    setC(rightBit);
    return 4;
}

// FIXME
u32 CPU::OP_STOP() {
    fetch8();
    // Push for the streak
    return 4;
}

u32 CPU::OP_LD_DE_d16() {
    regs.de = fetch16();
    return 12;
}

u32 CPU::OP_LD_DE_A() {
    mmu->write8(regs.de, regs.a);
    return 8;
}

u32 CPU::OP_INC_DE() {
    regs.de++;
    return 8;
}

u32 CPU::OP_INC_D() {
    inc8(regs.d);
    return 4;
}

u32 CPU::OP_DEC_D() {
    dec8(regs.d);
    return 4;
}

u32 CPU::OP_LD_D_d8() {
    regs.d = fetch8();
    return 8;
}

u32 CPU::OP_RLA() {
    u8 leftBit = (regs.a >> 7) & 0x1;
    regs.a = (regs.a << 1) | getC();
    setZ(0);
    setN(0);
    setH(0);
    setC(leftBit);
    return 4;
}

u32 CPU::OP_JR_r8() {
    s8 jrAmount = static_cast<s8>(fetch8());
    pc += jrAmount;
    return 12;
}

u32 CPU::OP_ADD_HL_DE() {
    add16(regs.hl, regs.de);
    return 8;
}

u32 CPU::OP_LD_A_DE() {
    regs.a = mmu->read8(regs.de);
    return 8;
}

u32 CPU::OP_DEC_DE() {
    regs.de--;
    return 8;
}

u32 CPU::OP_INC_E() {
    inc8(regs.e);
    return 4;
}

u32 CPU::OP_DEC_E() {
    dec8(regs.e);
    return 4;
}

u32 CPU::OP_LD_E_d8() {
    regs.e = fetch8();
    return 8;
}

u32 CPU::OP_RRA() {
    u8 rightBit = regs.a & 0x1;
    regs.a = (getC() << 7) | (regs.a >> 1);
    setZ(0);
    setN(0);
    setH(0);
    setC(rightBit);
    return 4;
}

u32 CPU::OP_JR_NZ_r8() {
    s8 jrAmount = static_cast<s8>(fetch8());
    if (!getZ()) {
        pc += jrAmount;
        return 12;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_LD_HL_d16() {
    regs.hl = fetch16();
    return 12;
}

u32 CPU::OP_LD_HLp_A() {
    mmu->write8(regs.hl, regs.a);
    regs.hl++;
    return 8;
}

u32 CPU::OP_INC_HL() {
    regs.hl++;
    return 8;
}

u32 CPU::OP_INC_H() {
    inc8(regs.h);
    return 4;
}

u32 CPU::OP_DEC_H() {
    dec8(regs.h);
    return 4;
}

u32 CPU::OP_LD_H_d8() {
    regs.h = fetch8();
    return 8;
}

// FIXME
u32 CPU::OP_DAA() {

    return 4;
}

u32 CPU::OP_JR_Z_r8() {
    s8 jrAmount = static_cast<s8>(fetch8());
    if (getZ()) {
        pc += jrAmount;
        return 12;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_ADD_HL_HL() {
    add16(regs.hl, regs.hl);
    return 8;
}

u32 CPU::OP_LD_A_HLp() {
    regs.a = mmu->read8(regs.hl);
    regs.hl++;
    return 8;
}

u32 CPU::OP_DEC_HL() {
    regs.hl--;
    return 8;
}

u32 CPU::OP_INC_L() {
    inc8(regs.l);
    return 4;
}

u32 CPU::OP_DEC_L() {
    dec8(regs.l);
    return 4;
}

u32 CPU::OP_LD_L_d8() {
    regs.l = fetch8();
    return 8;
}

u32 CPU::OP_CPL() {
    setN(1);
    setH(1);
    regs.a = ~regs.a;
    return 4;
}

u32 CPU::OP_JR_NC_r8() {
    s8 jrAmount = static_cast<s8>(fetch8());
    if (!getC()) {
        pc += jrAmount;
        return 12;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_LD_SP_d16() {
    sp = fetch16();
    return 12;
}

u32 CPU::OP_LD_HLm_A() {
    mmu->write8(regs.hl, regs.a);
    regs.hl--;
    return 8;
}

u32 CPU::OP_INC_SP() {
    sp++;
    return 8;
}

u32 CPU::OP_INC_aHL() {
    u8 r = mmu->read8(regs.hl);
    setH((r & 0x0F) == 0x0F);
    r++;
    mmu->write8(regs.hl, r);
    setZ(r == 0);
    setN(0);
    return 12;
}

u32 CPU::OP_DEC_aHL() {
    u8 r = mmu->read8(regs.hl);
    setH((r & 0x0F) == 0x00);
    r--;
    mmu->write8(regs.hl, r);
    setZ(r == 0);
    setN(1);
    return 12;
}

u32 CPU::OP_LD_HL_d8() {
    mmu->write8(regs.hl, fetch8());
    return 12;
}

u32 CPU::OP_SCF() {
    setN(0);
    setH(0);
    setC(1);
    return 4;
}

u32 CPU::OP_JR_C_r8() {
    s8 jrAmount = static_cast<s8>(fetch8());
    if (getC()) {
        pc += jrAmount;
        return 12;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_ADD_HL_SP() {
    add16(regs.hl, sp);
    return 8;
}

u32 CPU::OP_LD_A_HLm() {
    regs.a = mmu->read8(regs.hl);
    regs.hl--;
    return 8;
}

u32 CPU::OP_DEC_SP() {
    sp--;
    return 8;
}

u32 CPU::OP_INC_A() {
    inc8(regs.a);
    return 4;
}

u32 CPU::OP_DEC_A() {
    dec8(regs.a);
    return 4;
}

u32 CPU::OP_LD_A_d8() {
    regs.a = fetch8();
    return 8;
}

u32 CPU::OP_CCF() {
    setN(0);
    setH(0);
    setC(!getC());
    return 4;
}

// 0x40 - 0x4F
u32 CPU::OP_LD_B_B() { regs.b = regs.b; return 4; }
u32 CPU::OP_LD_B_C() { regs.b = regs.c; return 4; }
u32 CPU::OP_LD_B_D() { regs.b = regs.d; return 4; }
u32 CPU::OP_LD_B_E() { regs.b = regs.e; return 4; }
u32 CPU::OP_LD_B_H() { regs.b = regs.h; return 4; }
u32 CPU::OP_LD_B_L() { regs.b = regs.l; return 4; }
u32 CPU::OP_LD_B_HL() { regs.b = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_B_A() { regs.b = regs.a; return 4; }
u32 CPU::OP_LD_C_B() { regs.c = regs.b; return 4; }
u32 CPU::OP_LD_C_C() { regs.c = regs.c; return 4; }
u32 CPU::OP_LD_C_D() { regs.c = regs.d; return 4; }
u32 CPU::OP_LD_C_E() { regs.c = regs.e; return 4; }
u32 CPU::OP_LD_C_H() { regs.c = regs.h; return 4; }
u32 CPU::OP_LD_C_L() { regs.c = regs.l; return 4; }
u32 CPU::OP_LD_C_HL() { regs.c = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_C_A() { regs.c = regs.a; return 4; }

// 0x50 - 0x5F
u32 CPU::OP_LD_D_B() { regs.d = regs.b; return 4; }
u32 CPU::OP_LD_D_C() { regs.d = regs.c; return 4; }
u32 CPU::OP_LD_D_D() { regs.d = regs.d; return 4; }
u32 CPU::OP_LD_D_E() { regs.d = regs.e; return 4; }
u32 CPU::OP_LD_D_H() { regs.d = regs.h; return 4; }
u32 CPU::OP_LD_D_L() { regs.d = regs.l; return 4; }
u32 CPU::OP_LD_D_HL() { regs.d = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_D_A() { regs.d = regs.a; return 4; }
u32 CPU::OP_LD_E_B() { regs.e = regs.b; return 4; }
u32 CPU::OP_LD_E_C() { regs.e = regs.c; return 4; }
u32 CPU::OP_LD_E_D() { regs.e = regs.d; return 4; }
u32 CPU::OP_LD_E_E() { regs.e = regs.e; return 4; }
u32 CPU::OP_LD_E_H() { regs.e = regs.h; return 4; }
u32 CPU::OP_LD_E_L() { regs.e = regs.l; return 4; }
u32 CPU::OP_LD_E_HL() { regs.e = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_E_A() { regs.e = regs.a; return 4; }

// 0x60 - 0x6F
u32 CPU::OP_LD_H_B() { regs.h = regs.b; return 4; }
u32 CPU::OP_LD_H_C() { regs.h = regs.c; return 4; }
u32 CPU::OP_LD_H_D() { regs.h = regs.d; return 4; }
u32 CPU::OP_LD_H_E() { regs.h = regs.e; return 4; }
u32 CPU::OP_LD_H_H() { regs.h = regs.h; return 4; }
u32 CPU::OP_LD_H_L() { regs.h = regs.l; return 4; }
u32 CPU::OP_LD_H_HL() { regs.h = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_H_A() { regs.h = regs.a; return 4; }
u32 CPU::OP_LD_L_B() { regs.l = regs.b; return 4; }
u32 CPU::OP_LD_L_C() { regs.l = regs.c; return 4; }
u32 CPU::OP_LD_L_D() { regs.l = regs.d; return 4; }
u32 CPU::OP_LD_L_E() { regs.l = regs.e; return 4; }
u32 CPU::OP_LD_L_H() { regs.l = regs.h; return 4; }
u32 CPU::OP_LD_L_L() { regs.l = regs.l; return 4; }
u32 CPU::OP_LD_L_HL() { regs.l = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_L_A() { regs.l = regs.a; return 4; }

// 0x70 - 0x7F
u32 CPU::OP_LD_HL_B() { mmu->write8(regs.hl, regs.b); return 8; }
u32 CPU::OP_LD_HL_C() { mmu->write8(regs.hl, regs.c); return 8; }
u32 CPU::OP_LD_HL_D() { mmu->write8(regs.hl, regs.d); return 8; }
u32 CPU::OP_LD_HL_E() { mmu->write8(regs.hl, regs.e); return 8; }
u32 CPU::OP_LD_HL_H() { mmu->write8(regs.hl, regs.h); return 8; }
u32 CPU::OP_LD_HL_L() { mmu->write8(regs.hl, regs.l); return 8; }
u32 CPU::OP_HALT() { return 4; }; // FIXME
u32 CPU::OP_LD_HL_A() { mmu->write8(regs.hl, regs.a); return 8; }
u32 CPU::OP_LD_A_B() { regs.a = regs.b; return 4; }
u32 CPU::OP_LD_A_C() { regs.a = regs.c; return 4; }
u32 CPU::OP_LD_A_D() { regs.a = regs.d; return 4; }
u32 CPU::OP_LD_A_E() { regs.a = regs.e; return 4; }
u32 CPU::OP_LD_A_H() { regs.a = regs.h; return 4; }
u32 CPU::OP_LD_A_L() { regs.a = regs.l; return 4; }
u32 CPU::OP_LD_A_HL() { regs.a = mmu->read8(regs.hl); return 8; }
u32 CPU::OP_LD_A_A() { regs.a = regs.a; return 4; }

// 0x80-0x8F
u32 CPU::OP_ADD_A_B() { add8(regs.a, regs.b); return 4; }
u32 CPU::OP_ADD_A_C() { add8(regs.a, regs.c); return 4; }
u32 CPU::OP_ADD_A_D() { add8(regs.a, regs.d); return 4; }
u32 CPU::OP_ADD_A_E() { add8(regs.a, regs.e); return 4; }
u32 CPU::OP_ADD_A_H() { add8(regs.a, regs.h); return 4; }
u32 CPU::OP_ADD_A_L() { add8(regs.a, regs.l); return 4; }
u32 CPU::OP_ADD_A_HL() { add8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_ADD_A_A() { add8(regs.a, regs.a); return 4; }
u32 CPU::OP_ADC_A_B() { adc8(regs.a, regs.b); return 4; }
u32 CPU::OP_ADC_A_C() { adc8(regs.a, regs.c); return 4; }
u32 CPU::OP_ADC_A_D() { adc8(regs.a, regs.d); return 4; }
u32 CPU::OP_ADC_A_E() { adc8(regs.a, regs.e); return 4; }
u32 CPU::OP_ADC_A_H() { adc8(regs.a, regs.h); return 4; }
u32 CPU::OP_ADC_A_L() { adc8(regs.a, regs.l); return 4; }
u32 CPU::OP_ADC_A_HL() { adc8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_ADC_A_A() { adc8(regs.a, regs.a); return 4; }

// 0x90-0x9F
u32 CPU::OP_SUB_B() { sub8(regs.a, regs.b); return 4; }
u32 CPU::OP_SUB_C() { sub8(regs.a, regs.c); return 4; }
u32 CPU::OP_SUB_D() { sub8(regs.a, regs.d); return 4; }
u32 CPU::OP_SUB_E() { sub8(regs.a, regs.e); return 4; }
u32 CPU::OP_SUB_H() { sub8(regs.a, regs.h); return 4; }
u32 CPU::OP_SUB_L() { sub8(regs.a, regs.l); return 4; }
u32 CPU::OP_SUB_HL() { sub8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_SUB_A() { sub8(regs.a, regs.a); return 4; }
u32 CPU::OP_SBC_A_B() { sbc8(regs.a, regs.b); return 4; }
u32 CPU::OP_SBC_A_C() { sbc8(regs.a, regs.c); return 4; }
u32 CPU::OP_SBC_A_D() { sbc8(regs.a, regs.d); return 4; }
u32 CPU::OP_SBC_A_E() { sbc8(regs.a, regs.e); return 4; }
u32 CPU::OP_SBC_A_H() { sbc8(regs.a, regs.h); return 4; }
u32 CPU::OP_SBC_A_L() { sbc8(regs.a, regs.l); return 4; }
u32 CPU::OP_SBC_A_HL() { sbc8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_SBC_A_A() { sbc8(regs.a, regs.a); return 4; }

// 0xA0-0xAF
u32 CPU::OP_AND_B() { and8(regs.a, regs.b); return 4; }
u32 CPU::OP_AND_C() { and8(regs.a, regs.c); return 4; }
u32 CPU::OP_AND_D() { and8(regs.a, regs.d); return 4; }
u32 CPU::OP_AND_E() { and8(regs.a, regs.e); return 4; }
u32 CPU::OP_AND_H() { and8(regs.a, regs.h); return 4; }
u32 CPU::OP_AND_L() { and8(regs.a, regs.l); return 4; }
u32 CPU::OP_AND_HL() { and8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_AND_A() { and8(regs.a, regs.a); return 4; }
u32 CPU::OP_XOR_B() { xor8(regs.a, regs.b); return 4; }
u32 CPU::OP_XOR_C() { xor8(regs.a, regs.c); return 4; }
u32 CPU::OP_XOR_D() { xor8(regs.a, regs.d); return 4; }
u32 CPU::OP_XOR_E() { xor8(regs.a, regs.e); return 4; }
u32 CPU::OP_XOR_H() { xor8(regs.a, regs.h); return 4; }
u32 CPU::OP_XOR_L() { xor8(regs.a, regs.l); return 4; }
u32 CPU::OP_XOR_HL() { xor8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_XOR_A() { xor8(regs.a, regs.a); return 4; }

// 0xB0-0xBF
u32 CPU::OP_OR_B() { or8(regs.a, regs.b); return 4; }
u32 CPU::OP_OR_C() { or8(regs.a, regs.c); return 4; }
u32 CPU::OP_OR_D() { or8(regs.a, regs.d); return 4; }
u32 CPU::OP_OR_E() { or8(regs.a, regs.e); return 4; }
u32 CPU::OP_OR_H() { or8(regs.a, regs.h); return 4; }
u32 CPU::OP_OR_L() { or8(regs.a, regs.l); return 4; }
u32 CPU::OP_OR_HL() { or8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_OR_A() { or8(regs.a, regs.a); return 4; }
u32 CPU::OP_CP_B() { cp8(regs.a, regs.b); return 4; }
u32 CPU::OP_CP_C() { cp8(regs.a, regs.c); return 4; }
u32 CPU::OP_CP_D() { cp8(regs.a, regs.d); return 4; }
u32 CPU::OP_CP_E() { cp8(regs.a, regs.e); return 4; }
u32 CPU::OP_CP_H() { cp8(regs.a, regs.h); return 4; }
u32 CPU::OP_CP_L() { cp8(regs.a, regs.l); return 4; }
u32 CPU::OP_CP_HL() { cp8(regs.a, mmu->read8(regs.hl)); return 8; }
u32 CPU::OP_CP_A() { cp8(regs.a, regs.a); return 4; }

u32 CPU::OP_RET_NZ() {
    if (!getZ()) {
        pc = mmu->read16(sp);
        sp += 2;
        return 20;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_POP_BC() {
    regs.bc = mmu->read16(sp);
    sp += 2;
    return 12;
}

u32 CPU::OP_JP_NZ_a16() {
    u16 a16 = fetch16();
    if (!getZ()) {
        pc = a16;
        return 16;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_JP_a16() {
    u16 a16 = fetch16();
    pc = a16;
    return 16;
}

u32 CPU::OP_CALL_NZ_a16() {
    u16 a16 = fetch16();
    if (!getZ()) {
        sp -= 2;
        mmu->write16(sp, pc);
        pc = a16;
        return 24;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_PUSH_BC() {
    sp -= 2;
    mmu->write16(sp, regs.bc);
    return 16;
}

u32 CPU::OP_ADD_A_d8() {
    add8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_00H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0000;
    return 16;
}

u32 CPU::OP_RET_Z() {
    if (getZ()) {
        pc = mmu->read16(sp);
        sp += 2;
        return 20;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_RET() {
    pc = mmu->read16(sp);
    sp += 2;
    return 16;
}

u32 CPU::OP_JP_Z_a16() {
    u16 a16 = fetch16();
    if (getZ()) {
        pc = a16;
        return 16;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_CB_prefix() {
    return 0;
}

u32 CPU::OP_CALL_Z_a16() {
    u16 a16 = fetch16();
    if (getZ()) {
        sp -= 2;
        mmu->write16(sp, pc);
        pc = a16;
        return 24;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_CALL_a16() {
    u16 a16 = fetch16();
    sp -= 2;
    mmu->write16(sp, pc);
    pc = a16;
    return 24;
}

u32 CPU::OP_ADC_A_d8() {
    adc8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_08H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0008;
    return 16;
}

u32 CPU::OP_RET_NC() {
    if (!getC()) {
        pc = mmu->read16(sp);
        sp += 2;
        return 20;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_POP_DE() {
    regs.de = mmu->read16(sp);
    sp += 2;
    return 12;
}

u32 CPU::OP_JP_NC_a16() {
    u16 a16 = fetch16();
    if (!getC()) {
        pc = a16;
        return 16;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_UNDEFINED_D3() {
    return 0;
}

u32 CPU::OP_CALL_NC_a16() {
    u16 a16 = fetch16();
    if (!getC()) {
        sp -= 2;
        mmu->write16(sp, pc);
        pc = a16;
        return 24;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_PUSH_DE() {
    sp -= 2;
    mmu->write16(sp, regs.de);
    return 16;
}

u32 CPU::OP_SUB_d8() {
    sub8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_10H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0010;
    return 16;
}

u32 CPU::OP_RET_C() {
    if (getC()) {
        pc = mmu->read16(sp);
        sp += 2;
        return 20;
    }
    else {
        return 8;
    }
}

u32 CPU::OP_RETI() {
    pc = mmu->read16(sp);
    sp += 2;
    ime_enable_next = 1;
    return 16;
}

u32 CPU::OP_JP_C_a16() {
    u16 a16 = fetch16();
    if (getC()) {
        pc = a16;
        return 16;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_UNDEFINED_DB() {
    return 0;
}

u32 CPU::OP_CALL_C_a16() {
    u16 a16 = fetch16();
    if (getC()) {
        sp -= 2;
        mmu->write16(sp, pc);
        pc = a16;
        return 24;
    }
    else {
        return 12;
    }
}

u32 CPU::OP_UNDEFINED_DD() {
    return 0;
}

u32 CPU::OP_SBC_A_d8() {
    sbc8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_18H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0018;
    return 16;
}

u32 CPU::OP_LDH_a8_A() {
    u8 a8 = fetch8();
    mmu->write8(0xFF00 + a8, regs.a);
    return 12;
}

u32 CPU::OP_POP_HL() {
    regs.hl = mmu->read16(sp);
    sp += 2;
    return 12;
}

u32 CPU::OP_LD_aC_A() {
    mmu->write8(0xFF00 + regs.c, regs.a);
    return 8;
}

u32 CPU::OP_UNDEFINED_E3() {
    return 0;
}

u32 CPU::OP_UNDEFINED_E4() {
    return 0;
}

u32 CPU::OP_PUSH_HL() {
    sp -= 2;
    mmu->write16(sp, regs.hl);
    return 16;
}

u32 CPU::OP_AND_d8() {
    and8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_20H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0020;
    return 16;
}

u32 CPU::OP_ADD_SP_r8() {
    s8 r8 = static_cast<s8>(fetch8());
    u16 spBefore = sp;
    u16 result = spBefore + r8;

    setZ(0);
    setN(0);
    setH(((spBefore & 0x0F) + (r8 & 0x0F)) > 0x0F);
    setC(((spBefore & 0xFF) + (r8 & 0xFF)) > 0xFF);

    sp = result;
    return 16;
}

u32 CPU::OP_JP_HL() {
    pc = regs.hl;
    return 4;
}

u32 CPU::OP_LD_a16_A() {
    mmu->write8(fetch16(), regs.a);
    return 16;
}

u32 CPU::OP_UNDEFINED_EB() {
    return 0;
}

u32 CPU::OP_UNDEFINED_EC() {
    return 0;
}

u32 CPU::OP_UNDEFINED_ED() {
    return 0;
}

u32 CPU::OP_XOR_d8() {
    xor8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_28H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0028;
    return 16;
}

u32 CPU::OP_LDH_A_a8() {
    u8 a8 = fetch8();
    regs.a = mmu->read8(0xFF00 + a8);
    return 12;
}

u32 CPU::OP_POP_AF() {
    regs.af = mmu->read16(sp) & 0xFFF0;
    sp += 2;
    return 12;
}

u32 CPU::OP_LD_A_aC() {
    regs.a = mmu->read8(0xFF00 + regs.c);
    return 8;
}

u32 CPU::OP_DI() {
    ime = 0;
    ime_enable_next = 0;
    return 4;
}

u32 CPU::OP_UNDEFINED_F4() {
    return 0;
}

u32 CPU::OP_PUSH_AF() {
    sp -= 2;
    mmu->write16(sp, regs.af & 0xFFF0);
    return 16;
}

u32 CPU::OP_OR_d8() {
    or8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_30H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0030;
    return 16;
}

u32 CPU::OP_LD_HL_SP_r8() {
    setZ(0);
    setN(0);

    s8 r8 = static_cast<s8>(fetch8());
    u16 res = sp + r8;
    
    setH(((sp & 0xF) + (r8 & 0xF)) > 0xF);
    setC(((sp & 0xFF) + static_cast<u8>(r8)) > 0xFF);

    regs.hl = res;
    return 12;
}

u32 CPU::OP_LD_SP_HL() {
    sp = regs.hl;
    return 8;
}

u32 CPU::OP_LD_A_a16() {
    u16 a16 = fetch16();
    regs.a = mmu->read8(a16);
    return 16;
}

u32 CPU::OP_EI() {
    ime_enable_next = 1;
    return 4;
}

u32 CPU::OP_UNDEFINED_FC() {
    return 0;
}

u32 CPU::OP_UNDEFINED_FD() {
    return 0;
}

u32 CPU::OP_CP_d8() {
    cp8(regs.a, fetch8());
    return 8;
}

u32 CPU::OP_RST_38H() {
    sp -= 2;
    mmu->write16(sp, pc);
    pc = 0x0038;
    return 16;
}

u32 CPU::OP_RLC_B()   { rlc8(regs.b); return 8; }
u32 CPU::OP_RLC_C()   { rlc8(regs.c); return 8; }
u32 CPU::OP_RLC_D()   { rlc8(regs.d); return 8; }
u32 CPU::OP_RLC_E()   { rlc8(regs.e); return 8; }
u32 CPU::OP_RLC_H()   { rlc8(regs.h); return 8; }
u32 CPU::OP_RLC_L()   { rlc8(regs.l); return 8; }
u32 CPU::OP_RLC_HL()  { u8 val = mmu->read8(regs.hl); rlc8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_RLC_A()   { rlc8(regs.a); return 8; }
u32 CPU::OP_RRC_B()   { rrc8(regs.b); return 8; }
u32 CPU::OP_RRC_C()   { rrc8(regs.c); return 8; }
u32 CPU::OP_RRC_D()   { rrc8(regs.d); return 8; }
u32 CPU::OP_RRC_E()   { rrc8(regs.e); return 8; }
u32 CPU::OP_RRC_H()   { rrc8(regs.h); return 8; }
u32 CPU::OP_RRC_L()   { rrc8(regs.l); return 8; }
u32 CPU::OP_RRC_HL()  { u8 val = mmu->read8(regs.hl); rrc8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_RRC_A()   { rrc8(regs.a); return 8; }

u32 CPU::OP_RL_B()    { rl8(regs.b); return 8; }
u32 CPU::OP_RL_C()    { rl8(regs.c); return 8; }
u32 CPU::OP_RL_D()    { rl8(regs.d); return 8; }
u32 CPU::OP_RL_E()    { rl8(regs.e); return 8; }
u32 CPU::OP_RL_H()    { rl8(regs.h); return 8; }
u32 CPU::OP_RL_L()    { rl8(regs.l); return 8; }
u32 CPU::OP_RL_HL()   { u8 val = mmu->read8(regs.hl); rl8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_RL_A()    { rl8(regs.a); return 8; }
u32 CPU::OP_RR_B()    { rr8(regs.b); return 8; }
u32 CPU::OP_RR_C()    { rr8(regs.c); return 8; }
u32 CPU::OP_RR_D()    { rr8(regs.d); return 8; }
u32 CPU::OP_RR_E()    { rr8(regs.e); return 8; }
u32 CPU::OP_RR_H()    { rr8(regs.h); return 8; }
u32 CPU::OP_RR_L()    { rr8(regs.l); return 8; }
u32 CPU::OP_RR_HL()   { u8 val = mmu->read8(regs.hl); rr8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_RR_A()    { rr8(regs.a); return 8; }

u32 CPU::OP_SLA_B()   { sla8(regs.b); return 8; }
u32 CPU::OP_SLA_C()   { sla8(regs.c); return 8; }
u32 CPU::OP_SLA_D()   { sla8(regs.d); return 8; }
u32 CPU::OP_SLA_E()   { sla8(regs.e); return 8; }
u32 CPU::OP_SLA_H()   { sla8(regs.h); return 8; }
u32 CPU::OP_SLA_L()   { sla8(regs.l); return 8; }
u32 CPU::OP_SLA_HL()  { u8 val = mmu->read8(regs.hl); sla8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_SLA_A()   { sla8(regs.a); return 8; }
u32 CPU::OP_SRA_B()   { sra8(regs.b); return 8; }
u32 CPU::OP_SRA_C()   { sra8(regs.c); return 8; }
u32 CPU::OP_SRA_D()   { sra8(regs.d); return 8; }
u32 CPU::OP_SRA_E()   { sra8(regs.e); return 8; }
u32 CPU::OP_SRA_H()   { sra8(regs.h); return 8; }
u32 CPU::OP_SRA_L()   { sra8(regs.l); return 8; }
u32 CPU::OP_SRA_HL()  { u8 val = mmu->read8(regs.hl); sra8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_SRA_A()   { sra8(regs.a); return 8; }

u32 CPU::OP_SWAP_B()  { swap8(regs.b); return 8; }
u32 CPU::OP_SWAP_C()  { swap8(regs.c); return 8; }
u32 CPU::OP_SWAP_D()  { swap8(regs.d); return 8; }
u32 CPU::OP_SWAP_E()  { swap8(regs.e); return 8; }
u32 CPU::OP_SWAP_H()  { swap8(regs.h); return 8; }
u32 CPU::OP_SWAP_L()  { swap8(regs.l); return 8; }
u32 CPU::OP_SWAP_HL() { u8 val = mmu->read8(regs.hl); swap8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_SWAP_A()  { swap8(regs.a); return 8; }
u32 CPU::OP_SRL_B()   { srl8(regs.b); return 8; }
u32 CPU::OP_SRL_C()   { srl8(regs.c); return 8; }
u32 CPU::OP_SRL_D()   { srl8(regs.d); return 8; }
u32 CPU::OP_SRL_E()   { srl8(regs.e); return 8; }
u32 CPU::OP_SRL_H()   { srl8(regs.h); return 8; }
u32 CPU::OP_SRL_L()   { srl8(regs.l); return 8; }
u32 CPU::OP_SRL_HL()  { u8 val = mmu->read8(regs.hl); srl8(val); mmu->write8(regs.hl, val); return 16; }
u32 CPU::OP_SRL_A()   { srl8(regs.a); return 8; }

u32 CPU::OP_BIT_0_B()  { bit8(0, regs.b); return 8; }
u32 CPU::OP_BIT_0_C()  { bit8(0, regs.c); return 8; }
u32 CPU::OP_BIT_0_D()  { bit8(0, regs.d); return 8; }
u32 CPU::OP_BIT_0_E()  { bit8(0, regs.e); return 8; }
u32 CPU::OP_BIT_0_H()  { bit8(0, regs.h); return 8; }
u32 CPU::OP_BIT_0_L()  { bit8(0, regs.l); return 8; }
u32 CPU::OP_BIT_0_HL() { u8 val = mmu->read8(regs.hl); bit8(0, val); return 12; }
u32 CPU::OP_BIT_0_A()  { bit8(0, regs.a); return 8; }
u32 CPU::OP_BIT_1_B()  { bit8(1, regs.b); return 8; }
u32 CPU::OP_BIT_1_C()  { bit8(1, regs.c); return 8; }
u32 CPU::OP_BIT_1_D()  { bit8(1, regs.d); return 8; }
u32 CPU::OP_BIT_1_E()  { bit8(1, regs.e); return 8; }
u32 CPU::OP_BIT_1_H()  { bit8(1, regs.h); return 8; }
u32 CPU::OP_BIT_1_L()  { bit8(1, regs.l); return 8; }
u32 CPU::OP_BIT_1_HL() { u8 val = mmu->read8(regs.hl); bit8(1, val); return 12; }
u32 CPU::OP_BIT_1_A()  { bit8(1, regs.a); return 8; }

u32 CPU::OP_BIT_2_B()  { bit8(2, regs.b); return 8; }
u32 CPU::OP_BIT_2_C()  { bit8(2, regs.c); return 8; }
u32 CPU::OP_BIT_2_D()  { bit8(2, regs.d); return 8; }
u32 CPU::OP_BIT_2_E()  { bit8(2, regs.e); return 8; }
u32 CPU::OP_BIT_2_H()  { bit8(2, regs.h); return 8; }
u32 CPU::OP_BIT_2_L()  { bit8(2, regs.l); return 8; }
u32 CPU::OP_BIT_2_HL() { u8 val = mmu->read8(regs.hl); bit8(2, val); return 12; }
u32 CPU::OP_BIT_2_A()  { bit8(2, regs.a); return 8; }
u32 CPU::OP_BIT_3_B()  { bit8(3, regs.b); return 8; }
u32 CPU::OP_BIT_3_C()  { bit8(3, regs.c); return 8; }
u32 CPU::OP_BIT_3_D()  { bit8(3, regs.d); return 8; }
u32 CPU::OP_BIT_3_E()  { bit8(3, regs.e); return 8; }
u32 CPU::OP_BIT_3_H()  { bit8(3, regs.h); return 8; }
u32 CPU::OP_BIT_3_L()  { bit8(3, regs.l); return 8; }
u32 CPU::OP_BIT_3_HL() { u8 val = mmu->read8(regs.hl); bit8(3, val); return 12; }
u32 CPU::OP_BIT_3_A()  { bit8(3, regs.a); return 8; }

u32 CPU::OP_BIT_4_B()  { bit8(4, regs.b); return 8; }
u32 CPU::OP_BIT_4_C()  { bit8(4, regs.c); return 8; }
u32 CPU::OP_BIT_4_D()  { bit8(4, regs.d); return 8; }
u32 CPU::OP_BIT_4_E()  { bit8(4, regs.e); return 8; }
u32 CPU::OP_BIT_4_H()  { bit8(4, regs.h); return 8; }
u32 CPU::OP_BIT_4_L()  { bit8(4, regs.l); return 8; }
u32 CPU::OP_BIT_4_HL() { u8 val = mmu->read8(regs.hl); bit8(4, val); return 12; }
u32 CPU::OP_BIT_4_A()  { bit8(4, regs.a); return 8; }
u32 CPU::OP_BIT_5_B()  { bit8(5, regs.b); return 8; }
u32 CPU::OP_BIT_5_C()  { bit8(5, regs.c); return 8; }
u32 CPU::OP_BIT_5_D()  { bit8(5, regs.d); return 8; }
u32 CPU::OP_BIT_5_E()  { bit8(5, regs.e); return 8; }
u32 CPU::OP_BIT_5_H()  { bit8(5, regs.h); return 8; }
u32 CPU::OP_BIT_5_L()  { bit8(5, regs.l); return 8; }
u32 CPU::OP_BIT_5_HL() { u8 val = mmu->read8(regs.hl); bit8(5, val); return 12; }
u32 CPU::OP_BIT_5_A()  { bit8(5, regs.a); return 8; }

u32 CPU::OP_BIT_6_B()  { bit8(6, regs.b); return 8; }
u32 CPU::OP_BIT_6_C()  { bit8(6, regs.c); return 8; }
u32 CPU::OP_BIT_6_D()  { bit8(6, regs.d); return 8; }
u32 CPU::OP_BIT_6_E()  { bit8(6, regs.e); return 8; }
u32 CPU::OP_BIT_6_H()  { bit8(6, regs.h); return 8; }
u32 CPU::OP_BIT_6_L()  { bit8(6, regs.l); return 8; }
u32 CPU::OP_BIT_6_HL() { u8 val = mmu->read8(regs.hl); bit8(6, val); return 12; }
u32 CPU::OP_BIT_6_A()  { bit8(6, regs.a); return 8; }
u32 CPU::OP_BIT_7_B()  { bit8(7, regs.b); return 8; }
u32 CPU::OP_BIT_7_C()  { bit8(7, regs.c); return 8; }
u32 CPU::OP_BIT_7_D()  { bit8(7, regs.d); return 8; }
u32 CPU::OP_BIT_7_E()  { bit8(7, regs.e); return 8; }
u32 CPU::OP_BIT_7_H()  { bit8(7, regs.h); return 8; }
u32 CPU::OP_BIT_7_L()  { bit8(7, regs.l); return 8; }
u32 CPU::OP_BIT_7_HL() { u8 val = mmu->read8(regs.hl); bit8(7, val); return 12; }
u32 CPU::OP_BIT_7_A()  { bit8(7, regs.a); return 8; }

u32 CPU::OP_RES_0_B()  { res8(0, regs.b); return 8; }
u32 CPU::OP_RES_0_C()  { res8(0, regs.c); return 8; }
u32 CPU::OP_RES_0_D()  { res8(0, regs.d); return 8; }
u32 CPU::OP_RES_0_E()  { res8(0, regs.e); return 8; }
u32 CPU::OP_RES_0_H()  { res8(0, regs.h); return 8; }
u32 CPU::OP_RES_0_L()  { res8(0, regs.l); return 8; }
u32 CPU::OP_RES_0_HL() { u8 v = mmu->read8(regs.hl); res8(0, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_0_A()  { res8(0, regs.a); return 8; }
u32 CPU::OP_RES_1_B()  { res8(1, regs.b); return 8; }
u32 CPU::OP_RES_1_C()  { res8(1, regs.c); return 8; }
u32 CPU::OP_RES_1_D()  { res8(1, regs.d); return 8; }
u32 CPU::OP_RES_1_E()  { res8(1, regs.e); return 8; }
u32 CPU::OP_RES_1_H()  { res8(1, regs.h); return 8; }
u32 CPU::OP_RES_1_L()  { res8(1, regs.l); return 8; }
u32 CPU::OP_RES_1_HL() { u8 v = mmu->read8(regs.hl); res8(1, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_1_A()  { res8(1, regs.a); return 8; }

u32 CPU::OP_RES_2_B()  { res8(2, regs.b); return 8; }
u32 CPU::OP_RES_2_C()  { res8(2, regs.c); return 8; }
u32 CPU::OP_RES_2_D()  { res8(2, regs.d); return 8; }
u32 CPU::OP_RES_2_E()  { res8(2, regs.e); return 8; }
u32 CPU::OP_RES_2_H()  { res8(2, regs.h); return 8; }
u32 CPU::OP_RES_2_L()  { res8(2, regs.l); return 8; }
u32 CPU::OP_RES_2_HL() { u8 v = mmu->read8(regs.hl); res8(2, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_2_A()  { res8(2, regs.a); return 8; }
u32 CPU::OP_RES_3_B()  { res8(3, regs.b); return 8; }
u32 CPU::OP_RES_3_C()  { res8(3, regs.c); return 8; }
u32 CPU::OP_RES_3_D()  { res8(3, regs.d); return 8; }
u32 CPU::OP_RES_3_E()  { res8(3, regs.e); return 8; }
u32 CPU::OP_RES_3_H()  { res8(3, regs.h); return 8; }
u32 CPU::OP_RES_3_L()  { res8(3, regs.l); return 8; }
u32 CPU::OP_RES_3_HL() { u8 v = mmu->read8(regs.hl); res8(3, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_3_A()  { res8(3, regs.a); return 8; }

u32 CPU::OP_RES_4_B()  { res8(4, regs.b); return 8; }
u32 CPU::OP_RES_4_C()  { res8(4, regs.c); return 8; }
u32 CPU::OP_RES_4_D()  { res8(4, regs.d); return 8; }
u32 CPU::OP_RES_4_E()  { res8(4, regs.e); return 8; }
u32 CPU::OP_RES_4_H()  { res8(4, regs.h); return 8; }
u32 CPU::OP_RES_4_L()  { res8(4, regs.l); return 8; }
u32 CPU::OP_RES_4_HL() { u8 v = mmu->read8(regs.hl); res8(4, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_4_A()  { res8(4, regs.a); return 8; }
u32 CPU::OP_RES_5_B()  { res8(5, regs.b); return 8; }
u32 CPU::OP_RES_5_C()  { res8(5, regs.c); return 8; }
u32 CPU::OP_RES_5_D()  { res8(5, regs.d); return 8; }
u32 CPU::OP_RES_5_E()  { res8(5, regs.e); return 8; }
u32 CPU::OP_RES_5_H()  { res8(5, regs.h); return 8; }
u32 CPU::OP_RES_5_L()  { res8(5, regs.l); return 8; }
u32 CPU::OP_RES_5_HL() { u8 v = mmu->read8(regs.hl); res8(5, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_5_A()  { res8(5, regs.a); return 8; }

u32 CPU::OP_RES_6_B()  { res8(6, regs.b); return 8; }
u32 CPU::OP_RES_6_C()  { res8(6, regs.c); return 8; }
u32 CPU::OP_RES_6_D()  { res8(6, regs.d); return 8; }
u32 CPU::OP_RES_6_E()  { res8(6, regs.e); return 8; }
u32 CPU::OP_RES_6_H()  { res8(6, regs.h); return 8; }
u32 CPU::OP_RES_6_L()  { res8(6, regs.l); return 8; }
u32 CPU::OP_RES_6_HL() { u8 v = mmu->read8(regs.hl); res8(6, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_6_A()  { res8(6, regs.a); return 8; }
u32 CPU::OP_RES_7_B()  { res8(7, regs.b); return 8; }
u32 CPU::OP_RES_7_C()  { res8(7, regs.c); return 8; }
u32 CPU::OP_RES_7_D()  { res8(7, regs.d); return 8; }
u32 CPU::OP_RES_7_E()  { res8(7, regs.e); return 8; }
u32 CPU::OP_RES_7_H()  { res8(7, regs.h); return 8; }
u32 CPU::OP_RES_7_L()  { res8(7, regs.l); return 8; }
u32 CPU::OP_RES_7_HL() { u8 v = mmu->read8(regs.hl); res8(7, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_RES_7_A()  { res8(7, regs.a); return 8; }

u32 CPU::OP_SET_0_B()  { set8(0, regs.b); return 8; }
u32 CPU::OP_SET_0_C()  { set8(0, regs.c); return 8; }
u32 CPU::OP_SET_0_D()  { set8(0, regs.d); return 8; }
u32 CPU::OP_SET_0_E()  { set8(0, regs.e); return 8; }
u32 CPU::OP_SET_0_H()  { set8(0, regs.h); return 8; }
u32 CPU::OP_SET_0_L()  { set8(0, regs.l); return 8; }
u32 CPU::OP_SET_0_HL() { u8 v = mmu->read8(regs.hl); set8(0, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_0_A()  { set8(0, regs.a); return 8; }
u32 CPU::OP_SET_1_B()  { set8(1, regs.b); return 8; }
u32 CPU::OP_SET_1_C()  { set8(1, regs.c); return 8; }
u32 CPU::OP_SET_1_D()  { set8(1, regs.d); return 8; }
u32 CPU::OP_SET_1_E()  { set8(1, regs.e); return 8; }
u32 CPU::OP_SET_1_H()  { set8(1, regs.h); return 8; }
u32 CPU::OP_SET_1_L()  { set8(1, regs.l); return 8; }
u32 CPU::OP_SET_1_HL() { u8 v = mmu->read8(regs.hl); set8(1, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_1_A()  { set8(1, regs.a); return 8; }

u32 CPU::OP_SET_2_B()  { set8(2, regs.b); return 8; }
u32 CPU::OP_SET_2_C()  { set8(2, regs.c); return 8; }
u32 CPU::OP_SET_2_D()  { set8(2, regs.d); return 8; }
u32 CPU::OP_SET_2_E()  { set8(2, regs.e); return 8; }
u32 CPU::OP_SET_2_H()  { set8(2, regs.h); return 8; }
u32 CPU::OP_SET_2_L()  { set8(2, regs.l); return 8; }
u32 CPU::OP_SET_2_HL() { u8 v = mmu->read8(regs.hl); set8(2, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_2_A()  { set8(2, regs.a); return 8; }
u32 CPU::OP_SET_3_B()  { set8(3, regs.b); return 8; }
u32 CPU::OP_SET_3_C()  { set8(3, regs.c); return 8; }
u32 CPU::OP_SET_3_D()  { set8(3, regs.d); return 8; }
u32 CPU::OP_SET_3_E()  { set8(3, regs.e); return 8; }
u32 CPU::OP_SET_3_H()  { set8(3, regs.h); return 8; }
u32 CPU::OP_SET_3_L()  { set8(3, regs.l); return 8; }
u32 CPU::OP_SET_3_HL() { u8 v = mmu->read8(regs.hl); set8(3, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_3_A()  { set8(3, regs.a); return 8; }

u32 CPU::OP_SET_4_B()  { set8(4, regs.b); return 8; }
u32 CPU::OP_SET_4_C()  { set8(4, regs.c); return 8; }
u32 CPU::OP_SET_4_D()  { set8(4, regs.d); return 8; }
u32 CPU::OP_SET_4_E()  { set8(4, regs.e); return 8; }
u32 CPU::OP_SET_4_H()  { set8(4, regs.h); return 8; }
u32 CPU::OP_SET_4_L()  { set8(4, regs.l); return 8; }
u32 CPU::OP_SET_4_HL() { u8 v = mmu->read8(regs.hl); set8(4, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_4_A()  { set8(4, regs.a); return 8; }
u32 CPU::OP_SET_5_B()  { set8(5, regs.b); return 8; }
u32 CPU::OP_SET_5_C()  { set8(5, regs.c); return 8; }
u32 CPU::OP_SET_5_D()  { set8(5, regs.d); return 8; }
u32 CPU::OP_SET_5_E()  { set8(5, regs.e); return 8; }
u32 CPU::OP_SET_5_H()  { set8(5, regs.h); return 8; }
u32 CPU::OP_SET_5_L()  { set8(5, regs.l); return 8; }
u32 CPU::OP_SET_5_HL() { u8 v = mmu->read8(regs.hl); set8(5, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_5_A()  { set8(5, regs.a); return 8; }

u32 CPU::OP_SET_6_B()  { set8(6, regs.b); return 8; }
u32 CPU::OP_SET_6_C()  { set8(6, regs.c); return 8; }
u32 CPU::OP_SET_6_D()  { set8(6, regs.d); return 8; }
u32 CPU::OP_SET_6_E()  { set8(6, regs.e); return 8; }
u32 CPU::OP_SET_6_H()  { set8(6, regs.h); return 8; }
u32 CPU::OP_SET_6_L()  { set8(6, regs.l); return 8; }
u32 CPU::OP_SET_6_HL() { u8 v = mmu->read8(regs.hl); set8(6, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_6_A()  { set8(6, regs.a); return 8; }
u32 CPU::OP_SET_7_B()  { set8(7, regs.b); return 8; }
u32 CPU::OP_SET_7_C()  { set8(7, regs.c); return 8; }
u32 CPU::OP_SET_7_D()  { set8(7, regs.d); return 8; }
u32 CPU::OP_SET_7_E()  { set8(7, regs.e); return 8; }
u32 CPU::OP_SET_7_H()  { set8(7, regs.h); return 8; }
u32 CPU::OP_SET_7_L()  { set8(7, regs.l); return 8; }
u32 CPU::OP_SET_7_HL() { u8 v = mmu->read8(regs.hl); set8(7, v); mmu->write8(regs.hl, v); return 16; }
u32 CPU::OP_SET_7_A()  { set8(7, regs.a); return 8; }