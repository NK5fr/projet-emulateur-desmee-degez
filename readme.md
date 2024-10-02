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

void loadBinaryFile(string filePath, char* memory){
    ifstream file(filePath, ios::in | ios::binary);

    if(!file.is_open()){
        cout << "Cannot open the file" << endl;
    }else{  

        char* a;

        file.read(a, 1);
        int index = 0;
        while(!file.eof()){
            //cout << hex << a << endl;
            memory[index] = *a;

            file.read(a, 1);
            index+=sizeof(a);
        }

        file.close();
    }
}

void printMemory(char* memory){
    for(int i = 0; i < sizeof(memory); ++i){
        cout << hex << memory[i] << endl;
    }
}