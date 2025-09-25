#pragma once
#include <string>
#include <common.h>
#include <memory>
using namespace std;

struct RomHeader {
    u8 entry[4] {};
    u8 logo[48] {};
    char title[16] {};
    char manufacturer[4] {};
    u8 cgbFlag;
    char newLicenseeCode[2] {};
    u8 sgbFlag;
    u8 cartridgeType;
    u8 romSize;
    u8 ramSize;
    u8 destinationCode;
    u8 oldLicenseeCode;
    u8 maskRomVersion;
    u8 headerChecksum;
    u16 globalChecksum;
};

class Cartridge {
public:
    Cartridge(string romPath);
    void printRomInfo();
    
private:
    bool loadRom(string filename);

    RomHeader romHeader;
    string romPath;
    u32 romSize;
    unique_ptr<u8[]> romData;
};