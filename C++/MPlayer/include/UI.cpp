#include <dirent.h>

#include <string>

#include "UI.hpp"

namespace {
constexpr int MAX_COMMAND_LENGTH = 256;
}

std::string UI::Full_Path;

bool UI::Check_Dependencies() {
  return std::system("command -v fzf > /dev/null 2>&1") == 0 ||
         std::system("ffmpeg -h > /dev/null 2>&1") == 0;
}

void UI::Install_Dependencies() {
  if (Check_Dependencies()) {
    return;
  }

  std::cout << "Dependencies not found. Install? (y/n): ";
  char choice;
  if (std::cin >> choice && (choice == 'y' || choice == 'Y')) {
    const int installResult =
        std::system("sudo apt install fzf > /dev/null 2>&1 && "
                    "sudo apt install ffmpeg > /dev/null 2>&1 && "
                    "sudo apt install fonts-robot > /dev/null 2>&1");
    if (installResult == 0) {
      std::cout << "Dependencies installed successfully" << std::endl;
    } else {
      std::cerr << "Installation failed" << std::endl;
    }
  } else {
    std::cout << "Exiting..." << std::endl;
    exit(1);
  }
}

std::string UI::Menu() {
  if (!Check_Dependencies()) {
    Install_Dependencies();
  }

  char *command = new (std::nothrow) char[MAX_COMMAND_LENGTH];
  if (!command) {
    std::cerr << "Memory allocation failed" << std::endl;
    exit(1);
  }

  const char *home = std::getenv("HOME");
  if (!home) {
    std::cerr << "Error: HOME environment variable not set" << std::endl;
    delete[] command;
    exit(1);
  }

  std::string musicDir = std::string(home) + "/Music";

  DIR *dir = opendir(musicDir.c_str());
  if (!dir) {
    std::cerr << "Error: Music folder doesn't exist or is empty" << std::endl;
    delete[] command;
    exit(1);
  }

  struct stat st;
  if (stat(musicDir.c_str(), &st) != 0 || !(st.st_mode & S_IFDIR)) {
    std::cerr << "Error: Music directory doesn't exist" << std::endl;
    closedir(dir);
    delete[] command;
    exit(1);
  }

  if (chdir(musicDir.c_str()) != 0) {
    std::cerr << "Error: Cannot change to music directory" << std::endl;
    closedir(dir);
    delete[] command;
    exit(1);
  }

  FILE *fzf = popen("fzf", "r");
  if (!fzf) {
    std::cerr << "Error: Cannot run file picker" << std::endl;
    closedir(dir);
    delete[] command;
    exit(1);
  }

  if (!std::fgets(command, MAX_COMMAND_LENGTH, fzf)) {
    std::cerr << "Error: No file selected or folder is empty" << std::endl;
    pclose(fzf);
    closedir(dir);
    delete[] command;
    exit(1);
  }

  command[strcspn(command, "\n")] = '\0';
  std::cout << "Selected: " << command << std::endl;

  Full_Path = musicDir + "/" + command;

  pclose(fzf);
  closedir(dir);
  delete[] command;

  return GetSelectedFile();
}
