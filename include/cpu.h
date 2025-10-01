#pragma once
#include <array>
#include "mmu.h"

class CPU {
public:
    CPU(MMU* mmu);
    
    struct {
        union { struct { u8 f, a; }; u16 af; };
        union { struct { u8 c, b; }; u16 bc; };
        union { struct { u8 e, d; }; u16 de; };
        union { struct { u8 l, h; }; u16 hl; };
    } regs;
    
    u16 sp;
    u16 pc;

    u8 fetch8();
    u16 fetch16();
    u8 peek8();
    u16 peek16();

    static constexpr u8 FLAG_Z = 1 << 7;
    static constexpr u8 FLAG_N = 1 << 6;
    static constexpr u8 FLAG_H = 1 << 5;
    static constexpr u8 FLAG_C = 1 << 4;

    inline void setZ(bool v) { regs.f = (regs.f & ~FLAG_Z) | (v * FLAG_Z); }
    inline void setN(bool v) { regs.f = (regs.f & ~FLAG_N) | (v * FLAG_N); }
    inline void setH(bool v) { regs.f = (regs.f & ~FLAG_H) | (v * FLAG_H); }
    inline void setC(bool v) { regs.f = (regs.f & ~FLAG_C) | (v * FLAG_C); }

    inline bool getZ() const { return regs.f & FLAG_Z; }
    inline bool getN() const { return regs.f & FLAG_N; }
    inline bool getH() const { return regs.f & FLAG_H; }
    inline bool getC() const { return regs.f & FLAG_C; }

    void inc8(u8& r);
    void dec8(u8& r);
    void add16(u16& r1, u16 r2);
    void add8(u8& r1, u8 r2);
    void adc8(u8& r1, u8 r2);
    void sub8(u8& r1, u8 r2);
    void sbc8(u8& r1, u8 r2);
    void and8(u8& r1, u8 r2);
    void xor8(u8& r1, u8 r2);
    void or8(u8& r1, u8 r2);
    void cp8(u8 r1, u8 r2);

    struct Instruction {
        string name = "UND";
        u32 (CPU::*op)() = nullptr;
        u32 execute(CPU* cpu) const;
    };
    
    void step();
    
    // 0x00-0x0F
    u32 OP_NOP();
    u32 OP_LD_BC_d16();
    u32 OP_LD_BC_A();
    u32 OP_INC_BC();
    u32 OP_INC_B();
    u32 OP_DEC_B();
    u32 OP_LD_B_d8();
    u32 OP_RLCA();
    u32 OP_LD_a16_SP();
    u32 OP_ADD_HL_BC();
    u32 OP_LD_A_BC();
    u32 OP_DEC_BC();
    u32 OP_INC_C();
    u32 OP_DEC_C();
    u32 OP_LD_C_d8();
    u32 OP_RRCA();

    // 0x10-0x1F
    u32 OP_STOP(); // 0x1000
    u32 OP_LD_DE_d16();
    u32 OP_LD_DE_A();
    u32 OP_INC_DE();
    u32 OP_INC_D();
    u32 OP_DEC_D();
    u32 OP_LD_D_d8();
    u32 OP_RLA();
    u32 OP_JR_r8();
    u32 OP_ADD_HL_DE();
    u32 OP_LD_A_DE();
    u32 OP_DEC_DE();
    u32 OP_INC_E();
    u32 OP_DEC_E();
    u32 OP_LD_E_d8();
    u32 OP_RRA();

    // 0x20-0x2F
    u32 OP_JR_NZ_r8();
    u32 OP_LD_HL_d16();
    u32 OP_LD_HLp_A();
    u32 OP_INC_HL();
    u32 OP_INC_H();
    u32 OP_DEC_H();
    u32 OP_LD_H_d8();
    u32 OP_DAA();
    u32 OP_JR_Z_r8();
    u32 OP_ADD_HL_HL();
    u32 OP_LD_A_HLp();
    u32 OP_DEC_HL();
    u32 OP_INC_L();
    u32 OP_DEC_L();
    u32 OP_LD_L_d8();
    u32 OP_CPL();

    // 0x30-0x3F
    u32 OP_JR_NC_r8();
    u32 OP_LD_SP_d16();
    u32 OP_LD_HLm_A();
    u32 OP_INC_SP();
    u32 OP_INC_aHL();
    u32 OP_DEC_aHL();
    u32 OP_LD_HL_d8();
    u32 OP_SCF();
    u32 OP_JR_C_r8();
    u32 OP_ADD_HL_SP();
    u32 OP_LD_A_HLm();
    u32 OP_DEC_SP();
    u32 OP_INC_A();
    u32 OP_DEC_A();
    u32 OP_LD_A_d8();
    u32 OP_CCF();

