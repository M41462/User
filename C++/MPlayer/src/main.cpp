#include "../include/MP.hpp"
#include "../include/UI.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
  UI ui;
  std::string fileName = ui.Menu();
  MPlayer *MP = new MPlayer();
  if (MP == NULL) {
    std::cout << "Memory Allocation Failed" << std::endl;
    return EXIT_FAILURE;
  }
  MP->LoadAndPlay(fileName);
  MP->Run();
  delete MP;
  return EXIT_SUCCESS;
}
