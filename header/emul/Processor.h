#ifndef Processor_H
#define Processor_H

#include <iostream> 
#include <string> 
#include <map> 
#include <array>
#include "EncodingInstruction.h"
#include "IEncodingInstruction.h"
#include "REncodingInstruction.h"
#include "SEncodingInstruction.h"
#include "UEncodingInstruction.h"

using namespace std; 

class Processor {
    private :
        static map<uint32_t, array<string, 2>> opcode;
        uint32_t regs[32];
        uint32_t pc;
        uint32_t reset;
        char* memory;
        bool run = true;

        void printRegisters();
        uint32_t getOpcode(uint32_t word);
        uint32_t readMemory(int start, int size);
    
    public :
        Processor(uint32_t pc, uint32_t memory);
        void runContinuous();
        void runStepByStep();
};

#endif