    // 0x40 - 0x4F
    u32 OP_LD_B_B();
    u32 OP_LD_B_C();
    u32 OP_LD_B_D();
    u32 OP_LD_B_E();
    u32 OP_LD_B_H();
    u32 OP_LD_B_L();
    u32 OP_LD_B_HL();
    u32 OP_LD_B_A();
    u32 OP_LD_C_B();
    u32 OP_LD_C_C();
    u32 OP_LD_C_D();
    u32 OP_LD_C_E();
    u32 OP_LD_C_H();
    u32 OP_LD_C_L();
    u32 OP_LD_C_HL();
    u32 OP_LD_C_A();

    // 0x50 - 0x5F
    u32 OP_LD_D_B();
    u32 OP_LD_D_C();
    u32 OP_LD_D_D();
    u32 OP_LD_D_E();
    u32 OP_LD_D_H();
    u32 OP_LD_D_L();
    u32 OP_LD_D_HL();
    u32 OP_LD_D_A();
    u32 OP_LD_E_B();
    u32 OP_LD_E_C();
    u32 OP_LD_E_D();
    u32 OP_LD_E_E();
    u32 OP_LD_E_H();
    u32 OP_LD_E_L();
    u32 OP_LD_E_HL();
    u32 OP_LD_E_A();

    // 0x60 - 0x6F
    u32 OP_LD_H_B();
    u32 OP_LD_H_C();
    u32 OP_LD_H_D();
    u32 OP_LD_H_E();
    u32 OP_LD_H_H();
    u32 OP_LD_H_L();
    u32 OP_LD_H_HL();
    u32 OP_LD_H_A();
    u32 OP_LD_L_B();
    u32 OP_LD_L_C();
    u32 OP_LD_L_D();
    u32 OP_LD_L_E();
    u32 OP_LD_L_H();
    u32 OP_LD_L_L();
    u32 OP_LD_L_HL();
    u32 OP_LD_L_A();

    // 0x70 - 0x7F
    u32 OP_LD_HL_B();
    u32 OP_LD_HL_C();
    u32 OP_LD_HL_D();
    u32 OP_LD_HL_E();
    u32 OP_LD_HL_H();
    u32 OP_LD_HL_L();
    u32 OP_HALT();
    u32 OP_LD_HL_A();
    u32 OP_LD_A_B();
    u32 OP_LD_A_C();
    u32 OP_LD_A_D();
    u32 OP_LD_A_E();
    u32 OP_LD_A_H();
    u32 OP_LD_A_L();
    u32 OP_LD_A_HL();
    u32 OP_LD_A_A();

    // 0x80-0x8F
    u32 OP_ADD_A_B();
    u32 OP_ADD_A_C();
    u32 OP_ADD_A_D();
    u32 OP_ADD_A_E();
    u32 OP_ADD_A_H();
    u32 OP_ADD_A_L();
    u32 OP_ADD_A_HL();
    u32 OP_ADD_A_A();
    u32 OP_ADC_A_B();
    u32 OP_ADC_A_C();
    u32 OP_ADC_A_D();
    u32 OP_ADC_A_E();
    u32 OP_ADC_A_H();
    u32 OP_ADC_A_L();
    u32 OP_ADC_A_HL();
    u32 OP_ADC_A_A();

    // 0x90-0x9F
    u32 OP_SUB_B();
    u32 OP_SUB_C();
    u32 OP_SUB_D();
    u32 OP_SUB_E();
    u32 OP_SUB_H();
    u32 OP_SUB_L();
    u32 OP_SUB_HL();
    u32 OP_SUB_A();
    u32 OP_SBC_A_B();
    u32 OP_SBC_A_C();
    u32 OP_SBC_A_D();
    u32 OP_SBC_A_E();
    u32 OP_SBC_A_H();
    u32 OP_SBC_A_L();
    u32 OP_SBC_A_HL();
    u32 OP_SBC_A_A();

    // 0xA0-0xAF
    u32 OP_AND_B();
    u32 OP_AND_C();
    u32 OP_AND_D();
    u32 OP_AND_E();
    u32 OP_AND_H();
    u32 OP_AND_L();
    u32 OP_AND_HL();
    u32 OP_AND_A();
    u32 OP_XOR_B();
    u32 OP_XOR_C();
    u32 OP_XOR_D();
    u32 OP_XOR_E();
    u32 OP_XOR_H();
    u32 OP_XOR_L();
    u32 OP_XOR_HL();
    u32 OP_XOR_A();

