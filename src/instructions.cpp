#include "cpu.h"
#include <iostream>

void CPU::OP_NOP() {
    cout << "NOP" << endl;
}

void CPU::OP_LD_BC_d16() {
    cout << "LD BC, d16" << endl;
}

void CPU::OP_LD_BC_A() {
    cout << "LD BC, A" << endl;
}