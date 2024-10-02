#ifndef UEncodingInstruction_H
#define UEncodingInstruction_H

#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream> 
#include "Instruction.h"

using namespace std; 

class UEncodingInstruction : public Instruction {

  private :    
    string name;
    uint32_t word;
    int32_t getImmJ();

  public :
    UEncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getRd();
    int32_t getImm();
    void printInstruction() override;
    void execute(int32_t* regs, uint32_t* pc) override;
} ;

#endif