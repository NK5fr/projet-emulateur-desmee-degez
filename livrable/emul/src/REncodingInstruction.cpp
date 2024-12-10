#include "../header/REncodingInstruction.h"

map<string, map<uint32_t, string>> REncodingInstruction::instructions = {
    {"OP", {
        {1, "sll"},
        {2, "slt"},
        {3, "sltu"},
        {4, "xor"},
        {6, "or"},
        {7, "and"}}}
};

map<string, map<uint32_t, string>> REncodingInstruction::mInstructions = {
    {"OP", {
        {0, "mul"},
        {1, "mulh"},
        {2, "mulhsu"},
        {3, "mulhu"},
        {4, "div"},
        {5, "divu"},
        {6, "rem"},
        {7, "remu"}}}
};

REncodingInstruction::REncodingInstruction(uint32_t word, string name) {
  this->name = name;
  this->word = word;
}

string REncodingInstruction::getName(){
  uint32_t funct3 = (this->word >> 12) & 0x7;
  uint32_t funct7 = (this->word >> 25) & 0x7f;

  if(funct7 == 1){
    try{
      return mInstructions.at(this->name).at(funct3);
    }catch (const out_of_range& oor){
      stringstream ssword;
      ssword << hex << word;
      stringstream message;
      message << "instruction set error: invalid intruction: error funct3 : " << funct3 << ", funct7 : " << funct7 << " for opcode " << this->name << " for word " << setfill('0') << setw(8) << ssword.str();
      throw invalid_argument(message.str());
    }
  }

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
  }else if(!name.compare("and")){
    regs[rd] = regs[rs1] & regs[rs2];
  }else if(!name.compare("mul")){
    int64_t res = regs[rs1] * regs[rs2];
    regs[rd] = (int32_t) (res & 0xffffffff);
  }else if(!name.compare("mulh")){
    int64_t x = regs[rs1];
    int64_t y = regs[rs2];
    int64_t res = x * y;
    regs[rd] = int32_t (res >> 32);
  }else if(!name.compare("mulhsu")){
    int64_t x = regs[rs1];
    uint64_t y = (uint32_t) regs[rs2];
    int64_t res = x * y;
    regs[rd] = (int32_t) (res >> 32);
  }else if(!name.compare("mulhu")){
    uint64_t x = (uint32_t) regs[rs1];
    uint64_t y = (uint32_t) regs[rs2];
    int64_t res = x * y;
    regs[rd] = (int32_t) (res >> 32);
  }else if(!name.compare("div")){
    if(regs[rs2] == 0) regs[rd] = -1;
    else if (regs[rs1] == -2147483648 && regs[rs2] == -1) regs[rd] = -2147483648;
    else regs[rd] = regs[rs1] / regs[rs2];
  }else if(!name.compare("divu")){
    if(regs[rs2] == 0) regs[rd] = 4294967295;
    else regs[rd] = (uint32_t) regs[rs1] / (uint32_t) regs[rs2];
  }else if(!name.compare("rem")){
    if(regs[rs2] == 0) regs[rd] = regs[rs1];
    else if (regs[rs1] == -2147483648 && regs[rs2] == -1) regs[rd] = 0;
    else regs[rd] = regs[rs1] % regs[rs2];
  }else if(!name.compare("remu")){
    if(regs[rs2] == 0) regs[rd] = regs[rs1];
    else regs[rd] = (uint32_t) regs[rs1] % (uint32_t) regs[rs2];
  }

  regs[0] = 0;
}