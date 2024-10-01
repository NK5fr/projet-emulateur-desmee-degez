#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream>  
#include <map> 
#include <bitset>

using namespace std; 

class REncodingInstruction {

  private :    
    string name;
    uint32_t word;

  public :
    static map<string, map<uint32_t, string>> instructions;
    REncodingInstruction(uint32_t word, string name) ;
    string getName();
    string getRd();
    string getRs1();
    string getRs2();
    void printInstruction(string offset);
} ;