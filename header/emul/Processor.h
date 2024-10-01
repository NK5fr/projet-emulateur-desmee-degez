#include <iostream> 

using namespace std; 

class Processor {
    private :
        uint32_t regs[32];
        uint32_t pc;
    
    public :
        Processor(uint32_t pc);
        Processor();
};