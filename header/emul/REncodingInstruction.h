#ifndef REncodingInstruction_H
#define REncodingInstruction_H

#include <map>
#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream> 

using namespace std; 

class REncodingInstruction {

  private :    
    static map<string, map<uint32_t, string>> instructions;
    string name;
    uint32_t word;

  public :
    REncodingInstruction(uint32_t word, string name);
    string getName();
    uint32_t getRd();
    uint32_t getRs1();
    uint32_t getRs2();
    void printInstruction();
    void execute();
} ;

#endif