#include "../../header/disas/IEncodingInstruction.h"

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
        {"001", "slli"},}}
};

IEncodingInstruction::IEncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string IEncodingInstruction::getName(){
  if(!this->name.compare("JALR")){
    return "jalr";
  }

  uint32_t funct3 = (this->word >> 12) & 0x7;
  bitset<3> funct3Bin (funct3);
  string funct3Str = funct3Bin.to_string();

  bitset<12> ImmBin (getImm());
  string ImmStr = ImmBin.to_string();



  if(!this->name.compare("OP-IMM") && !funct3Str.compare("101") && !getFunct7().compare("0100000")){
    return "srai";
  }else if(!this->name.compare("OP-IMM") && !funct3Str.compare("101") && !getFunct7().compare("0000000")){
    return "srli";
  }else if(!this->name.compare("SYSTEM") && !ImmStr.compare("000000000000")){
    return "ecall";
  }else if(!this->name.compare("SYSTEM") && !ImmStr.compare("000000000001")){
    return "ebreak";
  }

  return instructions.at(this->name).at(funct3Str);
}

string IEncodingInstruction::getFunct7(){
  uint32_t funct7 = (this->word >> 25) & 0x7f;
  bitset<7> funct7Bin (funct7);
  return funct7Bin.to_string();
}

string IEncodingInstruction::getRd(){
  uint32_t rd = (this->word >> 7) & 0x1f;
  return "x" + to_string(rd);
}

string IEncodingInstruction::getRs1(){
  uint32_t rs1 = (this->word >> 15) & 0x1f;
  return "x" + to_string(rs1);
}

int32_t IEncodingInstruction::getImm(){
  int32_t imm32 = (this->word >> 20) & 0xfff;
  if ((imm32 >> 11) & 1) {
    return imm32 | 0xfffff000;
  }else{
    return imm32;
  }
}

void IEncodingInstruction::printInstruction(string offset){
  stringstream immHex;
  immHex << hex << getImm();

  cout << setfill('0') << setw(8) << offset << ": ";

  if(!this->name.compare("SYSTEM")){
    cout << getName() << endl;
  }else{
    cout << getName() << " " << getRd() << ", " << getRs1() << ", " << getImm() << "    // 0x" << immHex.str() << endl;
  }
}