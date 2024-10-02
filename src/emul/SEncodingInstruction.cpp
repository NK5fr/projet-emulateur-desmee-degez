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
  return instructions.at(this->name).at(funct3);
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

void SEncodingInstruction::execute(){
  string name = getName();

  if(!name.compare("beq")){
      cout << "beq" << endl;
  }else if(!name.compare("bne")){
      cout << "bne" << endl;
  }else if(!name.compare("blt")){
      cout << "blt" << endl;
  }else if(!name.compare("bge")){
      cout << "bge" << endl;
  }else if(!name.compare("bltu")){
      cout << "bltu" << endl;
  }else if(!name.compare("bgeu")){
      cout << "bgeu" << endl;
  }else if(!name.compare("sb")){
      cout << "sb" << endl;
  }else if(!name.compare("sh")){
      cout << "sh" << endl;
  }else{
      cout << "sw" << endl;
  }
}