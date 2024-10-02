#ifndef Memory_H
#define Memory_H

#include <iostream> 
#include <fstream>

using namespace std; 

class Memory {

    private :
        char* memory;
        int size;
    
    public :
        Memory(uint32_t size);
        void loadFile(string filename);
        uint32_t readMemory(int start, int size);
};

#endif