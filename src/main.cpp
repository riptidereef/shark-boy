#include <iostream>
#include "emulator.h"
using namespace std;

int main() {
    Emulator sharkBoy;
    sharkBoy.loadCartridge("data/PokemonRed.gb");
    sharkBoy.run();
}