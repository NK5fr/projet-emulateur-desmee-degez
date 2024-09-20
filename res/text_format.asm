addi x1, x0, -100
addi x2, x0, 200
addi x5, x0, 1
addi x6, x0, 1
xor  x4,x5,x6
lui  x11, -21
sw x2,-100(x7)
addi x10, x0, 4
slli x0, x0, 31

# Branch instructions
beq x1, x2, label_beq   # BEQ: Branch if equal
bne x1, x2, label_bne   # BNE: Branch if not equal
blt x1, x2, label_blt   # BLT: Branch if less than
bge x1, x2, label_bge   # BGE: Branch if greater than or equal
bltu x1, x2, label_bltu # BLTU: Branch if less than unsigned
bgeu x1, x2, label_bgeu # BGEU: Branch if greater than or equal unsigned

# Load instructions
lb x3, 0(x1)      # LB: Load byte
lh x3, 0(x1)      # LH: Load halfword
lw x3, 0(x1)      # LW: Load word
lbu x3, 0(x1)     # LBU: Load byte unsigned
lhu x3, 0(x1)     # LHU: Load halfword unsigned

# Miscellaneous memory instructions
fence 1,1            # FENCE: Memory barrier

# Immediate arithmetic operations
addi x3, x1, 1     # ADDI: Add immediate
slti x3, x1, 1     # SLTI: Set less than immediate
sltiu x3, x1, 1    # SLTIU: Set less than immediate unsigned
xori x3, x1, 1     # XORI: XOR immediate
ori x3, x1, 1      # ORI: OR immediate
andi x3, x1, 1     # ANDI: AND immediate
slli x3, x1, 1     # SLLI: Shift left logical immediate
srli x3, x1, 1     # SRLI: Shift right logical immediate
srai x3, x1, 1     # SRAI: Shift right arithmetic immediate

# Jump and link register
jalr x3, 0(x1)    # JALR: Jump and link register

# System instructions
ecall            # ECALL: Environment call
ebreak           # EBREAK: Environment break

# Jump and link
jal x3, label_jal # JAL: Jump and link

# Register-register arithmetic operations
add x3, x1, x2    # ADD: Add
sub x3, x1, x2    # SUB: Subtract
sll x3, x1, x2    # SLL: Shift left logical
slt x3, x1, x2    # SLT: Set less than
sltu x3, x1, x2   # SLTU: Set less than unsigned
xor x3, x1, x2    # XOR: Exclusive OR
srl x3, x1, x2    # SRL: Shift right logical
sra x3, x1, x2    # SRA: Shift right arithmetic
or x3, x1, x2     # OR: Logical OR
and x3, x1, x2    # AND: Logical AND

# Store instructions
sb x3, 0(x1)      # SB: Store byte
sh x3, 0(x1)      # SH: Store halfword
sw x3, 0(x1)      # SW: Store word

# Upper immediate instructions
auipc x3, 1       # AUIPC: Add upper immediate to PC
lui x3, 1         # LUI: Load upper immediate

# Labels for branch and jump instructions
label_beq:
  nop
label_bne:
  nop
label_blt:
  nop
label_bge:
  nop
label_bltu:
  nop
label_bgeu:
  nop
label_jal:
  nop
