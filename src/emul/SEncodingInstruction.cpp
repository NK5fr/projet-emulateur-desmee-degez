#include "../../header/emul/SEncodingInstruction.h"

map<string, map<uint32_t, string>> SEncodingInstruction::instructions = {
    {"BRANCH", {
        {0, "beq"},
        {1, "bne"},
        {4, "blt"},
        {5, "bge"},
        {6, "bltu"},
        {7, "bgeu"}}},
    {"STORE", {
        {0, "sb"},
        {1, "sh"},
        {2, "sw"}}}
};

SEncodingInstruction::SEncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string SEncodingInstruction::getName(){
  uint32_t funct3 = (this->word >> 12) & 0x7;

  try{
    return instructions.at(this->name).at(funct3);
  }catch (const out_of_range& oor){
    stringstream ssword;
    ssword << hex << word;
    stringstream message;
    message << "instruction set error: invalid intruction: error funct3 : " << funct3 << " for opcode " << this->name << " for word " << setfill('0') << setw(8) << ssword.str();
    throw invalid_argument(message.str());
  }
}

uint32_t SEncodingInstruction::getRs1(){
  return (this->word >> 15) & 0x1f;
}

uint32_t SEncodingInstruction::getRs2(){
  return (this->word >> 20) & 0x1f;
}

int32_t SEncodingInstruction::getImm(){
  if(!this->name.compare("BRANCH")){
    return getImmB();
  }

  int imm_11_5 = (this->word >> 25) & 0x7f;
  int imm_4_0 = (this->word >> 7) & 0x1f;
  int32_t imm32 = imm_11_5 << 5 | imm_4_0;
  if ((imm32 >> 11) & 1) {
    return imm32 | 0xfffff000;
  }
  return imm32;
}

int32_t SEncodingInstruction::getImmB(){
  int imm_10_5 = (this->word >> 25) & 0x7f;
  int imm_4_1 = (this->word >> 8) & 0x1f;
  int imm_11 = (this->word >> 7) & 0x1;
  int imm_12 = (this->word >> 31) & 0x1;
  int32_t imm32 = imm_12 << 12 | imm_11 << 11 | imm_10_5 << 5 | imm_4_1 << 1;
  if ((imm32 >> 11) & 1) {
    return imm32 | 0xfffff000;
  }
  return imm32;
}

void SEncodingInstruction::printInstruction(){
  int32_t imm = getImm();

  stringstream immHex;
  immHex << hex << imm;

  ostringstream oss;
  oss << "x" << getRs1() << ", x" << getRs2() << ", " << imm;
  cout << left << setw(13) << setfill(' ') << getName() << left << setw(17) << setfill(' ') << oss.str() << "// 0x" << immHex.str() << endl;
}

void SEncodingInstruction::execute(int32_t* regs, uint32_t* pc, Memory* memory){
  string name = getName();
  uint32_t rs1 = getRs1();
  uint32_t rs2 = getRs2();
  int32_t imm = getImm();

  if(!name.compare("beq")){
    if(regs[rs1] == regs[rs2]){
      *pc += imm - 4;
    }
  }else if(!name.compare("bne")){
    if(regs[rs1] != regs[rs2]){
      *pc += imm - 4;
    }
  }else if(!name.compare("blt")){
    if(regs[rs1] < regs[rs2]){
      *pc += imm - 4;
    }
  }else if(!name.compare("bge")){
    if(regs[rs1] > regs[rs2]){
      *pc += imm - 4;
    }
  }else if(!name.compare("bltu")){
    if( (uint32_t) regs[rs1] < (uint32_t) regs[rs2]){
      *pc += imm - 4;
    }
  }else if(!name.compare("bgeu")){
    if( (uint32_t) regs[rs1] >= (uint32_t) regs[rs2]){
      *pc += imm - 4;
    }
  }else if(!name.compare("sb")){
    int32_t start = regs[rs1] + imm;
    memory->writeMemory(start, 1, regs[rs2]);
  }else if(!name.compare("sh")){
    int32_t start = regs[rs1] + imm;
    memory->writeMemory(start, 2, regs[rs2]);
  }else{
    int32_t start = regs[rs1] + imm;
    memory->writeMemory(start, 4, regs[rs2]);
  }

  regs[0] = 0;
}