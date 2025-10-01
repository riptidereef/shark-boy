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
    return 0;
}

u32 CPU::OP_POP_BC() {
    return 12;
}

u32 CPU::OP_JP_NZ_a16() {
    return 0;
}

u32 CPU::OP_JP_a16() {
    pc = peek16();
    return 16;
}