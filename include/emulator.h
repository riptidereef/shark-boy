#pragma once
#include <string>
#include "cartridge.h"
using namespace std;

class Emulator {
public:
    void loadCartridge(const string& romPath);

private:
    Cartridge cart;
};
