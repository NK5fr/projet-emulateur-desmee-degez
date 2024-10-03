addi x1, x0, 3
slti x2, x1, 4
ebreak
lb x15, 10(x2)
lh x16, 10(x2) 
lw x17, 10(x2) 
lhu x16, 10(x2) 
lbu x15, 10(x2)
auipc x10, 3
lui x9, -15
addi x5, x0, 6
slti x3, x1, 3
sltiu x4, x3, -1
