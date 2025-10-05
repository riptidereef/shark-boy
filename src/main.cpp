#include <iostream>
#include "emulator.h"
using namespace std;

int main() {
    Emulator sharkBoy;
    sharkBoy.loadCartridge("data/cpu_instrs.gb");
    sharkBoy.run();
}