#ifndef Instruction_H
#define Instruction_H

#include <string>

class Instruction {
public:
    virtual ~Instruction() = default;
    virtual void printInstruction() = 0;
    virtual void execute(int32_t* regs) = 0;
};

#endif