#include "../header/UEncodingInstruction.h"

UEncodingInstruction::UEncodingInstruction(uint32_t word, string name) {
  this->word = word;
  this->name = name;
}

string UEncodingInstruction::getName(){
  string res;
  for (char c : this->name) {
      res += tolower(c); 
  }
  return res;
}

uint32_t UEncodingInstruction::getRd(){
  return (this->word >> 7) & 0x1f;
}

int32_t UEncodingInstruction::getImm(){
  if(!this->name.compare("JAL")){
    return getImmJ();
  }

  int32_t imm = (this->word) & 0xfffff000;
  return imm;
}

int32_t UEncodingInstruction::getImmJ(){
  int imm_10_1 = (this->word >> 21) & 0x3ff;
  int imm_11 = (this->word >> 20) & 0x1;
  int imm_19_12 = (this->word >> 12) & 0xff;
  int imm_20 = (this->word >> 31) & 0x1;
  int32_t imm32 = imm_20 << 20 | imm_19_12 << 12 | imm_11 << 11 | imm_10_1 << 1;
  if ((imm32 >> 20) & 1) {
    return imm32 | 0xffe00000;
  }
  return imm32;
}

void UEncodingInstruction::printInstruction(){
  int32_t imm = getImm();
  stringstream immHex;
  immHex << hex << imm;

  ostringstream oss;
  oss << "x" << getRd() << ", " << imm;
  cout << getName() << " " << oss.str() << " // 0x" << immHex.str() << endl;
}

void UEncodingInstruction::execute(int32_t* regs, uint32_t* pc, Memory* memory){
  string name = getName();
  uint32_t rd = getRd();
  int32_t imm = getImm();

  if(!name.compare("jal")){
    regs[rd] = *pc + 4;
    *pc += imm - 4;
  }else if(!name.compare("auipc")){
    regs[rd] = *pc + imm;
  }else if(!name.compare("lui")){
    regs[rd] = imm;
  }

  regs[0] = 0;
}