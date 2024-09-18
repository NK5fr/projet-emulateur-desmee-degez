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

    if(argc < 2){
        return 1;
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
        string opcStr = nat.to_string();

        array<string, 2>& values = opcode.at(opcStr);

        cout << setfill('0') << setw(8) << offset.str() << ", "
             << hex << words.at(i) << ", "
             << values[0] << ", "
             << values[1] << ", "
             << endl;
    }
}


