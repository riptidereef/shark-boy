#include <iostream>
#include "common.h"
#include "cartridge.h"
#include "emulator.h"
using namespace std;

int main() {
    Emulator emu;
    emu.loadCartridge("../data/PokemonRed.gb");
}