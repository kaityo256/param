/*
MIT License
Copyright (c) 2019 - present H. Watanabe
The latest version is available at
https://github.com/kaityo256/params

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace param {

std::string trim(const std::string &str) {
  size_t start = 0;
  while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start]))) {
    ++start;
  }

  size_t end = str.size();
  while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
    --end;
  }

  return str.substr(start, end - start);
}

typedef std::map<std::string, std::string> ptype;
class parameter {
private:
  ptype params;
  bool valid;

  bool contains(std::string &key) const {
    return params.find(key) != params.end();
  }

public:
  parameter(const std::string filename)
      : valid(true) {
    loadfromfile(filename);
  }

  explicit operator bool() const {
    return valid;
  };

  void loadfromfile(const std::string filename) {
    std::ifstream is(filename);
    if (is.fail()) {
      std::cerr << "Could not open file " << filename << std::endl;
      valid = false;
    }
    readfromstream(is);
  }
  void readfromstream(std::istream &is) {
    std::string line;
    while (getline(is, line)) {
      if (line.length() > 0 && line[0] == '#') {
        continue;
      }
      size_t index = line.find("=");
      if (std::string::npos != index) {
        std::string key = line.substr(0, index);
        std::string value = line.substr(index + 1, line.length());
        key = trim(key);
        value = trim(value);
        params.insert(ptype::value_type(key, value));
      }
    }
  }
  void check_key(std::string &key) const {
    if (!contains(key)) {
      std::cerr << "No such key: " << key << std::endl;
      std::abort();
    }
  }

  template <class T>
  T get(std::string) {
  }

  template <class T>
  T get(std::string, T value) {
    return value;
  }
};

template <>
bool parameter::get<bool>(std::string key, bool value) {
  if (!contains(key)) {
    return value;
  }
  if ("yes" == params[key] || "Yes" == params[key] || "true" == params[key] || "True" == params[key]) {
    return true;
  } else {
    return false;
  }
}

template <>
bool parameter::get(std::string key) {
  check_key(key);
  return get<bool>(key, false);
}

template <>
int parameter::get(std::string key, int value) {
  if (!contains(key)) {
    return value;
  }
  return std::stoi(params[key]);
}

template <>
int parameter::get(std::string key) {
  check_key(key);
  return get<int>(key, 0);
}

template <>
double parameter::get(std::string key, double value) {
  if (!contains(key)) {
    return value;
  }
  return std::stod(params[key]);
}

template <>
double parameter::get(std::string key) {
  check_key(key);
  return get<double>(key, 0.0);
}

template <>
std::string parameter::get(std::string key, std::string value) {
  if (!contains(key)) {
    return value;
  }
  return params[key];
}

template <>
std::string parameter::get(std::string key) {
  check_key(key);
  return get<std::string>(key, "");
}

} // namespace param
