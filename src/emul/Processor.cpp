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
        stringstream reg, value;
        reg << "x" << left << setfill(' ') << setw(2) << dec << i << " : ";
        value << setfill('0') << setw(8) << hex << regs[i];
        cout << reg.str() << value.str();
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

Instruction* Processor::createInstruction(uint32_t word, uint32_t opc){
    Instruction* instruction = nullptr;

    array<string, 2>& values = opcode.at(opc);

    if(!values[1].compare("I")){
        instruction = new IEncodingInstruction(word, values[0]);
    }else if(!values[1].compare("U") || !values[1].compare("U_J")){
        instruction = new UEncodingInstruction(word, values[0]);
    }else if(!values[1].compare("R")){
        instruction = new REncodingInstruction(word, values[0]);
    }else if(!values[1].compare("S") || !values[1].compare("S_B")){
        instruction = new SEncodingInstruction(word, values[0]);
    }

    return instruction;
}

string Processor::getOpcodeError(uint32_t word, uint32_t opc){
    stringstream message;
    stringstream ssword;
    ssword << hex << word;
    message << "instruction set error: invalid opcode: error value: 0x" << hex << opc
            << " for word " << setfill('0') << setw(8) << ssword.str();
    return message.str();
}

void Processor::printMemoryValue(string command){
    vector<string> splitedString = split(command, ' ');
    int count = stoi(split(splitedString.at(0), '/').at(1));
    int address = stoi(splitedString.at(1));
    int q = count / 4;
    int r = count % 4;
    cout << hex << address << " : ";
    for(int i = 0; i < q; ++i){
        uint32_t n = this->memory->readMemory(address + 4*i, 4);
        for(int j = 0; j < 4; ++j){
            cout << hex << ((n >> 8*j) & 0xff) << " ";
        }
    }
    if(r != 0){
        uint32_t n = this->memory->readMemory(address + 4*q, r);
        for(int j = 0; j < r; ++j){
            cout << hex << ((n >> 8*j) & 0xff) << " ";
        }
    }
    cout << endl;
}

void Processor::getCommand(){
    cout << "rivemul (default=" << this->defaultCommand << "): ";
    getline(cin, this->command);

    if(!command.compare("")) this->command = this->defaultCommand;
    else this->defaultCommand = this->command;
}

Instruction* Processor::getInstruction(uint32_t word, uint32_t opc){
    if (!this->continuous){
        printRegisters();
        stringstream pcValue;
        pcValue << setfill('0') << setw(8) << hex << this->pc;
        cout << "pc : " << pcValue.str() << " : ";
    }

    Instruction* instruction = nullptr;

    try {
        instruction = createInstruction(word, opc);
        if (!this->continuous && instruction) instruction->printInstruction();
    } catch (const out_of_range& oor) {
        cout << getOpcodeError(word, opc) << endl;
    } catch (const invalid_argument& ia) {
        cout << ia.what() << endl;
        instruction = nullptr;
    }

    return instruction;
}

void Processor::executeInstruction(Instruction* instruction){
    try {
        if(this->continuous){
            if(instruction){
                instruction->execute(this->regs, &(this->pc), this->memory);
                this->pc += 4;
            }else{
                this->continuous = false;
            }
        }else{
            getCommand();
            if (!command.compare("step")) {
                if (instruction) {
                    instruction->execute(this->regs, &(this->pc), this->memory);
                    this->pc += 4;
                }
            } else if (regex_match(this->command, regex("x/[0-9]* [0-9]*"))) { 
                printMemoryValue(this->command);
            } else if (!command.compare("reset")) {
                this->pc = this->reset;
            } else if (!command.compare("continue")) {
                this->continuous = true;
                if (instruction) {
                    instruction->execute(this->regs, &(this->pc), this->memory);
                    this->pc += 4;
                }
            } else if (!command.compare("exit")) {
                this->run = false;
            } else {
                cout << "unknown command : " << this->command << endl;
            }
        }
    } catch (const length_error& le) {
        cout << le.what() << endl;
        this->continuous = false;
    } catch (const EbreakException& eb){
        if(isSemiHosting()) {
            executeSemiHosting();
        } else {
            this->continuous = false;
            this->pc += 4;
        }
    }
}

int Processor::runEmulator(bool b){
    this->continuous = b;

    while(this->run){
        uint32_t word = this->memory->readMemory(this->pc, 4);
        uint32_t opc = getOpcode(word);

        Instruction* instruction = getInstruction(word, opc);

        executeInstruction(instruction);

        delete instruction;
    }

    return !this->command.compare("exit") ? 0 : 1;

}

vector<string> Processor::split(const string& str, char delimiter) {
    stringstream ss(str);
    vector<string> splitedString;
    string element;
    while (getline(ss, element, delimiter)) {
        splitedString.push_back(element);
    }

    return splitedString;
}

bool Processor::isSemiHosting(){
    uint32_t wordBefore = this->memory->readMemory(this->pc-4, 4);
    uint32_t wordAfter = this->memory->readMemory(this->pc+4, 4);
    return (wordBefore == 0x01f01013) && (wordAfter == 0x40705013);
}

void Processor::executeSemiHosting(){
    try {
        uint32_t instruction = (uint32_t) this->regs[10];
        int emplacement = this->regs[11];
        char c;
        int n;
        switch (instruction) {
            case 0x03:
                c = (char) this->memory->readMemory(emplacement, 1);
                cout << c ;
                break;
            case 0x04:
                c = (char) this->memory->readMemory(emplacement, 1);
                while(c != '\0'){
                    cout << c ;
                    emplacement++;
                    c = (char) this->memory->readMemory(emplacement, 1);
                }
                break;
            case 0x102:
                n = this->memory->readMemory(emplacement, 4);
                cerr << "test unsuccessful : " <<  n << endl;
                this->run = false;
                break;
            case 0x101:
                cout << "test successful" << endl;
                this->run = false;
                this->command = "exit";
                break;
        }
        this->pc += 4;
    } catch (const length_error& le) {
        cout << le.what() << endl;
        this->continuous = false;
    }
}

