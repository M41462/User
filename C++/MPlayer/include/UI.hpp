#pragma once

#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <string>

class UI {
public:
  static std::string Full_Path;
  static std::string GetSelectedFile() { return Full_Path; }
  std::string Menu();
};

#endif
