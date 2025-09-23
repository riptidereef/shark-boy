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
}