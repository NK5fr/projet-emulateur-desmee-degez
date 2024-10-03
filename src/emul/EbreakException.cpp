#include "../../header/emul/EbreakException.h"

EbreakException::EbreakException(const char* msg) : message(msg){}

const char* EbreakException::what() const throw(){
    return message.c_str();
}
