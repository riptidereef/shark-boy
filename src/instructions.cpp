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

// FIXME
u32 CPU::OP_RETI() {
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

// FIXME
u32 CPU::OP_DI() {
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

// FIXME
u32 CPU::OP_LD_HL_SP_r8() {
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

// FIXME
u32 CPU::OP_EI() {
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