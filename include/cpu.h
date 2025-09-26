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

private:
    MMU* mmu;
    array<Instruction, 256> opcodes;
    array<Instruction, 256> cbOpcodes;
};