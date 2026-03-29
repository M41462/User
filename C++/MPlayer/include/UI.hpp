#pragma once

#ifndef UI_HPP
#define UI_HPP

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

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