    // 0xB0-0xBF
    u32 OP_OR_B();
    u32 OP_OR_C();
    u32 OP_OR_D();
    u32 OP_OR_E();
    u32 OP_OR_H();
    u32 OP_OR_L();
    u32 OP_OR_HL();
    u32 OP_OR_A();
    u32 OP_CP_B();
    u32 OP_CP_C();
    u32 OP_CP_D();
    u32 OP_CP_E();
    u32 OP_CP_H();
    u32 OP_CP_L();
    u32 OP_CP_HL();
    u32 OP_CP_A();

    // 0xC0-0xCF
    u32 OP_RET_NZ();
    u32 OP_POP_BC();
    u32 OP_JP_NZ_a16();
    u32 OP_JP_a16();
    u32 OP_CALL_NZ_a16();
    u32 OP_PUSH_BC();
    u32 OP_ADD_A_d8();
    u32 OP_RST_00H();
    u32 OP_RET_Z();
    u32 OP_RET();
    u32 OP_JP_Z_a16();
    u32 OP_CB_prefix();
    u32 OP_CALL_Z_a16();
    u32 OP_CALL_a16();
    u32 OP_ADC_A_d8();
    u32 OP_RST_08H();

    // 0xD0-0xDF
    u32 OP_RET_NC();
    u32 OP_POP_DE();
    u32 OP_JP_NC_a16();
    u32 OP_UNDEFINED_D3();
    u32 OP_CALL_NC_a16();
    u32 OP_PUSH_DE();
    u32 OP_SUB_d8();
    u32 OP_RST_10H();
    u32 OP_RET_C();
    u32 OP_RETI();
    u32 OP_JP_C_a16();
    u32 OP_UNDEFINED_DB();
    u32 OP_CALL_C_a16();
    u32 OP_UNDEFINED_DD();
    u32 OP_SBC_A_d8();
    u32 OP_RST_18H();

    // 0xE0-0xEF
    u32 OP_LDH_a8_A();
    u32 OP_POP_HL();
    u32 OP_LD_aC_A();
    u32 OP_UNDEFINED_E3();
    u32 OP_UNDEFINED_E4();
    u32 OP_PUSH_HL();
    u32 OP_AND_d8();
    u32 OP_RST_20H();
    u32 OP_ADD_SP_r8();
    u32 OP_JP_HL();
    u32 OP_LD_a16_A();
    u32 OP_UNDEFINED_EB();
    u32 OP_UNDEFINED_EC();
    u32 OP_UNDEFINED_ED();
    u32 OP_XOR_d8();
    u32 OP_RST_28H();

    // 0xF0-0xFF
    u32 OP_LDH_A_a8();
    u32 OP_POP_AF();
    u32 OP_LD_A_aC();
    u32 OP_DI();
    u32 OP_UNDEFINED_F4();
    u32 OP_PUSH_AF();
    u32 OP_OR_d8();
    u32 OP_RST_30H();
    u32 OP_LD_HL_SP_r8();
    u32 OP_LD_SP_HL();
    u32 OP_LD_A_a16();
    u32 OP_EI();
    u32 OP_UNDEFINED_FC();
    u32 OP_UNDEFINED_FD();
    u32 OP_CP_d8();
    u32 OP_RST_38H();

    // CB-prefix opcodes
    // CB 0x00-0x0F
    u32 OP_RLC_B();
    u32 OP_RLC_C();
    u32 OP_RLC_D();
    u32 OP_RLC_E();
    u32 OP_RLC_H();
    u32 OP_RLC_L();
    u32 OP_RLC_HL();
    u32 OP_RLC_A();
    u32 OP_RRC_B();
    u32 OP_RRC_C();
    u32 OP_RRC_D();
    u32 OP_RRC_E();
    u32 OP_RRC_H();
    u32 OP_RRC_L();
    u32 OP_RRC_HL();
    u32 OP_RRC_A();

    // CB 0x10-0x1F
    u32 OP_RL_B();
    u32 OP_RL_C();
    u32 OP_RL_D();
    u32 OP_RL_E();
    u32 OP_RL_H();
    u32 OP_RL_L();
    u32 OP_RL_HL();
    u32 OP_RL_A();
    u32 OP_RR_B();
    u32 OP_RR_C();
    u32 OP_RR_D();
    u32 OP_RR_E();
    u32 OP_RR_H();
    u32 OP_RR_L();
    u32 OP_RR_HL();
    u32 OP_RR_A();

