#ifndef IEncodingInstruction_H
#define IEncodingInstruction_H

#include "EncodingInstruction.h"

class IEncodingInstruction : public EncodingInstruction {

  private : 
    static map<string, map<uint32_t, string>> instructions;   
    string name;
    uint32_t word;

  public :
    IEncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getRd();
    uint32_t getRs1();
    int32_t getImm();
    void printInstruction();
    void execute();
} ;

#endif