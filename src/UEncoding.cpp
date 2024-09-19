#include "../header/UEncoding.h"

UEncoding::UEncoding(string name) {
  this->name = name;
}

string UEncoding::getName() {
  return this->name;
}