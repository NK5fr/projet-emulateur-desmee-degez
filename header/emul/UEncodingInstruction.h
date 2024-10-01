#ifndef UEncodingInstruction_H
#define UEncodingInstruction_H

#include "EncodingInstruction.h"

using namespace std; 

class UEncodingInstruction : public EncodingInstruction {

  private :    
    string name;
    uint32_t word;
    int32_t getImmJ();

  public :
    UEncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getRd();
    int32_t getImm();
    void printInstruction();
    void execute();
} ;

#endif