    // CB 0x20-0x2F
    u32 OP_SLA_B();
    u32 OP_SLA_C();
    u32 OP_SLA_D();
    u32 OP_SLA_E();
    u32 OP_SLA_H();
    u32 OP_SLA_L();
    u32 OP_SLA_HL();
    u32 OP_SLA_A();
    u32 OP_SRA_B();
    u32 OP_SRA_C();
    u32 OP_SRA_D();
    u32 OP_SRA_E();
    u32 OP_SRA_H();
    u32 OP_SRA_L();
    u32 OP_SRA_HL();
    u32 OP_SRA_A();

    // CB 0x30-0x3F
    u32 OP_SWAP_B();
    u32 OP_SWAP_C();
    u32 OP_SWAP_D();
    u32 OP_SWAP_E();
    u32 OP_SWAP_H();
    u32 OP_SWAP_L();
    u32 OP_SWAP_HL();
    u32 OP_SWAP_A();
    u32 OP_SRL_B();
    u32 OP_SRL_C();
    u32 OP_SRL_D();
    u32 OP_SRL_E();
    u32 OP_SRL_H();
    u32 OP_SRL_L();
    u32 OP_SRL_HL();
    u32 OP_SRL_A();

    // CB 0x40–0x4F
    u32 OP_BIT_0_B();
    u32 OP_BIT_0_C();
    u32 OP_BIT_0_D();
    u32 OP_BIT_0_E();
    u32 OP_BIT_0_H();
    u32 OP_BIT_0_L();
    u32 OP_BIT_0_HL();
    u32 OP_BIT_0_A();
    u32 OP_BIT_1_B();
    u32 OP_BIT_1_C();
    u32 OP_BIT_1_D();
    u32 OP_BIT_1_E();
    u32 OP_BIT_1_H();
    u32 OP_BIT_1_L();
    u32 OP_BIT_1_HL();
    u32 OP_BIT_1_A();

    // CB 0x50–0x5F
    u32 OP_BIT_2_B();
    u32 OP_BIT_2_C();
    u32 OP_BIT_2_D();
    u32 OP_BIT_2_E();
    u32 OP_BIT_2_H();
    u32 OP_BIT_2_L();
    u32 OP_BIT_2_HL();
    u32 OP_BIT_2_A();
    u32 OP_BIT_3_B();
    u32 OP_BIT_3_C();
    u32 OP_BIT_3_D();
    u32 OP_BIT_3_E();
    u32 OP_BIT_3_H();
    u32 OP_BIT_3_L();
    u32 OP_BIT_3_HL();
    u32 BIT_3_A();

    // CB 0x60–0x6F
    u32 OP_BIT_4_B();
    u32 OP_BIT_4_C();
    u32 OP_BIT_4_D();
    u32 OP_BIT_4_E();
    u32 OP_BIT_4_H();
    u32 OP_BIT_4_L();
    u32 OP_BIT_4_HL();
    u32 OP_BIT_4_A();
    u32 OP_BIT_5_B();
    u32 OP_BIT_5_C();
    u32 OP_BIT_5_D();
    u32 OP_BIT_5_E();
    u32 OP_BIT_5_H();
    u32 OP_BIT_5_L();
    u32 OP_BIT_5_HL();
    u32 OP_BIT_5_A();

    // CB 0x70–0x7F
    u32 OP_BIT_6_B();
    u32 OP_BIT_6_C();
    u32 OP_BIT_6_D();
    u32 OP_BIT_6_E();
    u32 OP_BIT_6_H();
    u32 OP_BIT_6_L();
    u32 OP_BIT_6_HL();
    u32 OP_BIT_6_A();
    u32 OP_BIT_7_B();
    u32 OP_BIT_7_C();
    u32 OP_BIT_7_D();
    u32 OP_BIT_7_E();
    u32 OP_BIT_7_H();
    u32 OP_BIT_7_L();
    u32 OP_BIT_7_HL();
    u32 OP_BIT_7_A();

    // CB 0x80 - 0x8F
    u32 OP_RES_0_B();
    u32 OP_RES_0_C();
    u32 OP_RES_0_D();
    u32 OP_RES_0_E();
    u32 OP_RES_0_H();
    u32 OP_RES_0_L();
    u32 OP_RES_0_HL();
    u32 OP_RES_0_A();
    u32 OP_RES_1_B();
    u32 OP_RES_1_C();
    u32 OP_RES_1_D();
    u32 OP_RES_1_E();
    u32 OP_RES_1_H();
    u32 OP_RES_1_L();
    u32 OP_RES_1_HL();
    u32 OP_RES_1_A();

