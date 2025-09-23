#include <iostream>
#include <common.h>
#include <cartridge.h>
using namespace std;

int main() {
    Cartridge cart;
    if (cart.loadRom("../data/PokemonRed.gb")) {
        cart.printRomInfo();
    }
}