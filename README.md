# Groupe

>Romain DEGEZ
>Nathan DESMEE

# Livrable 1

Compiler le livrable 1 :

```bash
g++ -o bin/riscv-decode livrable/decode/header/* livrable/decode/src/*
```

Executer le livrable 1 :

```bash
bin/riscv-decode
```

# Livrable 2

Compiler le livrable 2 :

```bash
g++ -o bin/riscv-disas livrable/disas/header/* livrable/disas/src/*
```

Executer le livrable 2 :

```bash
bin/riscv-disas
```

# Livrable 3-4

Compiler le livrable 3-4 :

```bash
g++ -o bin/rivemul livrable/emul/header/* livrable/emul/src/*
```

Executer le livrable 3-4 :

```bash
bin/rivemul
```


# Docker 

Le livrable 3 et le livrable 4 sont tous deux compris dans le dossier livrable/emul.

Construire le container contenant l'exécutable du livrable :

```bash
docker build -t livrable1 -f Dockerfile.l1 .
```

Exécuter le container avec un fichier en paramètre :

```bash
docker run -it --rm -v /home/vagrant/workspace/res:/res livrable1 /res/binary_format.bin
```

# Extensions

