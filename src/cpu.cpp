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

    updateOpcodeTables();
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
    if (handleInterrupts()) {
        return;
    }

    if (ime_enable_next) {
        ime = 1;
        ime_enable_next = 0;
    }

    Instruction instr = fetchInstruction();
    u32 cycles = instr.execute(this);
}

CPU::Instruction CPU::fetchInstruction() {
    u16 startPc = pc;
    u8 opcode = fetch8();

    Instruction instr;
    if (opcode == 0xCB) {
        opcode = fetch8();
        pc++;
        instr = extOpcodes[opcode];
    }
    else {
        instr = opcodes[opcode];
    }

    cout << "0x" << right << uppercase << setfill('0') << setw(4) 
         << hex << startPc << " " << left << setw(14) << setfill(' ') 
         << instr.name << "\n";

    return instr;
}

bool CPU::handleInterrupts() {
    return false;
}