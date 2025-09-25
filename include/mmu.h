#pragma once
#include "common.h"

class MMU {
public:
    void write8(u16 address, u8 data);
    u8 read8(u16 address);
    void write16(u16 address, u16 data);
    u16 read16(u16 address);

private:
    Cartridge* cartridge;
};