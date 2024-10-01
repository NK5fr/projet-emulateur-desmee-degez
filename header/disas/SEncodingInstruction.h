#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream>  
#include <map> 
#include <bitset>

using namespace std; 

class SEncodingInstruction {

  private :    
    string name;
    uint32_t word;

  public :
    static map<string, map<uint32_t, string>> instructions;
    SEncodingInstruction(uint32_t word, string name) ;
    string getName();
    string getRs1();
    string getRs2();
    int32_t getImm();
    int32_t getImmB();
    void printInstruction(string offset);
} ;