    // CB 0x90 - 0x9F
    u32 OP_RES_2_B();
    u32 OP_RES_2_C();
    u32 OP_RES_2_D();
    u32 OP_RES_2_E();
    u32 OP_RES_2_H();
    u32 OP_RES_2_L();
    u32 OP_RES_2_HL();
    u32 OP_RES_2_A();
    u32 OP_RES_3_B();
    u32 OP_RES_3_C();
    u32 OP_RES_3_D();
    u32 OP_RES_3_E();
    u32 OP_RES_3_H();
    u32 OP_RES_3_L();
    u32 OP_RES_3_HL();
    u32 OP_RES_3_A();

    // CB 0xA0 - 0xAF
    u32 OP_RES_4_B();
    u32 OP_RES_4_C();
    u32 OP_RES_4_D();
    u32 OP_RES_4_E();
    u32 OP_RES_4_H();
    u32 OP_RES_4_L();
    u32 OP_RES_4_HL();
    u32 OP_RES_4_A();
    u32 OP_RES_5_B();
    u32 OP_RES_5_C();
    u32 OP_RES_5_D();
    u32 OP_RES_5_E();
    u32 OP_RES_5_H();
    u32 OP_RES_5_L();
    u32 OP_RES_5_HL();
    u32 OP_RES_5_A();

    // CB 0xB0 - 0xBF
    u32 OP_RES_6_B();
    u32 OP_RES_6_C();
    u32 OP_RES_6_D();
    u32 OP_RES_6_E();
    u32 OP_RES_6_H();
    u32 OP_RES_6_L();
    u32 OP_RES_6_HL();
    u32 OP_RES_6_A();
    u32 OP_RES_7_B();
    u32 OP_RES_7_C();
    u32 OP_RES_7_D();
    u32 OP_RES_7_E();
    u32 OP_RES_7_H();
    u32 OP_RES_7_L();
    u32 OP_RES_7_HL();
    u32 OP_RES_7_A();

    // CB 0xC0 - 0xCF
    u32 OP_SET_0_B();
    u32 OP_SET_0_C();
    u32 OP_SET_0_D();
    u32 OP_SET_0_E();
    u32 OP_SET_0_H();
    u32 OP_SET_0_L();
    u32 OP_SET_0_HL();
    u32 OP_SET_0_A();
    u32 OP_SET_1_B();
    u32 OP_SET_1_C();
    u32 OP_SET_1_D();
    u32 OP_SET_1_E();
    u32 OP_SET_1_H();
    u32 OP_SET_1_L();
    u32 OP_SET_1_HL();
    u32 OP_SET_1_A();

    // CB 0xD0 - 0xDF
    u32 OP_SET_2_B();
    u32 OP_SET_2_C();
    u32 OP_SET_2_D();
    u32 OP_SET_2_E();
    u32 OP_SET_2_H();
    u32 OP_SET_2_L();
    u32 OP_SET_2_HL();
    u32 OP_SET_2_A();
    u32 OP_SET_3_B();
    u32 OP_SET_3_C();
    u32 OP_SET_3_D();
    u32 OP_SET_3_E();
    u32 OP_SET_3_H();
    u32 OP_SET_3_L();
    u32 OP_SET_3_HL();
    u32 OP_SET_3_A();

    // CB 0xE0 - 0xEF
    u32 OP_SET_4_B();
    u32 OP_SET_4_C();
    u32 OP_SET_4_D();
    u32 OP_SET_4_E();
    u32 OP_SET_4_H();
    u32 OP_SET_4_L();
    u32 OP_SET_4_HL();
    u32 OP_SET_4_A();
    u32 OP_SET_5_B();
    u32 OP_SET_5_C();
    u32 OP_SET_5_D();
    u32 OP_SET_5_E();
    u32 OP_SET_5_H();
    u32 OP_SET_5_L();
    u32 OP_SET_5_HL();
    u32 OP_SET_5_A();

    // CB 0xF0 - 0xFF
    u32 OP_SET_6_B();
    u32 OP_SET_6_C();
    u32 OP_SET_6_D();
    u32 OP_SET_6_E();
    u32 OP_SET_6_H();
    u32 OP_SET_6_L();
    u32 OP_SET_6_HL();
    u32 OP_SET_6_A();
    u32 OP_SET_7_B();
    u32 OP_SET_7_C();
    u32 OP_SET_7_D();
    u32 OP_SET_7_E();
    u32 OP_SET_7_H();
    u32 OP_SET_7_L();
    u32 OP_SET_7_HL();
    u32 OP_SET_7_A();

private:
    MMU* mmu;
    array<Instruction, 256> opcodes;
    array<Instruction, 256> extOpcodes;
};