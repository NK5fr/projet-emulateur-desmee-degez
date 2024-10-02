#ifndef Memory_H
#define Memory_H

#include <iostream> 

using namespace std; 

class Memory {

    private :
        char* memory;
    
    public :
        Memory(uint32_t size, string filename);
        void loadFile(string filename);
        uint32_t readMemory(int start, int size);
};

#endif