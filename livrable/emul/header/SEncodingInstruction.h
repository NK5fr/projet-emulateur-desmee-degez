#ifndef SEncodingInstruction_H
#define SEncodingInstruction_H

#include <map>
#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream> 
#include "Instruction.h"

using namespace std;

class SEncodingInstruction : public Instruction {

  private :  
    static map<string, map<uint32_t, string>> instructions;  
    string name;
    uint32_t word;
    int32_t getImmB();

  public :
    SEncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getFunct3();
    uint32_t getRs1();
    uint32_t getRs2();
    int32_t getImm();
    void printInstruction() override;
    void execute(int32_t* regs, uint32_t* pc, Memory* memory) override;
} ;

#endif