#include <iostream>
#include <filesystem>
#include "emulator.h"
using namespace std;

int main() {
    cout << "Current working directory: " << filesystem::current_path() << endl;
    Emulator sharkBoy;
    sharkBoy.loadCartridge("data/PokemonRed.gb");
    sharkBoy.run();
}