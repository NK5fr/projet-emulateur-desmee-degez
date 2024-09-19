#include <iostream> 
#include <string>
#include <sstream>   

using namespace std; 

class UEncodingInstruction {

  private :    
    string name;
    uint32_t rd;
    int32_t imm;

  public :
    UEncodingInstruction(uint32_t word, string name) ;
    string getName();
    void printInstruction();
} ;