#ifndef EbreakException_H
#define EbreakException_H

#include <exception>

using namespace std;
#include <string>

class EbreakException : public exception {
private:
    string message;

public:
    EbreakException(const char* msg);
    const char* what() const throw();
};

#endif