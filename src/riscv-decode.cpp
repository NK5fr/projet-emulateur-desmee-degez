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

    cout << "offset,valeur,opcode,encoding" << endl;

    for (int i = 0; i < words.size(); ++i) {

        stringstream offset;
        offset << hex << i * 4;

        uint32_t opc = getOpcode(words.at(i));

        bitset<7> opcBin (opc);
        string opcStr = opcBin.to_string();

        stringstream word;
        word << hex << words.at(i);

        array<string, 2>& values = opcode.at(opcStr);

        cout << setfill('0') << setw(8) << offset.str() << ", "
             << setfill('0') << setw(8) << word.str() << ", "
             << values[0] << ", "
             << values[1] << ", "
             << endl;
    }
}

void printHelp(){
    cout << "Un décodeur d'instruction RISC-V RV32I" << endl;
    cout << "Utilisation: riscv-decode [OPTIONS] FICHIER_BIN" << endl;
    cout << "Arguments:" << endl;
    cout << "   FICHIER_BIN Un fichier au format binaire contenant les instructions à décoder" << endl;
    cout << "Options:" << endl;
    cout << "   -h Affiche ce message d'aide" << endl;
}

void printError(){
    cout << "Utilisation: riscv-decode [OPTIONS] FICHIER_BIN" << endl;
    cout << "Essaie 'riscv-decode -h' pour plus d'information." << endl;
}


