#pragma once
#include <array>
#include "common.h"
using namespace std;

class PPU {
public:
    void write8(u16 address, u8 data);
    u8 read8(u16 address);
    void write16(u16 address, u16 data);
    u16 read16(u16 address);

private:
    array<u8, 0x2000> vram {};
};