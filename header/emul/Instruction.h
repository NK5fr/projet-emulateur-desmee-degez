#ifndef Instruction_H
#define Instruction_H

#include <string>

class Instruction {
public:
    virtual ~Instruction() = default;
    virtual void printInstruction() = 0;
    virtual void execute(int32_t* regs, uint32_t* pc, Memory* memory) = 0;
};

#endif