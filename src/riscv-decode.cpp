#include <iostream> 
#include "../header/riscv-decode.h"

using namespace std; 

int main() { 
    cout << "Hello, World!" << endl; 
    addition(5,2);
    return 0; 
}

void addition(int a, int b){
    cout << a + b << endl;
}

