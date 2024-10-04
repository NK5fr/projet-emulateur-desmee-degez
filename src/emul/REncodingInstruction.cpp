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

  try{
    return instructions.at(this->name).at(funct3);
  }catch (const out_of_range& oor){
    stringstream ssword;
    ssword << hex << word;
    stringstream message;
    message << "instruction set error: invalid intruction: error funct3 : " << funct3 << ", funct7 : " << funct7 << " for opcode " << this->name << " for word " << setfill('0') << setw(8) << ssword.str();
    throw invalid_argument(message.str());
  }
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
  cout << getName() << " " << oss.str() << endl;
}

void REncodingInstruction::execute(int32_t* regs, uint32_t* pc, Memory* memory){
  string name = getName();
  uint32_t rd = getRd();
  uint32_t rs1 = getRs1();
  uint32_t rs2 = getRs2();

  if(!name.compare("add")){
    regs[rd] = regs[rs1] + regs[rs2];
  }else if(!name.compare("sub")){
    regs[rd] = regs[rs1] - regs[rs2];
  }else if(!name.compare("sll")){
    regs[rd] = (uint32_t) regs[rs1] << regs[rs2];
  }else if(!name.compare("slt")){
    regs[rd] = regs[rs1] < regs[rs2];
  }else if(!name.compare("sltu")){
    regs[rd] = (uint32_t) regs[rs1] < (uint32_t) regs[rs2];
  }else if(!name.compare("xor")){
    regs[rd] = regs[rs1] ^ regs[rs2];
  }else if(!name.compare("srl")){
    regs[rd] = (uint32_t) regs[rs1] >> regs[rs2];
  }else if(!name.compare("sra")){
    regs[rd] = regs[rs1] >> regs[rs2];
  }else if(!name.compare("or")){
    regs[rd] = regs[rs1] | regs[rs2];
  }else{
    regs[rd] = regs[rs1] & regs[rs2];
  }

  regs[0] = 0;
}