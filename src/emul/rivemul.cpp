#include "../../header/emul/rivemul.h"

int main(int argc, char *argv[]) {
    if(argc != 2){
        printHelp();
        return 1;
    }
    string argument(argv[1]);
    
    if(!argument.compare("-h")){
        printHelp();
        return 0;
    }
    return 0; 
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