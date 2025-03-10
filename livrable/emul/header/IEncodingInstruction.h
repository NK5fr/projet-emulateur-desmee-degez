#ifndef IEncodingInstruction_H
#define IEncodingInstruction_H

#include <map>
#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream> 
#include "Instruction.h"
#include "EbreakException.h"

using namespace std;

class IEncodingInstruction : public Instruction{

  private : 
    static map<string, map<uint32_t, string>> instructions;   
    string name;
    uint32_t word;

  public :
    IEncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getFunct3();
    uint32_t getFunct7();
    uint32_t getRd();
    uint32_t getRs1();
    int32_t getImm();
    void printInstruction() override;
    void execute(int32_t* regs, uint32_t* pc, Memory* memory) override;
} ;

#endif