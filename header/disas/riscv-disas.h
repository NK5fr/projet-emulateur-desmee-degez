#include <iostream> 
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include <string>          
#include <bitset>
#include "UEncodingInstruction.h"
#include "IEncodingInstruction.h"
#include "REncodingInstruction.h"
#include "SEncodingInstruction.h"

using namespace std; 

vector<uint32_t> readFile(string filePath);
uint32_t getOpcode(uint32_t word);
void printIEncoding(uint32_t word, string name);
void printUEncoding(uint32_t word, string name);
void printResult(vector<uint32_t> words);
void printHelp();
void printError();