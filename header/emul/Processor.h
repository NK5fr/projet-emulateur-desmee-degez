#ifndef Processor_H
#define Processor_H

#include <iostream> 
#include <string> 
#include <map> 
#include <array>
#include "IEncodingInstruction.h"
#include "REncodingInstruction.h"
#include "SEncodingInstruction.h"
#include "UEncodingInstruction.h"
#include "Memory.h"

using namespace std; 

class Processor {
    private :
        static map<uint32_t, array<string, 2>> opcode;
        int32_t* regs;
        uint32_t pc;
        uint32_t reset;
        Memory* memory;

        void printRegisters();
        uint32_t getOpcode(uint32_t word);
    
    public :
        Processor(uint32_t pc, uint32_t memorySize, string filename);
        void runContinuous();
        void runStepByStep();
};

#endif