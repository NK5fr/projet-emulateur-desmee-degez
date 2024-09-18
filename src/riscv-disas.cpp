#include "../header/riscv-decode.h"

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
    {"1100011", {
        {"000", "BEQ"},
        {"001", "BNE"},
        {"100", "BLT"},
        {"101", "BGE"},
        {"110", "BLTU"},
        {"111", "BGEU"}}},
    {"1100111", {
        {"000", "JALR"}}},
    {"0000011", {
        {"000", "LB"},
        {"001", "LH"},
        {"010", "LW"},
        {"100", "LBU"},
        {"101", "LHU"},}},
    {"0001111", {
        {"000", "FENCE"}}},
    {"0010011", {
        {"000", "ADDI"},
        {"010", "SLTI"},
        {"011", "SLTIU"},
        {"100", "XORI"},
        {"110", "ORI"},
        {"111", "ANDI"},
        {"001", "SLLI"},
        {"0101", "SRLI"},
        {"1101", "SRAI"},}},
    {"1110011", {
        {"0000", "ECALL"},
        {"0001", "EBREAK"}}},
    {"1101111", {
        {"000", "JAL"}}},
    {"0110011", {
        {"0000", "ADD"},
        {"1000", "SUB"},
        {"001", "SLL"},
        {"010", "SLT"},
        {"011", "SLTU"},
        {"100", "XOR"},
        {"0101", "SRL"},
        {"1101", "SRA"},
        {"110", "OR"},
        {"111", "AND"}}},
    {"0100011", {
        {"000", "SB"},
        {"001", "SH"},
        {"010", "SW"}}},
    {"0010111", {
        {"000", "AUIPC"},}},
    {"0110111", {
        {"000", "LUI"}}}
};

int main(int argc, char *argv[]) {
    cout << getDataTypeI() << endl;
    if(argc != 2){
        printError();
        return 1;
    }

    cout << instructions.at("1100011").at("000") << endl;

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

    cout << "offset,valeur,opcode,encoding" << endl;

    for (int i = 0; i < words.size(); ++i) {

        stringstream offset;
        offset << hex << i * 4;

        uint32_t opc = getOpcode(words.at(i));

        bitset<7> opcBin (opc);
        string opcStr = opcBin.to_string();

        array<string, 2>& values = opcode.at(opcStr);

        cout << setfill('0') << setw(8) << offset.str() << ", "
             << hex << words.at(i) << ", "
             << values[0] << ", "
             << values[1] << ", "
             << endl;
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

vector<int> getDataTypeI(){
    vector<uint32_t> res;
    res.push_back(7);
    res.push_back(5);
    return res;
}

