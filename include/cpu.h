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
    void OP_JR_r8();
    void OP_ADD_HL_DE();
    void OP_LD_A_DE();
    void OP_DEC_DE();
    void OP_INC_E();
    void OP_DEC_E();
    void OP_LD_E_d8();
    void OP_RRA();

    // 0x20-0x2F
    void OP_JR_NZ_r8();
    void OP_LD_HL_d16();
    void OP_LD_HLp_A();
    void OP_INC_HL();
    void OP_INC_H();
    void OP_DEC_H();
    void OP_LD_H_d8();
    void OP_DAA();
    void OP_JR_Z_r8();
    void OP_ADD_HL_HL();
    void OP_LD_A_HLp();
    void OP_DEC_HL();
    void OP_INC_L();
    void OP_DEC_L();
    void OP_LD_L_d8();
    void OP_CPL();

    // 0x30-0x3F
    void OP_JR_NC_r8();
    void OP_LD_SP_d16();
    void OP_LD_HLm_A();
    void OP_INC_SP();
    void OP_INC_atHL();
    void OP_DEC_atHL();
    void OP_LD_HL_d8();
    void OP_SCF();
    void OP_JR_C_r8();
    void OP_ADD_HL_SP();
    void OP_LD_A_HLm();
    void OP_DEC_SP();
    void OP_INC_A();
    void OP_DEC_A();
    void OP_LD_A_d8();
    void OP_CCF();

    // 0xC0-0xCF
    void OP_JP_a16();


private:
    MMU* mmu;
    array<Instruction, 256> opcodes;
    array<Instruction, 256> cbOpcodes;
};