#include "../header/UEncodingInstruction.h"

UEncodingInstruction::UEncodingInstruction(uint32_t word, string name) {
  for (char c : name) {
      this->name += tolower(c); 
  }

  this->rd = (word >> 7) & 0x1f;
  this->imm = (word) & 0xfffff000;
}

string UEncodingInstruction::getName() {
  return this->name;
}

void UEncodingInstruction::printInstruction(){
  string rdStr = "x" + to_string(this->rd);
  stringstream immHex;
  immHex << hex << this->imm;

  cout << this->name << " " << rdStr << ", " << this->imm << "    // 0x" << immHex.str() << endl;
}