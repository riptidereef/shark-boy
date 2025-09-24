#include "emulator.h"
#include <iostream>

void Emulator::loadCartridge(const string& romPath) {
    if (cart.loadRom(romPath)) {
        cart.printRomInfo();
    }
    else {
        cout << "Failed to load cartridge: " << romPath << endl;
    }
}