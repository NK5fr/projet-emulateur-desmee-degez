#include "../../header/disas/REncodingInstruction.h"

map<string, map<string, string>> REncodingInstruction::instructions = {
    {"OP", {
        {"001", "sll"},
        {"010", "slt"},
        {"011", "sltu"},
        {"100", "xor"},
        {"110", "or"},
        {"111", "and"}}}
};

REncodingInstruction::REncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string REncodingInstruction::getName(){
  uint32_t funct3 = (this->word >> 12) & 0x7;
  bitset<3> funct3Bin (funct3);
  string funct3Str = funct3Bin.to_string();

  if(!funct3Str.compare("101") && !getFunct7().compare("0100000")){
    return "sub";
  }else if(!funct3Str.compare("101") && !getFunct7().compare("0000000")){
    return "add";
  }else if(!funct3Str.compare("000") && !getFunct7().compare("0100000")){
    return "sra";
  }else if(!funct3Str.compare("000") && !getFunct7().compare("0000000")){
    return "srl";
  }

  return instructions.at(this->name).at(funct3Str);
}

string REncodingInstruction::getFunct7(){
  uint32_t funct7 = (this->word >> 25) & 0x7f;
  bitset<7> funct7Bin (funct7);
  return funct7Bin.to_string();
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
  cout << setfill('0') << setw(8) << offset << ": ";
  cout << getName() << " " << getRd() << ", " << getRs1() << ", " << getRs2() << endl;
}