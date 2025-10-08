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
        // cycles += 20
        return;
    }
    
    if (halted) {
        // cycles += 4
        return;
    }

    if (ime_enable_next) {
        ime = 1;
        ime_enable_next = 0;
    }

    Instruction instr = fetchInstruction();
    instr.execute(this);
    // cycles += instrCycles;

    handleSerial();
}

CPU::Instruction CPU::fetchInstruction() {
    u16 startPc = pc;
    u8 opcode = mmu->read8(pc);

    if (!halt_bug) {
        pc++;
    }
    halt_bug = false;

    Instruction instr;
    if (opcode == 0xCB) {
        opcode = fetch8();
        pc++;
        instr = extOpcodes[opcode];
    }
    else {
        instr = opcodes[opcode];
    }

    /*
    cout << "0x" << right << uppercase << setfill('0') << setw(4) 
         << hex << startPc << " " << left << setw(14) << setfill(' ') 
         << instr.name << "\n";
    */

    return instr;
}

bool CPU::handleInterrupts() {
    u8 pending = mmu->ie & mmu->if_reg;

    if (halted && pending) {
        halted = false;
    }
    
    if (!ime || !pending) return false;

    for (int i = 0; i <= 4; i++) {
        if (pending & (1 << i)) {
            mmu->if_reg &= ~(1 << i);
            ime = 0;

            sp -= 2;
            mmu->write16(sp, pc);

            switch (i) {
                case 0: pc = 0x0040; break;
                case 1: pc = 0x0048; break;
                case 2: pc = 0x0050; break;
                case 3: pc = 0x0058; break;
                case 4: pc = 0x0060; break;
            }

            return true;
        }
    }

    return false;
}

void CPU::handleSerial() {
    if (mmu->sc & 0x80) {
        cout << static_cast<char>(mmu->sb);
        mmu->sc &= ~0x80;
        mmu->if_reg |= (1 << 3);
    }
}