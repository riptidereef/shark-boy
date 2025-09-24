#pragma once
#include <string>
#include "common.h"
#include "cartridge.h"
using namespace std;

class Emulator {
public:
    bool paused;
    bool running;
    u64 ticks;

    void loadCartridge(const string& romPath);

private:
    Cartridge cart;
};
