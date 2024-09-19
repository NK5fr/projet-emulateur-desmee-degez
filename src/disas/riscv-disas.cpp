#include "../../header/disas/riscv-disas.h"
#include "../../header/disas/UEncodingInstruction.h"
#include "../../header/disas/IEncodingInstruction.h"
#include "../../header/disas/REncodingInstruction.h"
#include "../../header/disas/SEncodingInstruction.h"

map<string, array<string, 2>> opcode = {
    {"1100011", {"BRANCH", "S_B"}},
    {"1100111", {"JALR", "I"}},
    {"0000011", {"LOAD", "I"}},
    {"0001111", {"MISC-MEM", "I"}},
    {"0010011", {"OP-IMM", "I"}},
    {"1110011", {"SYSTEM", "I"}},
    {"1101111", {"JAL", "U_J"}},
    {"0110011", {"OP", "R"}},
    {"0100011", {"STORE", "S"}},
    {"0010111", {"AUIPC", "U"}},
    {"0110111", {"LUI", "U"}}
};

map<string, map<string, string>> instructions = {
    {"BRANCH", {
        {"000", "beq"},
        {"001", "bne"},
        {"100", "blt"},
        {"101", "bge"},
        {"110", "bltu"},
        {"111", "bgeu"}}},
    {"LOAD", {
        {"000", "lb"},
        {"001", "lh"},
        {"010", "lw"},
        {"100", "lbu"},
        {"101", "lhu"},}},
    {"MISC-MEM", {
        {"000", "fence"}}},
    {"OP-IMM", {
        {"000", "addi"},
        {"010", "slti"},
        {"011", "sltiu"},
        {"100", "xori"},
        {"110", "ori"},
        {"111", "andi"},
        {"001", "slli"},
        {"0101", "srli"},
        {"1101", "srai"},}},
    {"SYSTEM", {
        {"0000", "ecall"},
        {"0001", "ebreak"}}},
    {"OP", {
        {"0000", "add"},
        {"1000", "sub"},
        {"001", "sll"},
        {"010", "slt"},
        {"011", "sltu"},
        {"100", "xor"},
        {"0101", "srl"},
        {"1101", "sra"},
        {"110", "or"},
        {"111", "and"}}},
    {"STORE", {
        {"000", "sb"},
        {"001", "sh"},
        {"010", "sw"}}}
};

int main(int argc, char *argv[]) {

    //UEncoding ue("jarl");

    //cout << ue.getName() << endl;

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

void printIEncoding(uint32_t word, string name){
    
    uint32_t funct3 = (word >> 12) & 0x7;
    bitset<3> funct3Bin (funct3);
    string funct3Str = funct3Bin.to_string();
    string functName = instructions.at(name).at(funct3Str);

    uint32_t rd = (word >> 7) & 0x1f;
    string rdStr = "x" + to_string(rd);

    uint32_t rs1 = (word >> 15) & 0x1f;
    string rs1Str = "x" + to_string(rs1);

    uint32_t imm = (word >> 20) & 0xfff;

    stringstream immHex;
    immHex << hex << imm;

    cout << functName << " " << rdStr << ", " << rs1Str << ", " << imm << "    // 0x" << immHex.str() << endl;
}

void printUEncoding(uint32_t word, string name){

    string functName = "";
  
    for (char c : name) {
        functName += tolower(c); 
    }

    uint32_t rd = (word >> 7) & 0x1f;
    string rdStr = "x" + to_string(rd);

    uint32_t imm = (word >> 12) & 0xfffff;

    stringstream immHex;
    immHex << hex << imm;

    cout << functName << " " << rdStr << ", " << imm << "    // 0x" << immHex.str() << endl;
}

void printResult(vector<uint32_t> words)
{

    for (int i = 0; i < words.size(); ++i) {

        stringstream offset;
        offset << hex << i * 4;

        uint32_t opc = getOpcode(words.at(i));
        bitset<7> opcBin (opc);
        string opcStr = opcBin.to_string();

        try {
            array<string, 2>& values = opcode.at(opcStr);
            cout << setfill('0') << setw(8) << offset.str() << ": ";

            if(!values[1].compare("I")){
                IEncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction();
                //printIEncoding(words.at(i), values[0]);
            }else if(!values[1].compare("U")){
                UEncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction();
                //printUEncoding(words.at(i), values[0]);
            }else if(!values[1].compare("R")){
                REncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction();
            }else if(!values[1].compare("S")){
                SEncodingInstruction instruction(words.at(i), values[0]);
                instruction.printInstruction();
            }else{
                cout << endl;
            }
        } catch (const out_of_range& oor) {
            stringstream word;
            word << hex << words.at(i);
            cout << "Instruction 0x" << setfill('0') << setw(8) << word.str()
                 << " is not supported at offset " << setfill('0') << setw(8) << offset.str()
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

