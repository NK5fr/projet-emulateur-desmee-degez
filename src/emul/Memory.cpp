#include "../../header/emul/Memory.h"

Memory::Memory(uint32_t size){
    this->memory = new char[size * 1024];
    this->size = size;
}

void Memory::loadFile(string filename){
    ifstream file(filename, ios::in | ios::binary);

    if(!file.is_open()){
        cout << "Cannot open the file" << endl;
    }else{  

        char* a;

        file.read(a, 1);
        int index = 0;
        while(!file.eof() && index < this->size * 1024){

            this->memory[index] = *a;
            file.read(a, 1);
            index++;
        }

        file.close();

        if(!file.eof() && index >= this->size * 1024){
            cout << "Le fichier " << filename 
                 << " est trop grand pour être chargé dans une mémoire de " << this->size << "KB"
                 << " veuillez agrandir la mémoire pour charger complétement ce fichier" << endl;
        }

        cout << hex << readMemory(0) << endl;
    }
}

uint32_t Memory::readMemory(int start){
    uint32_t* instruction_ptr = (uint32_t *) this->memory[start];
    return *instruction_ptr;
}