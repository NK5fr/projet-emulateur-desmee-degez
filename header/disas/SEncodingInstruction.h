#include <iostream> 
#include <string>
#include <sstream>  
#include <map> 
#include <bitset>

using namespace std; 

class SEncodingInstruction {

  private :    
    string name;
    uint32_t rs1;
    uint32_t rs2;
    int32_t imm;

  public :
    static map<string, map<string, string>> instructions;
    SEncodingInstruction(uint32_t word, string name) ;
    void printInstruction();
} ;