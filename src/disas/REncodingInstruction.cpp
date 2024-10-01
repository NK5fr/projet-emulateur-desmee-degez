#include "../../header/disas/REncodingInstruction.h"

map<string, map<uint32_t, string>> REncodingInstruction::instructions = {
    {"OP", {
        {1, "sll"},
        {2, "slt"},
        {3, "sltu"},
        {4, "xor"},
        {6, "or"},
        {7, "and"}}}
};

REncodingInstruction::REncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string REncodingInstruction::getName(){
  uint32_t funct3 = (this->word >> 12) & 0x7;
  uint32_t funct7 = (this->word >> 25) & 0x7f;

  if(funct3 == 5 && funct7 == 32){
    return "sra";
  }else if(funct3 == 5 && funct7 == 0){
    return "srl";
  }else if(funct3 == 0 && funct7 == 32){
    return "sub";
  }else if(funct3 == 0 && funct7 == 0){
    return "add";
  }

  return instructions.at(this->name).at(funct3);
}

string REncodingInstruction::getRd(){
  uint32_t rd = (this->word >> 7) & 0x1f;
  return "x" + to_string(rd);
    
}

string REncodingInstruction::getRs1(){
  uint32_t rs1 = (this->word >> 15) & 0x1f;
  return "x" + to_string(rs1);
}

string REncodingInstruction::getRs2(){
  uint32_t rs2 = (this->word >> 20) & 0x1f;
  return "x" + to_string(rs2);
}

void REncodingInstruction::printInstruction(string offset){
  cout << right << setw(8) << setfill('0') << offset << ": ";
  ostringstream oss;
  oss << getRd() << ", " << getRs1() << ", " << getRs2();
  cout << left << setw(13) << setfill(' ') << getName() << oss.str() << endl;
}