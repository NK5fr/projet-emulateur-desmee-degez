#include <iostream> 
#include <string>
#include <sstream>  
#include <map> 
#include <bitset>

using namespace std; 

class REncodingInstruction {

  private :    
    string name;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;

  public :
    static map<string, map<string, string>> instructions;
    REncodingInstruction(uint32_t word, string name) ;
    string getName();
    void printInstruction();
} ;