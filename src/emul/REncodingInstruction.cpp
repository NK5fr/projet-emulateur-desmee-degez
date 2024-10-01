#include "../../header/emul/REncodingInstruction.h"

map<string, map<uint32_t, string>> REncodingInstruction::instructions = {
    {"OP", {
        {1, "sll"},
        {2, "slt"},
        {3, "sltu"},
        {4, "xor"},
        {6, "or"},
        {7, "and"}}}
};

REncodingInstruction::REncodingInstruction(uint32_t word, string name) : EncodingInstruction() {
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

uint32_t REncodingInstruction::getRd(){
  return (this->word >> 7) & 0x1f;
    
}

uint32_t REncodingInstruction::getRs1(){
  return (this->word >> 15) & 0x1f;
}

uint32_t REncodingInstruction::getRs2(){
  return (this->word >> 20) & 0x1f;
}

void REncodingInstruction::printInstruction(){
  ostringstream oss;
  oss << "x" << getRd() << ", x" << getRs1() << ", x" << getRs2();
  cout << left << setw(13) << setfill(' ') << getName() << oss.str() << endl;
}

void REncodingInstruction::execute(){
  string name = getName();

  if(!name.compare("add")){
      cout << "add" << endl;
  }else if(!name.compare("sub")){
      cout << "sub" << endl;
  }else if(!name.compare("sll")){
      cout << "sll" << endl;
  }else if(!name.compare("slt")){
      cout << "slt" << endl;
  }else if(!name.compare("sltu")){
      cout << "sltu" << endl;
  }else if(!name.compare("xor")){
      cout << "xor" << endl;
  }else if(!name.compare("srl")){
      cout << "srl" << endl;
  }else if(!name.compare("sra")){
      cout << "sra" << endl;
  }else if(!name.compare("or")){
      cout << "or" << endl;
  }else{
      cout << "and" << endl;
  }
}