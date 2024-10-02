#include "../../header/emul/Processor.h"

map<uint32_t, array<string, 2>> Processor::opcode = {
    {99, {"BRANCH", "S_B"}},
    {103, {"JALR", "I"}},
    {3, {"LOAD", "I"}},
    {15, {"MISC-MEM", "I"}},
    {19, {"OP-IMM", "I"}},
    {115, {"SYSTEM", "I"}},
    {111, {"JAL", "U_J"}},
    {51, {"OP", "R"}},
    {35, {"STORE", "S"}},
    {23, {"AUIPC", "U"}},
    {55, {"LUI", "U"}}
};

Processor::Processor(uint32_t pc, uint32_t memorySize, string filename) {
    this->pc = pc;
    this->reset = reset;
    this->memory = new Memory(memorySize);
    this->memory->loadFile(filename);
}


void Processor::printRegisters(){
    for(int i = 0; i < 32; ++i){
        cout << "x" << i << " : " << regs[i] << endl;
    }
}

uint32_t Processor::getOpcode(uint32_t word){
    uint32_t opcode = word & 0x7f;
    return opcode;
}

void Processor::runStepByStep(){
    string command;
    bool continuous = false;

    while(!command.compare("exit")){
        printRegisters();
        cout << "pc : " << this->pc;

        uint32_t word = this->memory->readMemory(this->pc, 4);
        uint32_t opc = getOpcode(word);

        try {
            array<string, 2>& values = opcode.at(opc);

            EncodingInstruction* instructionPtr;

            if(!values[1].compare("I")){
                instructionPtr = new IEncodingInstruction(word, values[0]);
            }else if(!values[1].compare("U") || !values[1].compare("U_J")){
                instructionPtr = new UEncodingInstruction(word, values[0]);
            }else if(!values[1].compare("R")){
                instructionPtr = new REncodingInstruction(word, values[0]);
            }else if(!values[1].compare("S") || !values[1].compare("S_B")){
                instructionPtr = new SEncodingInstruction(word, values[0]);
            }

            EncodingInstruction instruction = *instructionPtr;

            instruction.printInstruction();

            getline(cin, command);

            if(!command.compare("step")){
                instruction.execute();
                this->pc++;
            }else if(!command.rfind("x/", 0)){ 
                cout << "x" << endl;
            }else if(!command.compare("reset")){
                this->pc = this->reset;
            }else if(!command.compare("continue")){
                command = "exit";
                continuous = true;
            }
        
        } catch (const out_of_range& oor) {
            stringstream ssword;
            ssword << hex << word;
            cout << "instruction set error: invalid opcode: error value: 0x" << hex << opc
                << " for word " << setfill('0') << setw(8) << ssword.str()
                << endl;
        } catch (const length_error& le) {
            cout << le.what() << endl;
        }

    }

    if(continuous){
        runContinuous();
    }
}

void Processor::runContinuous(){
    bool run = true;

    while(run){
        uint32_t word = this->memory->readMemory(this->pc, 4);
        uint32_t opc = getOpcode(word);

        try {
            array<string, 2>& values = opcode.at(opc);

            EncodingInstruction* instructionPtr;

            if(!values[1].compare("I")){
                instructionPtr = new IEncodingInstruction(word, values[0]);
            }else if(!values[1].compare("U") || !values[1].compare("U_J")){
                instructionPtr = new UEncodingInstruction(word, values[0]);
            }else if(!values[1].compare("R")){
                instructionPtr = new REncodingInstruction(word, values[0]);
            }else if(!values[1].compare("S") || !values[1].compare("S_B")){
                instructionPtr = new SEncodingInstruction(word, values[0]);
            }

            EncodingInstruction instruction = *instructionPtr;

            instruction.execute();

            this->pc++;
        
        } catch (const out_of_range& oor) {
            run = false;
            stringstream ssword;
            ssword << hex << word;
            cout << "instruction set error: invalid opcode: error value: 0x" << hex << opc
                << " for word " << setfill('0') << setw(8) << ssword.str()
                << endl;
        }
    }

    runStepByStep();
}

