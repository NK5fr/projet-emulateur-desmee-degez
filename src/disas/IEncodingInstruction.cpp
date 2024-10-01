#include "../../header/disas/IEncodingInstruction.h"

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

  uint32_t funct3 = (this->word >> 12) & 0x7;
  int32_t imm = getImm();
  uint32_t funct7 = (this->word >> 25) & 0x7f;

  if(!this->name.compare("OP-IMM") && funct3 == 5 && funct7 == 32){
    return "srai";
  }else if(!this->name.compare("OP-IMM") && funct3 == 5 && funct7 == 0){
    return "srli";
  }else if(!this->name.compare("SYSTEM") && imm == 0){
    return "ecall";
  }else if(!this->name.compare("SYSTEM") && imm == 1){
    return "ebreak";
  }

  return instructions.at(this->name).at(funct3);
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

  cout << right << setw(8) << setfill('0') << offset << ": ";

  if(!this->name.compare("SYSTEM") || !this->name.compare("MISC-MEM")){
    cout << getName() << endl;
  }else{
    ostringstream oss;
    oss << getRd() << ", " << getRs1() << ", " << getImm();
    cout << left << setw(13) << setfill(' ') << getName() << left << setw(17) << setfill(' ') << oss.str() << "// 0x" << immHex.str() << endl;
  }
}