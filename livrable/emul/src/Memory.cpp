#include "../header/Memory.h"

Memory::Memory(uint32_t size){
    this->memory = new char[size * 1024];
    this->size = size;
}

void Memory::loadFile(string filename){
    ifstream file(filename, ios::in | ios::binary);

    if(!file.is_open()){
        cout << "Cannot open the file" << endl;
    }else{  

        uint32_t a;

        file.read((char*)&a, sizeof(a));
        int index = 0;
        while(!file.eof() && index < this->size * 1024){
            for(int i = 0; i<4;i++){
                this->memory[index+i] = (a >> (i*8)) & 0xFF;
            }

            file.read((char*)&a, sizeof(a));
            index+=sizeof(a);
        }

        file.close();

        if(!file.eof() && index >= this->size * 1024){
            cout << "Le fichier " << filename 
                 << " est trop grand pour être chargé dans une mémoire de " << this->size << "KB"
                 << " veuillez agrandir la mémoire pour charger complétement ce fichier" << endl;
        }
    }
}

uint32_t Memory::readMemory(int start, int size, bool isSigned){    
    if(start == 0x40000004 or start == 0x40000008){
        return 0;
    }

    if(start == 0x40000000){
        char c;
        cin >> c;
        uint32_t n;
        if(c == '\\') {
            cin >> c;
            if(c == 'n') n = (uint32_t) '\n' & 0xff;
            else n = (uint32_t) c & 0xff;
        } else {
            n = (uint32_t) c & 0xff;
        }
        cin.ignore(INT_MAX, '\n');
        return n;
    }

    if(start + size > this->size * 1024){
        stringstream message;
        message << "instruction set error: invalid intruction: imposible to read address : " << start + size << " for memory size : " << this->size * 1024 << " Bytes";
        throw length_error(message.str());
    }

    uint32_t res = 0;
    for(int i = 0; i < size; ++i){
        uint32_t n = (uint32_t) this->memory[start + i];
        n = n & 0xff;
        res = res | (n << 8 * i);
    }

    if(isSigned){
        if((res >> size*8-1) & 1){
            res = res | (0xffffffff << 8*size); 
        }
    }
    return res;
}

void Memory::writeMemory(int start, int size, int32_t word){
    if(start == 0x40000004){
        cout << (char) word << flush;
        return ;
    }
    if(start == 0x40000008){
        cerr << (char) word << flush;
        return ;
    }
    
    if(start + size > this->size * 1024){
        stringstream message;
        message << "instruction set error: invalid intruction: imposible to write on address : " << start + size << " for memory size : " << this->size * 1024 << " Bytes";
        throw length_error(message.str());
    }
    
    for(int i = 0; i < size; ++i){
        char c = (word >> 8 * i) & 0xff;
        this->memory[start + i] = c;
    }
}