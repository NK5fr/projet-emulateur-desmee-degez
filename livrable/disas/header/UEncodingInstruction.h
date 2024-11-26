#include <iostream> 
#include <iomanip>
#include <string>
#include <sstream>   

using namespace std; 

class UEncodingInstruction {

  private :    
    string name;
    uint32_t word;

  public :
    UEncodingInstruction(uint32_t word, string name) ;
    string getName();
    string getRd();
    int32_t getImm();
    int32_t getImmJ();
    void printInstruction(string offset);
} ;