#include "emulator.h"
#include <iostream>

Emulator::Emulator() {
    loadCartridge("../data/PokemonRed.gb");
}

void Emulator::loadCartridge(const string& romPath) {
    cartridge = make_unique<Cartridge>(romPath);
    cartridge->printRomInfo();
}