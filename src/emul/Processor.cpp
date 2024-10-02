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
    this->regs = new int32_t[32];
    this->pc = pc;
    this->reset = reset;
    this->memory = new Memory(memorySize);
    this->memory->loadFile(filename);
}


void Processor::printRegisters(){

    for(int i = 0; i < 32; ++i){
        cout << "x" << dec << i << " : " << hex << regs[i];
        if((i+1) % 4 == 0){
            cout << endl;
        }else{
            cout << ", ";
        }
    }
}

uint32_t Processor::getOpcode(uint32_t word){
    uint32_t opcode = word & 0x7f;
    return opcode;
}

void Processor::runStepByStep(){
    string command;
    bool continuous = false;

    while(command.compare("exit")){
        printRegisters();
        cout << "pc : " << this->pc << " : ";

        uint32_t word = this->memory->readMemory(this->pc);
        uint32_t opc = getOpcode(word);

        try {
            array<string, 2>& values = opcode.at(opc);

            if(!values[1].compare("I")){
                IEncodingInstruction instruction(word, values[0]);
                instruction.printInstruction();
                instruction.execute();
            }else if(!values[1].compare("U") || !values[1].compare("U_J")){
                UEncodingInstruction instruction(word, values[0]);
                instruction.printInstruction();
                instruction.execute();
            }else if(!values[1].compare("R")){
                REncodingInstruction instruction(word, values[0]);
                instruction.printInstruction();
                instruction.execute();
            }else if(!values[1].compare("S") || !values[1].compare("S_B")){
                SEncodingInstruction instruction(word, values[0]);
                instruction.printInstruction();
                instruction.execute();
            }
            
        
        } catch (const out_of_range& oor) {
            stringstream ssword;
            ssword << hex << word;
            cout << "instruction set error: invalid opcode: error value: 0x" << hex << opc
                << " for word " << setfill('0') << setw(8) << ssword.str()
                << endl;
        } catch (const length_error& le) {
            cout << le.what() << endl;
        } catch (const invalid_argument& ia) {
            cout << ia.what() << endl;
        }

        cout << "rivemul : ";

        getline(cin, command);

        if(!command.compare("step")){
            this->pc += 4;
        }else if(!command.rfind("x/", 0)){ 
            cout << "x" << endl;
        }else if(!command.compare("reset")){
            this->pc = this->reset;
        }else if(!command.compare("continue")){
            command = "exit";
            continuous = true;
        }

    }

    if(continuous){
        runContinuous();
    }
}

void Processor::runContinuous(){
    bool run = true;

    while(run){
        uint32_t word = this->memory->readMemory(this->pc);
        uint32_t opc = getOpcode(word);

        try {
            array<string, 2>& values = opcode.at(opc);

            if(!values[1].compare("I")){
                IEncodingInstruction instruction(word, values[0]);
                instruction.execute();
            }else if(!values[1].compare("U") || !values[1].compare("U_J")){
                UEncodingInstruction instruction(word, values[0]);
                instruction.execute();
            }else if(!values[1].compare("R")){
                REncodingInstruction instruction(word, values[0]);
                instruction.execute();
            }else if(!values[1].compare("S") || !values[1].compare("S_B")){
                SEncodingInstruction instruction(word, values[0]);
                instruction.execute();
            }

            this->pc += 4;
        
        } catch (const out_of_range& oor) {
            run = false;
            stringstream ssword;
            ssword << hex << word;
            cout << "instruction set error: invalid opcode: error value: 0x" << hex << opc
                << " for word " << setfill('0') << setw(8) << ssword.str()
                << endl;
        } catch (const length_error& le) {
            cout << le.what() << endl;
        } catch (const invalid_argument& ia) {
            cout << ia.what() << endl;
        }
    }

    runStepByStep();
}

