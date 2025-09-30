#include "cpu.h"
#include <iostream>

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











u32 CPU::OP_JP_a16() {
    pc = peek16();
    return 16;
}