#include "../../header/emul/Memory.h"

Memory::Memory(uint32_t size, string filename){
    this->memory = new char[size * 1024];
}

void Memory::loadFile(string filename){
    
}

uint32_t Memory::readMemory(int start, int size){
    uint32_t res = 0;
    for(int i = 0; i < size; ++i){
        res = res | (this->memory[start + i] << 8 * i);
    }
    return res;
}