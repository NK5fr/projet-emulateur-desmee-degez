#include <iostream> 
#include <string>
#include <sstream>  
#include <map> 
#include <bitset>

using namespace std; 

class IEncodingInstruction {

  private :    
    string name;
    uint32_t rd;
    uint32_t rs1;
    int32_t imm;

  public :
    static map<string, map<string, string>> instructions;
    IEncodingInstruction(uint32_t word, string name) ;
    string getName();
    void printInstruction();
} ;