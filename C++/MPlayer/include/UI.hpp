#pragma once

#ifndef UI_HPP
#define UI_HPP

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

constexpr int MAX_COMMAND_LENGTH = 256;

class UI {
public:
  static std::string Full_Path;
  static std::string GetSelectedFile() { return Full_Path; }
  bool Check_Dependencies();
  void Install_Dependencies();
  std::string Menu();
};

#endif
