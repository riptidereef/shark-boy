#pragma once
#include <string>
#include <memory>
#include "common.h"
#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"
using namespace std;

class Emulator {
public:
    Emulator();
    void loadCartridge(const string& romPath);
    void run();

private:
    unique_ptr<Cartridge> cartridge;
    unique_ptr<CPU> cpu;
    unique_ptr<MMU> mmu;
    unique_ptr<PPU> ppu;
};
