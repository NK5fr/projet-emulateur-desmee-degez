# SAE Emulateur BUT3

## Auteurs 

- Romain DEGEZ
- Nathan DESMEE

## Livrable 1

### Compilation

```bash
g++ -o bin/riscv-decode livrable/decode/header/* livrable/decode/src/*
```

### Execution

```bash
bin/riscv-decode
```

### Docker

```bash
docker build -t livrable1 -f Dockerfile.l1 .
```

```bash
docker run -it --rm -v /home/vagrant/workspace/res:/res livrable1
```

## Livrable 2

### Compilation

```bash
g++ -o bin/riscv-disas livrable/disas/header/* livrable/disas/src/*
```

### Execution

```bash
bin/riscv-disas
```

### Docker

```bash
docker build -t livrable2 -f Dockerfile.l2 .
```

```bash
docker run -it --rm -v /home/vagrant/workspace/res:/res livrable2
```

## Livrables 3 et 4

### Compilation

```bash
g++ -o bin/rivemul livrable/emul/header/* livrable/emul/src/*
```

### Execution

```bash
bin/rivemul
```

### Docker

```bash
docker build -t livrable3-4 -f Dockerfile.l3-4 .
```

```bash
docker run -it --rm -v /home/vagrant/workspace/res:/res livrable3-4
```

## Bonus

### Extension M

 Extension M fonctionnelle avec les instructions :
- mul
- mulh
- mulhu
- mulhsu
- div
- divu
- rem
- remu