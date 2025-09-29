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
    
    using Instruction = void (CPU::*)();
    
    void step();

    // 0x00-0x0F
    void OP_NOP();
    void OP_LD_BC_d16();
    void OP_LD_BC_A();
    void OP_INC_BC();
    void OP_INC_B();
    void OP_DEC_B();
    void OP_LD_B_d8();
    void OP_RLCA();
    void OP_LD_a16_SP();
    void OP_ADD_HL_BC();
    void OP_LD_A_BC();
    void OP_DEC_BC();
    void OP_INC_C();
    void OP_DEC_C();
    void OP_LD_C_d8();
    void OP_RRCA();

    // 0x10-0x1F
    void OP_STOP();
    void OP_LD_DE_d16();
    void OP_LD_DE_A();
    void OP_INC_DE();
    void OP_INC_D();
    void OP_DEC_D();
    void OP_LD_D_d8();
    void OP_RLA();
    void OP_JR_s8();
    void OP_ADD_HL_DE();
    void OP_LD_A_DE();
    void OP_DEC_DE();
    void OP_INC_E();
    void OP_DEC_E();
    void OP_LD_E_d8();
    void OP_RRA();

    // 0x20-0x2F
    void OP_JR_NZ_s8();
    void OP_LD_HL_d16();
    void OP_LD_HLp_A();
    void OP_INC_HL();
    void OP_INC_H();
    void OP_DEC_H();
    void OP_LD_H_d8();
    void OP_DAA();
    void OP_JR_Z_s8();
    void OP_ADD_HL_HL();
    void OP_LD_A_HLp();
    void OP_DEC_HL();
    void OP_INC_L();
    void OP_DEC_L();
    void OP_LD_L_d8();
    void OP_CPL();

    // 0x30-0x3F
    void OP_JR_NC_s8();
    void OP_LD_SP_d16();
    void OP_LD_HLm_A();
    void OP_INC_SP();
    void OP_INC_aHL();
    void OP_DEC_aHL();
    void OP_LD_HL_d8();
    void OP_SCF();
    void OP_JR_C_s8();
    void OP_ADD_HL_SP();
    void OP_LD_A_HLm();
    void OP_DEC_SP();
    void OP_INC_A();
    void OP_DEC_A();
    void OP_LD_A_d8();
    void OP_CCF();

    // 0x40 - 0x4F
    void OP_LD_B_B();
    void OP_LD_B_C();
    void OP_LD_B_D();
    void OP_LD_B_E();
    void OP_LD_B_H();
    void OP_LD_B_L();
    void OP_LD_B_HL();
    void OP_LD_B_A();
    void OP_LD_C_B();
    void OP_LD_C_C();
    void OP_LD_C_D();
    void OP_LD_C_E();
    void OP_LD_C_H();
    void OP_LD_C_L();
    void OP_LD_C_HL();
    void OP_LD_C_A();

    // 0x50-0x5F
    void OP_LD_D_B();
    void OP_LD_D_C();
    void OP_LD_D_D();
    void OP_LD_D_E();
    void OP_LD_D_H();
    void OP_LD_D_L();
    void OP_LD_D_HL();
    void OP_LD_D_A();
    void OP_LD_E_B();
    void OP_LD_E_C();
    void OP_LD_E_D();
    void OP_LD_E_E();
    void OP_LD_E_H();
    void OP_LD_E_L();
    void OP_LD_E_HL();
    void OP_LD_E_A();

    // 0x60-0x6F
    void OP_LD_H_B();
    void OP_LD_H_C();
    void OP_LD_H_D();
    void OP_LD_H_E();
    void OP_LD_H_H();
    void OP_LD_H_L();
    void OP_LD_H_HL();
    void OP_LD_H_A();
    void OP_LD_L_B();
    void OP_LD_L_C();
    void OP_LD_L_D();
    void OP_LD_L_E();
    void OP_LD_L_H();
    void OP_LD_L_L();
    void OP_LD_L_HL();
    void OP_LD_L_A();

    // 0x70-0x7F
    void OP_LD_HL_B();
    void OP_LD_HL_C();
    void OP_LD_HL_D();
    void OP_LD_HL_E();
    void OP_LD_HL_H();
    void OP_LD_HL_L();
    void OP_HALT();
    void OP_LD_HL_A();
    void OP_LD_A_B();
    void OP_LD_A_C();
    void OP_LD_A_D();
    void OP_LD_A_E();
    void OP_LD_A_H();
    void OP_LD_A_L();
    void OP_LD_A_HL();
    void OP_LD_A_A();

    // 0x80-0x8F
    void OP_ADD_A_B();
    void OP_ADD_A_C();
    void OP_ADD_A_D();
    void OP_ADD_A_E();
    void OP_ADD_A_H();
    void OP_ADD_A_L();
    void OP_ADD_A_HL();
    void OP_ADD_A_A();
    void OP_ADC_A_B();
    void OP_ADC_A_C();
    void OP_ADC_A_D();
    void OP_ADC_A_E();
    void OP_ADC_A_H();
    void OP_ADC_A_L();
    void OP_ADC_A_HL();
    void OP_ADC_A_A();

    // 0x90-0x9F
    void OP_SUB_B();
    void OP_SUB_C();
    void OP_SUB_D();
    void OP_SUB_E();
    void OP_SUB_H();
    void OP_SUB_L();
    void OP_SUB_HL();
    void OP_SUB_A();
    void OP_SBC_A_B();
    void OP_SBC_A_C();
    void OP_SBC_A_D();
    void OP_SBC_A_E();
    void OP_SBC_A_H();
    void OP_SBC_A_L();
    void OP_SBC_A_HL();
    void OP_SBC_A_A();

    // 0xA0-0xAF
    void OP_AND_B();
    void OP_AND_C();
    void OP_AND_D();
    void OP_AND_E();
    void OP_AND_H();
    void OP_AND_L();
    void OP_AND_HL();
    void OP_AND_A();
    void OP_XOR_B();
    void OP_XOR_C();
    void OP_XOR_D();
    void OP_XOR_E();
    void OP_XOR_H();
    void OP_XOR_L();
    void OP_XOR_HL();
    void OP_XOR_A();

    // 0xB0-0xBF
    void OP_OR_B();
    void OP_OR_C();
    void OP_OR_D();
    void OP_OR_E();
    void OP_OR_H();
    void OP_OR_L();
    void OP_OR_HL();
    void OP_OR_A();
    void OP_CP_B();
    void OP_CP_C();
    void OP_CP_D();
    void OP_CP_E();
    void OP_CP_H();
    void OP_CP_L();
    void OP_CP_HL();
    void OP_CP_A();

    // 0xC0-0xCF
    void OP_RET_NZ();
    void OP_POP_BC();
    void OP_JP_NZ_a16();
    void OP_JP_a16();
    void OP_CALL_NZ_a16();
    void OP_PUSH_BC();
    void OP_ADD_A_d8();
    void OP_RST_0();
    void OP_RET_Z();
    void OP_RET();
    void OP_JP_Z_a16();
    void OP_CB_prefix();
    void OP_CALL_Z_a16();
    void OP_CALL_a16();
    void OP_ADC_A_d8();
    void OP_RST_1();

    // 0xD0-0xDF
    void OP_RET_NC();
    void OP_POP_DE();
    void OP_JP_NC_a16();
    // void OP_UNDEFINED_D3();
    void OP_CALL_NC_a16();
    void OP_PUSH_DE();
    void OP_SUB_d8();
    void OP_RST_2();
    void OP_RET_C();
    void OP_RETI();
    void OP_JP_C_a16();
    // void OP_UNDEFINED_DB();
    void OP_CALL_C_a16();
    // void OP_UNDEFINED_DD();
    void OP_SBC_A_d8();
    void OP_RST_3();

    // 0xE0-0xEF
    void OP_LD_a8_A();
    void OP_POP_HL();
    void OP_LD_aC_A();
    // void OP_UNDEFINED_E3();
    // void OP_UNDEFINED_E4();
    void OP_PUSH_HL();
    void OP_AND_d8();
    void OP_RST_4();
    void OP_ADD_SP_s8();
    void OP_JP_HL();
    void OP_LD_a16_A();
    // void OP_UNDEFINED_EB();
    // void OP_UNDEFINED_EC();
    // void OP_UNDEFINED_ED();
    void OP_XOR_d8();
    void OP_RST_5();

    // 0xF0-0xFF
    void OP_LDH_A_a8();
    void OP_POP_AF();
    void OP_LD_A_aC();
    void OP_DI();
    // void OP_UNDEFINED_F4();
    void OP_PUSH_AF();
    void OP_OR_d8();
    void OP_RST_6();
    void OP_LD_HL_SP_s8();
    void OP_LD_SP_HL();
    void OP_LD_A_a16();
    void OP_EI();
    // void OP_UNDEFINED_FC();
    // void OP_UNDEFINED_FD();
    void OP_CP_d8();
    void OP_RST_7();

    // CB-prefix opcodes
    // CB 0x00-0x0F
    void OP_RLC_B();
    void OP_RLC_C();
    void OP_RLC_D();
    void OP_RLC_E();
    void OP_RLC_H();
    void OP_RLC_L();
    void OP_RLC_HL();
    void OP_RLC_A();
    void OP_RRC_B();
    void OP_RRC_C();
    void OP_RRC_D();
    void OP_RRC_E();
    void OP_RRC_H();
    void OP_RRC_L();
    void OP_RRC_HL();
    void OP_RRC_A();

    // CB 0x10-0x1F
    void OP_RL_B();
    void OP_RL_C();
    void OP_RL_D();
    void OP_RL_E();
    void OP_RL_H();
    void OP_RL_L();
    void OP_RL_HL();
    void OP_RL_A();
    void OP_RR_B();
    void OP_RR_C();
    void OP_RR_D();
    void OP_RR_E();
    void OP_RR_H();
    void OP_RR_L();
    void OP_RR_HL();
    void OP_RR_A();

    // CB 0x20-0x2F
    void OP_SLA_B();
    void OP_SLA_C();
    void OP_SLA_D();
    void OP_SLA_E();
    void OP_SLA_H();
    void OP_SLA_L();
    void OP_SLA_HL();
    void OP_SLA_A();
    void OP_SRA_B();
    void OP_SRA_C();
    void OP_SRA_D();
    void OP_SRA_E();
    void OP_SRA_H();
    void OP_SRA_L();
    void OP_SRA_HL();
    void OP_SRA_A();

    // CB 0x30-0x3F
    void OP_SWAP_B();
    void OP_SWAP_C();
    void OP_SWAP_D();
    void OP_SWAP_E();
    void OP_SWAP_H();
    void OP_SWAP_L();
    void OP_SWAP_HL();
    void OP_SWAP_A();
    void OP_SRL_B();
    void OP_SRL_C();
    void OP_SRL_D();
    void OP_SRL_E();
    void OP_SRL_H();
    void OP_SRL_L();
    void OP_SRL_HL();
    void OP_SRL_A();

    // CB 0x40–0x4F
    void OP_BIT_0_B();
    void OP_BIT_0_C();
    void OP_BIT_0_D();
    void OP_BIT_0_E();
    void OP_BIT_0_H();
    void OP_BIT_0_L();
    void OP_BIT_0_HL();
    void OP_BIT_0_A();
    void OP_BIT_1_B();
    void OP_BIT_1_C();
    void OP_BIT_1_D();
    void OP_BIT_1_E();
    void OP_BIT_1_H();
    void OP_BIT_1_L();
    void OP_BIT_1_HL();
    void OP_BIT_1_A();

    // CB 0x50–0x5F
    void OP_BIT_2_B();
    void OP_BIT_2_C();
    void OP_BIT_2_D();
    void OP_BIT_2_E();
    void OP_BIT_2_H();
    void OP_BIT_2_L();
    void OP_BIT_2_HL();
    void OP_BIT_2_A();
    void OP_BIT_3_B();
    void OP_BIT_3_C();
    void OP_BIT_3_D();
    void OP_BIT_3_E();
    void OP_BIT_3_H();
    void OP_BIT_3_L();
    void OP_BIT_3_HL();
    void BIT_3_A();

    // CB 0x60–0x6F
    void OP_BIT_4_B();
    void OP_BIT_4_C();
    void OP_BIT_4_D();
    void OP_BIT_4_E();
    void OP_BIT_4_H();
    void OP_BIT_4_L();
    void OP_BIT_4_HL();
    void OP_BIT_4_A();
    void OP_BIT_5_B();
    void OP_BIT_5_C();
    void OP_BIT_5_D();
    void OP_BIT_5_E();
    void OP_BIT_5_H();
    void OP_BIT_5_L();
    void OP_BIT_5_HL();
    void OP_BIT_5_A();

    // CB 0x70–0x7F
    void OP_BIT_6_B();
    void OP_BIT_6_C();
    void OP_BIT_6_D();
    void OP_BIT_6_E();
    void OP_BIT_6_H();
    void OP_BIT_6_L();
    void OP_BIT_6_HL();
    void OP_BIT_6_A();
    void OP_BIT_7_B();
    void OP_BIT_7_C();
    void OP_BIT_7_D();
    void OP_BIT_7_E();
    void OP_BIT_7_H();
    void OP_BIT_7_L();
    void OP_BIT_7_HL();
    void OP_BIT_7_A();

    // CB 0x80 - 0x8F
    void OP_RES_0_B();
    void OP_RES_0_C();
    void OP_RES_0_D();
    void OP_RES_0_E();
    void OP_RES_0_H();
    void OP_RES_0_L();
    void OP_RES_0_HL();
    void OP_RES_0_A();
    void OP_RES_1_B();
    void OP_RES_1_C();
    void OP_RES_1_D();
    void OP_RES_1_E();
    void OP_RES_1_H();
    void OP_RES_1_L();
    void OP_RES_1_HL();
    void OP_RES_1_A();

    // CB 0x90 - 0x9F
    void OP_RES_2_B();
    void OP_RES_2_C();
    void OP_RES_2_D();
    void OP_RES_2_E();
    void OP_RES_2_H();
    void OP_RES_2_L();
    void OP_RES_2_HL();
    void OP_RES_2_A();
    void OP_RES_3_B();
    void OP_RES_3_C();
    void OP_RES_3_D();
    void OP_RES_3_E();
    void OP_RES_3_H();
    void OP_RES_3_L();
    void OP_RES_3_HL();
    void OP_RES_3_A();

    // CB 0xA0 - 0xAF
    void OP_RES_4_B();
    void OP_RES_4_C();
    void OP_RES_4_D();
    void OP_RES_4_E();
    void OP_RES_4_H();
    void OP_RES_4_L();
    void OP_RES_4_HL();
    void OP_RES_4_A();
    void OP_RES_5_B();
    void OP_RES_5_C();
    void OP_RES_5_D();
    void OP_RES_5_E();
    void OP_RES_5_H();
    void OP_RES_5_L();
    void OP_RES_5_HL();
    void OP_RES_5_A();

    // CB 0xB0 - 0xBF
    void OP_RES_6_B();
    void OP_RES_6_C();
    void OP_RES_6_D();
    void OP_RES_6_E();
    void OP_RES_6_H();
    void OP_RES_6_L();
    void OP_RES_6_HL();
    void OP_RES_6_A();
    void OP_RES_7_B();
    void OP_RES_7_C();
    void OP_RES_7_D();
    void OP_RES_7_E();
    void OP_RES_7_H();
    void OP_RES_7_L();
    void OP_RES_7_HL();
    void OP_RES_7_A();

    // CB 0xC0 - 0xCF
    void OP_SET_0_B();
    void OP_SET_0_C();
    void OP_SET_0_D();
    void OP_SET_0_E();
    void OP_SET_0_H();
    void OP_SET_0_L();
    void OP_SET_0_HL();
    void OP_SET_0_A();
    void OP_SET_1_B();
    void OP_SET_1_C();
    void OP_SET_1_D();
    void OP_SET_1_E();
    void OP_SET_1_H();
    void OP_SET_1_L();
    void OP_SET_1_HL();
    void OP_SET_1_A();

    // CB 0xD0 - 0xDF
    void OP_SET_2_B();
    void OP_SET_2_C();
    void OP_SET_2_D();
    void OP_SET_2_E();
    void OP_SET_2_H();
    void OP_SET_2_L();
    void OP_SET_2_HL();
    void OP_SET_2_A();
    void OP_SET_3_B();
    void OP_SET_3_C();
    void OP_SET_3_D();
    void OP_SET_3_E();
    void OP_SET_3_H();
    void OP_SET_3_L();
    void OP_SET_3_HL();
    void OP_SET_3_A();

    // CB 0xE0 - 0xEF
    void OP_SET_4_B();
    void OP_SET_4_C();
    void OP_SET_4_D();
    void OP_SET_4_E();
    void OP_SET_4_H();
    void OP_SET_4_L();
    void OP_SET_4_HL();
    void OP_SET_4_A();
    void OP_SET_5_B();
    void OP_SET_5_C();
    void OP_SET_5_D();
    void OP_SET_5_E();
    void OP_SET_5_H();
    void OP_SET_5_L();
    void OP_SET_5_HL();
    void OP_SET_5_A();

    // CB 0xF0 - 0xFF
    void OP_SET_6_B();
    void OP_SET_6_C();
    void OP_SET_6_D();
    void OP_SET_6_E();
    void OP_SET_6_H();
    void OP_SET_6_L();
    void OP_SET_6_HL();
    void OP_SET_6_A();
    void OP_SET_7_B();
    void OP_SET_7_C();
    void OP_SET_7_D();
    void OP_SET_7_E();
    void OP_SET_7_H();
    void OP_SET_7_L();
    void OP_SET_7_HL();
    void OP_SET_7_A();

private:
    MMU* mmu;
    array<Instruction, 256> opcodes;
    array<Instruction, 256> cbOpcodes;
};