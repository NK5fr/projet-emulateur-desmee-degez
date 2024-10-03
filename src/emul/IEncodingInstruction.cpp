#include "../../header/emul/IEncodingInstruction.h"

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

  try{
    return instructions.at(this->name).at(funct3);
  }catch (const out_of_range& oor){
    stringstream ssword;
    ssword << hex << word;
    stringstream message;
    message << "instruction set error: invalid intruction: error funct3 : " << funct3 << ", funct7 : " << funct7 << ", imm : " << imm << " for opcode " << this->name << " for word " << setfill('0') << setw(8) << ssword.str();
    throw invalid_argument(message.str());
  }
}

uint32_t IEncodingInstruction::getRd(){
  return (this->word >> 7) & 0x1f;
}

uint32_t IEncodingInstruction::getRs1(){
  return (this->word >> 15) & 0x1f;
}

int32_t IEncodingInstruction::getImm(){
  int32_t imm32 = (this->word >> 20) & 0xfff;
  if ((imm32 >> 11) & 1) {
    return imm32 | 0xfffff000;
  }else{
    return imm32;
  }
}

void IEncodingInstruction::printInstruction(){
  stringstream immHex;
  immHex << hex << getImm();

  if(!this->name.compare("SYSTEM") || !this->name.compare("MISC-MEM")){
    cout << getName() << endl;
  }else{
    ostringstream oss;
    oss << "x" << getRd() << ", x" << getRs1() << ", " << getImm();
    cout << left << setw(13) << setfill(' ') << getName() << left << setw(17) << setfill(' ') << oss.str() << "// 0x" << immHex.str() << endl;
  }
}

void IEncodingInstruction::execute(int32_t* regs, uint32_t* pc, Memory* memory){
  string name = getName();

  if(!name.compare("lb")){
      cout << "lb" << endl;
  }else if(!name.compare("lh")){
      cout << "lh" << endl;
  }else if(!name.compare("lw")){
      cout << "lw" << endl;
  }else if(!name.compare("lbu")){
      cout << "lbu" << endl;
  }else if(!name.compare("lhu")){
      cout << "lhu" << endl;
  }else if(!name.compare("addi")){
    regs[getRd()] = regs[getRs1()] + getImm();
  }else if(!name.compare("slti")){
    regs[getRd()] = regs[getRs1()] < getImm();  
  }else if(!name.compare("sltiu")){
    regs[getRd()] = (uint32_t) regs[getRs1()] < (uint32_t) getImm();  
  }else if(!name.compare("xori")){
      regs[getRd()] = regs[getRs1()] ^ getImm();
  }else if(!name.compare("ori")){
    regs[getRd()] = regs[getRs1()] | getImm();
  }else if(!name.compare("andi")){
    regs[getRd()] = regs[getRs1()] & getImm();
  }else if(!name.compare("slli")){
    regs[getRd()] = (uint32_t) regs[getRs1()] << getImm();
  }else if(!name.compare("srli")){
    regs[getRd()] = (uint32_t) regs[getRs1()] >> getImm();
  }else if(!name.compare("srai")){
    regs[getRd()] = regs[getRs1()] >> getImm();
  }else if(!name.compare("jalr")){
    regs[getRd()] = *pc + 4;
    *pc = (regs[getRs1()] + getImm()) & 0xFFFFFFFE;
    *pc -= 4;
  }else if(!name.compare("ebreak")){
      cout << "ebreak" << endl;
  }

  regs[0] = 0;
}