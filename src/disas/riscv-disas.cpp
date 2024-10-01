#include "../../header/disas/riscv-disas.h"
#include "../../header/disas/UEncodingInstruction.h"
#include "../../header/disas/IEncodingInstruction.h"
#include "../../header/disas/REncodingInstruction.h"
#include "../../header/disas/SEncodingInstruction.h"

map<uint32_t, array<string, 2>> opcode = {
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

int main(int argc, char *argv[]) {

    if(argc != 2){
        printError();
        return 1;
    }

    string argument(argv[1]);
    
    if(!argument.compare("-h")){
        printHelp();
        return 0;
    }
    
    vector<uint32_t> words = readFile(argv[1]);
    printResult(words);

    return 0; 
}

vector<uint32_t> readFile(string filePath){
    
    vector<uint32_t> res;
    
    ifstream file(filePath, ios::in | ios::binary);

    if(!file.is_open()){
        cout << "Cannot open the file" << endl;
    }else{  

        uint32_t a;

        file.read((char*)&a, sizeof(a));

        while(!file.eof()){
            res.push_back(a);
            file.read((char*)&a, sizeof(a));
        }

        file.close();
    }

    return res;
}

uint32_t getOpcode(uint32_t word){
    uint32_t opcode = word & 0x7f;
    return opcode;
}

void printResult(vector<uint32_t> words)
{

    for (int i = 0; i < words.size(); ++i) {

        stringstream offset;
        offset << hex << i * 4;

        uint32_t opc = getOpcode(words.at(i));

        try {
            array<string, 2>& values = opcode.at(opc);

            if(!values[1].compare("I")){
                IEncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction(offset.str());
            }else if(!values[1].compare("U") || !values[1].compare("U_J")){
                UEncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction(offset.str());
            }else if(!values[1].compare("R")){
                REncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction(offset.str());
            }else if(!values[1].compare("S") || !values[1].compare("S_B")){
                SEncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction(offset.str());
            }else{
                cout << endl;
            }
            
        } catch (const out_of_range& oor) {
            stringstream word;
            word << hex << words.at(i);
            cout << "instruction set error: invalid opcode: error value: 0x" << hex << opc
                 << " at offset " << setfill('0') << setw(8) << offset.str()
                 << " for word " << setfill('0') << setw(8) << word.str()
                 << endl;
        }
    }
}

void printHelp(){
    cout << "Un désassembleur RISC-V pour le jeu d'instruction RV32I" << endl;
    cout << "\nUtilisation: riscv-disas [OPTIONS] FICHIER_BIN" << endl;
    cout << "\nArguments:" << endl;
    cout << "   FICHIER_BIN         Un fichier contenant les instructions à désassembler" << endl;
    cout << "\nOptions:" << endl;
    cout << "   -h                  Affiche ce message d'aide" << endl;
}

void printError(){
    cout << "Utilisation: riscv-decode [OPTIONS] FICHIER_BIN" << endl;
    cout << "Essaie 'riscv-decode -h' pour plus d'information." << endl;
}

