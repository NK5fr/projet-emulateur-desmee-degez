#ifndef Processor_H
#define Processor_H

#include <iostream> 
#include <string> 
#include <map> 
#include <array>
#include "Instruction.h"
#include "IEncodingInstruction.h"
#include "REncodingInstruction.h"
#include "SEncodingInstruction.h"
#include "UEncodingInstruction.h"
#include "Memory.h"
#include <vector>

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
        vector<string> split(const string& str, char delimiter);
        Instruction* getInstruction(uint32_t word, uint32_t opc);
        string getOpcodeError(uint32_t word, uint32_t opc);
        void getCommand(string* defaultCommand, string* command);
        uint32_t getMemoryValue(string command);
        Instruction* createInstruction(uint32_t word, uint32_t opc, bool* continuous);
        void executeInstruction(Instruction* instruction, string* defaultCommand, string* command, bool* continuous, bool* run);
    
    public :
        Processor(uint32_t pc, uint32_t memorySize, string filename);
        void run(bool b);
};

#endif