#include <iostream> 
#include <fstream>
#include <map>
#include <array>

using namespace std; 

void initOpcode();
void lireFichier(string filePath);
int getOpcode(uint32_t word);