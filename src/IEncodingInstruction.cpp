#include "../header/IEncodingInstruction.h"

map<string, map<string, string>> IEncodingInstruction::instructions = {
    {"LOAD", {
        {"000", "lb"},
        {"001", "lh"},
        {"010", "lw"},
        {"100", "lbu"},
        {"101", "lhu"},}},
    {"MISC-MEM", {
        {"000", "fence"}}},
    {"OP-IMM", {
        {"000", "addi"},
        {"010", "slti"},
        {"011", "sltiu"},
        {"100", "xori"},
        {"110", "ori"},
        {"111", "andi"},
        {"001", "slli"},
        {"0101", "srli"},
        {"1101", "srai"},}},
    {"SYSTEM", {
        {"0000", "ecall"},
        {"0001", "ebreak"}}}
};

IEncodingInstruction::IEncodingInstruction(uint32_t word, string name) {
  uint32_t funct3 = (word >> 12) & 0x7;
  bitset<3> funct3Bin (funct3);
  string funct3Str = funct3Bin.to_string();
  this->name = instructions.at(name).at(funct3Str);

  this->rd = (word >> 7) & 0x1f;
  this->rs1 = (word >> 15) & 0x1f;
  
  int32_t imm32 = (word >> 20) & 0xfff;
  if ((imm32 >> 11) & 1) {
    this->imm = imm32 | 0xfffff000;
  }else{
    this->imm = imm32;
  }
}

string IEncodingInstruction::getName() {
  return this->name;
}

void IEncodingInstruction::printInstruction(){
  string rdStr = "x" + to_string(this->rd);
  string rs1Str = "x" + to_string(this->rs1);
  stringstream immHex;
  immHex << hex << this->imm;

  cout << this->name << " " << rdStr << ", " << rs1Str << ", " << this->imm << "    // 0x" << immHex.str() << endl;
}