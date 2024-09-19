#include "../../header/disas/REncodingInstruction.h"

map<string, map<string, string>> REncodingInstruction::instructions = {
    {"OP", {
        {"0000", "add"},
        {"1000", "sub"},
        {"001", "sll"},
        {"010", "slt"},
        {"011", "sltu"},
        {"100", "xor"},
        {"0101", "srl"},
        {"1101", "sra"},
        {"110", "or"},
        {"111", "and"}}}
};

REncodingInstruction::REncodingInstruction(uint32_t word, string name) {
  uint32_t funct3 = (word >> 12) & 0x7;
  bitset<3> funct3Bin (funct3);
  string funct3Str = funct3Bin.to_string();
  this->name = instructions.at(name).at(funct3Str);

  this->rd = (word >> 7) & 0x1f;
  this->rs1 = (word >> 15) & 0x1f;
  this->rs2 = (word >> 20) & 0x1f;
}

void REncodingInstruction::printInstruction(){
  string rdStr = "x" + to_string(this->rd);
  string rs1Str = "x" + to_string(this->rs1);
  string rs2Str = "x" + to_string(this->rs2);

  cout << this->name << " " << rdStr << ", " << rs1Str << ", " << rs2Str << endl;
}