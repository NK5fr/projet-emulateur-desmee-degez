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
  uint32_t funct3 = (word >> 12) & 0x7;
  bitset<3> funct3Bin (funct3);
  string funct3Str = funct3Bin.to_string();
  this->name = instructions.at(name).at(funct3Str);

  this->rs1 = (word >> 15) & 0x1f;
  this->rs2 = (word >> 20) & 0x1f;
  
  int imm_11_5 = (word >> 25) & 0x7f;
  int imm_4_0 = (word >> 7) & 0x1f;
  int32_t imm32 = imm_11_5 << 5 | imm_4_0;
  if ((imm32 >> 11) & 1) {
    this->imm = imm32 | 0xfffff000;
  }else{
    this->imm = imm32;
  }
}

void SEncodingInstruction::printInstruction(){
  string rs1Str = "x" + to_string(this->rs1);
  string rs2Str = "x" + to_string(this->rs2);
  stringstream immHex;
  immHex << hex << this->imm;

  cout << this->name << " " << rs1Str << ", " << rs2Str << ", " << this->imm << "    // 0x" << immHex.str() << endl;
}