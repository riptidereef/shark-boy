#include "emulator.h"
#include <iostream>

Emulator::Emulator() {
    ppu = make_unique<PPU>();
    mmu = make_unique<MMU>(ppu.get());
    cpu = make_unique<CPU>(mmu.get());
}

void Emulator::loadCartridge(const string& romPath) {
    cartridge = make_unique<Cartridge>(romPath);
    cartridge->printRomInfo();

    mmu->setCartridge(cartridge.get());
}

void Emulator::run() {
    for (int i = 0; i < 10000000; i++)
        cpu->step();
}