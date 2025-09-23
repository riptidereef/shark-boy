#include "cartridge.h"
#include <fstream>
#include <iostream>

bool Cartridge::loadRom(string filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) {
        cerr << "Failed to open ROM: " << filename << endl;
        return false;
    }

    romSize = file.tellg();
    file.seekg(0, ios::beg);

    romData = make_unique<u8[]>(romSize);

    file.read(reinterpret_cast<char*>(romData.get()), romSize);

    const u16 headerAddr = 0x0100;

    memcpy(romHeader.entry, romData.get() + headerAddr, 4);
    memcpy(romHeader.logo, romData.get() + headerAddr + 0x04, 48);
    memcpy(romHeader.title, romData.get() + headerAddr + 0x34, 16);
    memcpy(romHeader.manufacturer, romData.get() + headerAddr + 0x3F, 4);
    
    romHeader.cgbFlag = *(romData.get() + headerAddr + 0x43);

    memcpy(romHeader.newLicenseeCode, romData.get() + headerAddr + 0x44, 2);

    romHeader.sgbFlag = *(romData.get() + headerAddr + 0x46);
    romHeader.cartridgeType = *(romData.get() + headerAddr + 0x47);
    romHeader.romSize = *(romData.get() + headerAddr + 0x48);
    romHeader.ramSize = *(romData.get() + headerAddr + 0x49);
    romHeader.destinationCode = *(romData.get() + headerAddr + 0x4A);
    romHeader.oldLicenseeCode = *(romData.get() + headerAddr + 0x4B);
    romHeader.maskRomVersion = *(romData.get() + headerAddr + 0x4C);
    romHeader.headerChecksum = *(romData.get() + headerAddr + 0x4D);

    romHeader.globalChecksum = *(u16*)(romData.get() + headerAddr + 0x4E);

    return true;
}