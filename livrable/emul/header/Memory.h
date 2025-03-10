#ifndef Memory_H
#define Memory_H

#include <iostream> 
#include <fstream>
#include <sstream> 
#include <climits>

using namespace std; 

class Memory {

    private :
        char* memory;
        int size;
    
    public :
        Memory(uint32_t size);
        void loadFile(string filename);
        uint32_t readMemory(int start, int size, bool isSigned=false);
        void writeMemory(int start, int size, int32_t word);
};

#endif