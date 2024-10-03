# Livrable 1

Compiler le livrable 1 :

```bash
g++ -o bin/riscv-decode header/decode/* src/decode/*
```

Executer le livrable 1 :

```bash
bin/riscv-decode
```

# Livrable 2

Compiler le livrable 2 :

```bash
g++ -o bin/riscv-disas header/disas/* src/disas/*
```

Executer le livrable 2 :

```bash
bin/riscv-disas
```

# Livrable 3

Compiler le livrable 3 :

```bash
g++ -o bin/rivemul header/emul/* src/emul/*
```

Executer le livrable 3 :

```bash
bin/rivemul
```

void Processor::runStepByStep(){
    string command;
    bool continuous = false;
    string defaultCommand = "step"; 

    while(command.compare("exit")){
        printRegisters();
        cout << "pc : " << this->pc << " : ";

        uint32_t word = this->memory->readMemory(this->pc, 4);
        uint32_t opc = getOpcode(word);

        Instruction* instruction = nullptr;

        try {
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

            if (instruction) {
                instruction->printInstruction();
            }
        } catch (const out_of_range& oor) {
            stringstream ssword;
            ssword << hex << word;
            cout << "instruction set error: invalid opcode: error value: 0x" << hex << opc
                << " for word " << setfill('0') << setw(8) << ssword.str()
                << endl;
        }catch (const invalid_argument& ia) {
            cout << ia.what() << endl;
            instruction = nullptr;
        }

        try {
            cout << "rivemul (default=" << defaultCommand << "): ";
            getline(cin, command);
            if(!command.compare("")){
                command = defaultCommand;
            }else{
                defaultCommand = command;
            }
            if (!command.compare("step")) {
                if (instruction) {
                    instruction->execute(this->regs, &(this->pc), this->memory);
                }
                this->pc += 4;
            } else if (!command.rfind("x/", 0)) { 
                vector<string> splitedString = split(command, ' ');
                int count = stoi(split(splitedString.at(0), '/').at(1));
                int adress = stoi(splitedString.at(1));
                uint32_t res = this->memory->readMemory(adress, count);
                cout << res << endl;
            } else if (!command.compare("reset")) {
                this->pc = this->reset;
            } else if (!command.compare("continue")) {
                if (instruction) {
                    instruction->execute(this->regs, &(this->pc), this->memory);
                }
                this->pc += 4;
                command = "exit";
                continuous = true;
            }
        } catch (const length_error& le) {
            cout << le.what() << endl;
        } catch (const EbreakException& eb){
            this->pc += 4;
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

            Instruction* instruction = nullptr;

            if(!values[1].compare("I")){
                instruction = new IEncodingInstruction(word, values[0]);
            }else if(!values[1].compare("U") || !values[1].compare("U_J")){
                instruction = new UEncodingInstruction(word, values[0]);
            }else if(!values[1].compare("R")){
                instruction = new REncodingInstruction(word, values[0]);
            }else if(!values[1].compare("S") || !values[1].compare("S_B")){
                instruction = new SEncodingInstruction(word, values[0]);
            }

            if (instruction) {
                instruction->execute(this->regs, &(this->pc), this->memory);
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
        } catch (const EbreakException& eb){
            this->pc += 4;
            run = false;
        }
    }

    runStepByStep();
}