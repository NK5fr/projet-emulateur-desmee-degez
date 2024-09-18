#include <iostream> 
#include  <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include <string>          
#include <bitset>

using namespace std; 

vector<uint32_t> readFile(string filePath);
uint32_t getOpcode(uint32_t word);
void printResult(vector<uint32_t> words);
void printHelp();
void printError();