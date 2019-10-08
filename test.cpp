#include "param.hpp"
#include <iostream>

int main() {
  param::parameter param("input.cfg");
  std::cout << param.get<bool>("test") << std::endl;
}