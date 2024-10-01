#include <string>
#include <iostream>
#include <getopt.h>
#include <fstream>

using namespace std;

void printHelp();
void printDetailedHelp();
void printError();
void printVersion();
void loadBinaryFile(string file, char* memory);
void printMemory(char* memory);