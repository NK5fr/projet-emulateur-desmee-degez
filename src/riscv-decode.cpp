#include "../header/riscv-decode.h"

map<string, array<string, 2>> opcode;

int main(int argc, char *argv[]) { 
    initOpcode();

    const array<string, 2>& values = opcode.at("1100011");
    cout << values[0] << ", " << values[1] << endl;
    
    lireFichier("res/test.txt");
    cout << getOpcode((uint32_t)227)  << endl;
    return 0; 
}

void initOpcode(){
    opcode.insert({"1100011", {"BRANCH", "S_B"}});
    opcode.insert({"1100111", {"JALR", "I"}});
    opcode.insert({"0000011", {"LOAD", "I"}});
    opcode.insert({"0001111", {"MISC-MEM", "I"}});
    opcode.insert({"0010011", {"OP-IMM", "I"}});
    opcode.insert({"1110011", {"SYSTEM", "I"}});
    opcode.insert({"1101111", {"JAL", "U_J"}});
    opcode.insert({"0110011", {"OP", "R"}});
    opcode.insert({"0100011", {"STORE", "S"}});
    opcode.insert({"0010111", {"AUIPC", "U"}});
    opcode.insert({"0110111", {"LUI", "U"}});
}

void lireFichier(string filePath){
    ifstream fichier(filePath, ios::binary);  

    if(!fichier){
        cout << "Cannot open the file" << endl;
    }
    char contenu[4];  
    fichier.read(contenu, 1);
    cout << contenu << endl;  

    fichier.close();
}

int getOpcode(uint32_t word){
    int opcode = word & 0x7f;
    return opcode;
}
