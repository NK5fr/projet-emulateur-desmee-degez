#include "../../header/disas/UEncodingInstruction.h"

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

string UEncodingInstruction::getRd(){
  uint32_t rd = (this->word >> 7) & 0x1f;
  return "x" + to_string(rd);
}

int32_t UEncodingInstruction::getImm(){
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

void UEncodingInstruction::printInstruction(string offset){
  int32_t imm;

  if(!this->name.compare("JAL")){
    imm = getImmJ();
  }else{
    imm = getImm();
  }

  stringstream immHex;
  immHex << hex << imm;

  cout << setfill('0') << setw(8) << offset << ": ";
  cout << getName() << " " << getRd() << ", " << imm << "    // 0x" << immHex.str() << endl;
}