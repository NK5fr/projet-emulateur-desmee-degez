#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream>  
#include <map> 
#include <bitset>

using namespace std; 

class IEncodingInstruction {

  private : 
    static map<string, map<uint32_t, string>> instructions;   
    string name;
    uint32_t word;

  public :
    string getName();
    string getRd();
    string getRs1();
    int32_t getImm();
    IEncodingInstruction(uint32_t word, string name) ;
    void printInstruction(string offset);
} ;