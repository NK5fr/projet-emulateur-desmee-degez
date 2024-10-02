#include "../../header/emul/UEncodingInstruction.h"

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
  if ((imm32 >> 19) & 1) {
    return imm32 | 0xfff00000;
  }
  return imm32;
}

void UEncodingInstruction::printInstruction(){
  int32_t imm = getImm();

  stringstream immHex;
  immHex << hex << imm;

  ostringstream oss;
  oss << "x" << getRd() << ", " << imm;
  cout << left << setw(13) << setfill(' ') << getName() << left << setw(17) << setfill(' ') << oss.str() << "// 0x" << immHex.str() << endl;
}

void UEncodingInstruction::execute(int32_t* regs, uint32_t* pc){
  string name = getName();

  if(!name.compare("jal")){
      cout << "jal" << endl;
  }else if(!name.compare("auipc")){
      cout << "auipc" << endl;
  }else{
      cout << "lui" << endl;
  }
}