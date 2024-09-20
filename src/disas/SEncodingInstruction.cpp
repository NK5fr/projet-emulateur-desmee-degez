#include "../../header/disas/SEncodingInstruction.h"

map<string, map<string, string>> SEncodingInstruction::instructions = {
    {"BRANCH", {
        {"000", "beq"},
        {"001", "bne"},
        {"100", "blt"},
        {"101", "bge"},
        {"110", "bltu"},
        {"111", "bgeu"}}},
    {"STORE", {
        {"000", "sb"},
        {"001", "sh"},
        {"010", "sw"}}}
};

SEncodingInstruction::SEncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string SEncodingInstruction::getName(){
  uint32_t funct3 = (this->word >> 12) & 0x7;
  bitset<3> funct3Bin (funct3);
  string funct3Str = funct3Bin.to_string();
  return instructions.at(this->name).at(funct3Str);
}

string SEncodingInstruction::getRs1(){
  uint32_t rs1 = (this->word >> 15) & 0x1f;
  return "x" + to_string(rs1);
}

string SEncodingInstruction::getRs2(){
  uint32_t rs2 = (this->word >> 20) & 0x1f;
  return "x" + to_string(rs2);
}

int32_t SEncodingInstruction::getImm(){
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

void SEncodingInstruction::printInstruction(string offset){
  int32_t imm;

  if(!this->name.compare("BRANCH")){
    imm = getImmB();
  }else{
    imm = getImm();
  }

  stringstream immHex;
  immHex << hex << imm;

  cout << right << setw(8) << setfill('0') << offset << ": ";
  ostringstream oss;
  oss << getRs1() << ", " << getRs2() << ", " << imm;
  cout << left << setw(13) << setfill(' ') << getName() << left << setw(17) << setfill(' ') << oss.str() << "// 0x" << immHex.str() << endl;
}