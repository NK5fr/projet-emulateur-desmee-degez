#ifndef REncodingInstruction_H
#define REncodingInstruction_H

#include <map>
#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream> 
#include "Instruction.h"

using namespace std; 

class REncodingInstruction : public Instruction {

  private :    
    static map<string, map<uint32_t, string>> instructions;
    static map<string, map<uint32_t, string>> mInstructions;
    string name;
    uint32_t word;

  public :
    REncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getFunct3();
    uint32_t getFunct7();
    uint32_t getRd();
    uint32_t getRs1();
    uint32_t getRs2();
    void printInstruction() override;
    void execute(int32_t* regs, uint32_t* pc, Memory* memory) override;
} ;

#endif