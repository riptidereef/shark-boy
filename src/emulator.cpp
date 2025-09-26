#include "emulator.h"
#include <iostream>

Emulator::Emulator() {
    loadCartridge("../data/PokemonRed.gb");

    ppu = make_unique<PPU>();
    mmu = make_unique<MMU>(ppu.get());
    cpu = make_unique<CPU>(mmu.get());
}

void Emulator::loadCartridge(const string& romPath) {
    cartridge = make_unique<Cartridge>(romPath);
    cartridge->printRomInfo();
}