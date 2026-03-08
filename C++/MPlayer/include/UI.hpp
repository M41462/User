#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#define MAX 100
class UI {
public:
  static std::string Full_Path;
  static std::string GetSelectedFile() { return Full_Path; }
  bool Check_Dependencies();
  void Install_Dependencies();
  std::string Menu();
};
