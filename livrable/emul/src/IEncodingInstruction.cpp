#include "../header/IEncodingInstruction.h"

map<string, map<uint32_t, string>> IEncodingInstruction::instructions = {
    {"LOAD", {
        {0, "lb"},
        {1, "lh"},
        {2, "lw"},
        {4, "lbu"},
        {5, "lhu"},}},
    {"MISC-MEM", {
        {0, "fence"}}},
    {"OP-IMM", {
        {0, "addi"},
        {2, "slti"},
        {3, "sltiu"},
        {4, "xori"},
        {6, "ori"},
        {7, "andi"},
        {1, "slli"},}}
};

IEncodingInstruction::IEncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string IEncodingInstruction::getName(){
  if(!this->name.compare("JALR")){
    return "jalr";
  }

  uint32_t funct3 = getFunct3();
  int32_t imm = getImm();
  uint32_t funct7 = getFunct7();

  if(!this->name.compare("OP-IMM") && funct3 == 5 && funct7 == 32){
    return "srai";
  }else if(!this->name.compare("OP-IMM") && funct3 == 5 && funct7 == 0){
    return "srli";
  }else if(!this->name.compare("SYSTEM") && imm == 0){
    return "ecall";
  }else if(!this->name.compare("SYSTEM") && imm == 1){
    return "ebreak";
  }

  try{
    return instructions.at(this->name).at(funct3);
  }catch (const out_of_range& oor){
    stringstream ssword;
    ssword << hex << word;
    stringstream message;
    message << "instruction set error: invalid intruction: error funct3 : " << funct3 << ", funct7 : " << funct7 << ", imm : " << imm << " for opcode " << this->name << " for word " << setfill('0') << setw(8) << ssword.str();
    throw invalid_argument(message.str());
  }
}

uint32_t IEncodingInstruction::getFunct3(){
  return (this->word >> 12) & 0x7;
}

uint32_t IEncodingInstruction::getFunct7(){
  return (this->word >> 25) & 0x7f;
}

uint32_t IEncodingInstruction::getRd(){
  return (this->word >> 7) & 0x1f;
}

uint32_t IEncodingInstruction::getRs1(){
  return (this->word >> 15) & 0x1f;
}

int32_t IEncodingInstruction::getImm(){
  int32_t imm32 = (this->word >> 20) & 0xfff;
  if ((imm32 >> 11) & 1) {
    return imm32 | 0xfffff000;
  }else{
    return imm32;
  }
}

void IEncodingInstruction::printInstruction(){
  stringstream immHex;
  immHex << hex << getImm();

  if(!this->name.compare("SYSTEM") || !this->name.compare("MISC-MEM")){
    cout << getName() << endl;
  }else{
    ostringstream oss;
    oss << "x" << getRd() << ", x" << getRs1() << ", " << getImm();
    cout << left << getName() << " " << oss.str() << " // 0x" << immHex.str() << endl;
  }
}

void IEncodingInstruction::execute(int32_t* regs, uint32_t* pc, Memory* memory){
  string name = getName();
  uint32_t rd = getRd();
  uint32_t rs1 = getRs1();
  int32_t imm = getImm();

  if(!name.compare("lb")){
    int32_t start = regs[rs1] + imm;
    regs[rd] = memory->readMemory(start, 1, true);
  }else if(!name.compare("lh")){
    int32_t start = regs[rs1] + imm;
    regs[rd] = memory->readMemory(start, 2, true);
  }else if(!name.compare("lw")){
    int32_t start = regs[rs1] + imm;
    regs[rd] = memory->readMemory(start, 4);
  }else if(!name.compare("lbu")){
    int32_t start = regs[rs1] + imm;
    regs[rd] = memory->readMemory(start, 1);
  }else if(!name.compare("lhu")){
    int32_t start = regs[rs1] + imm;
    regs[rd] = memory->readMemory(start, 2);
  }else if(!name.compare("addi")){
    regs[rd] = regs[rs1] + imm;
  }else if(!name.compare("slti")){
    regs[rd] = regs[rs1] < imm;  
  }else if(!name.compare("sltiu")){
    regs[rd] = (uint32_t) regs[rs1] < (uint32_t) imm;  
  }else if(!name.compare("xori")){
    regs[rd] = regs[rs1] ^ imm;
  }else if(!name.compare("ori")){
    regs[rd] = regs[rs1] | imm;
  }else if(!name.compare("andi")){
    regs[rd] = regs[rs1] & imm;
  }else if(!name.compare("slli")){
    regs[rd] = (uint32_t) regs[rs1] << imm;
  }else if(!name.compare("srli")){
    regs[rd] = (uint32_t) regs[rs1] >> imm;
  }else if(!name.compare("srai")){
    regs[rd] = regs[rs1] >> imm;
  }else if(!name.compare("jalr")){
    int tmp = (regs[rs1] + imm) & 0xFFFFFFFE;
    regs[rd] = *pc + 4;
    *pc = tmp;
    *pc -= 4;
  }else if(!name.compare("ebreak")){
    throw EbreakException("Passage au mode StepByStep");
  }

  regs[0] = 0;
}