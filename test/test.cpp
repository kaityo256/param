#include "../param.hpp"
#include <iostream>

int main() {
  std::string filename = "input.cfg";
  param::parameter param(filename);
  if (!param) {
    std::cerr << "Could not find file " << filename << std::endl;
    std::abort();
  }

  std::cout << "Read existing values" << std::endl;
  std::cout << "Reading bool named \"bool\": " << param.get<bool>("bool") << std::endl;
  std::cout << "Reading int named \"int\": " << param.get<int>("int") << std::endl;
  std::cout << "Reading double named \"double\": " << param.get<double>("double") << std::endl;
  std::cout << "Reading double named \"str\": " << param.get<std::string>("str") << std::endl;
  std::cout << std::endl;

  std::cout << "Read non-existing values" << std::endl;
  std::cout << "Reading bool named \"bool-non-exsiting\": " << param.get<bool>("bool-non-exsiting", false) << std::endl;
  std::cout << "Reading int named \"int-non-exsiting\": " << param.get<int>("int-non-exsiting", 6789) << std::endl;
  std::cout << "Reading double named \"double-non-exsiting\": " << param.get<double>("double-non-exsiting", 6.789) << std::endl;
  std::cout << std::endl;

  // Check for non-exisiting file
  std::string non_existing_filename = "input_non_existing.cfg";
  param::parameter param2(non_existing_filename);
  if (!param2) {
    std::cerr << "Error" << std::endl;
  }
}
