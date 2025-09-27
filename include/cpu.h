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


private:
    MMU* mmu;
    array<Instruction, 256> opcodes;
    array<Instruction, 256> cbOpcodes;
};