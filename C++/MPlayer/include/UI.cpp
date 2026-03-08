#include "UI.hpp"
#include <dirent.h>
#include <string>
std::string UI::Full_Path;
bool UI::Check_Dependencies() {
  if (std::system("command -v fzf > /dev/null") == 0 ||
      std::system("ffmpeg -h > /dev/null") == 0) {
    return true;
  }
  return false;
}

void UI::Install_Dependencies() {
  if (!Check_Dependencies()) {
    char Choice;
    Choice = getchar();
    if (Choice == 'y' || Choice == 'Y') {
      if (std::system("sudo apt install fzf > /dev/null") == 0 &&
          std::system("sudo apt install ffmpeg > /dev/null") == 0 &&
          std::system("sudo apt install fonts-robot > /dev/null") == 0) {
        std::cout << "Installed FZF \n";
        std::cout << "Installed FFMPEG \n";
        std::cout << "Installed FONTS-ROBOT\n";
      }
    } else {
      std::cout << "Exiting \n";
      exit(1);
    }
  }
}

std::string UI::Menu() {
  if (Check_Dependencies()) {
    char *command = (char *)malloc(MAX);
    if (command == NULL) {
      std::cout << "Error allocating memory" << std::endl;
      exit(1);
    }
    const char *home = std::getenv("HOME");
    if (home == NULL) {
      std::cout << "Error getting home directory" << std::endl;
      exit(1);
    }
    std::string music_dir = std::string(home) + "/Music";
    DIR *dir = opendir(music_dir.c_str());
    if (dir == NULL) {
      std::cout << "Music Folder Doesn't Exist or it's empty directory \n";
      exit(1);
    }
    struct stat st;
    if (stat(music_dir.c_str(), &st) || !(st.st_mode & S_IFDIR)) {
      std::cout << "Music Dir Doesn't Exist \n";
    }
    chdir(music_dir.c_str());
    FILE *fzf = popen("fzf", "r");
    if (fzf == NULL) {
      std::cout << "Error Running FZF \n";
      exit(1);
    }
    if (std::fgets(command, MAX, fzf) == NULL) {
      std::cout << "The Folder is Empty \n";
      pclose(fzf);
      exit(1);
    }
    command[strcspn(command, "\n")] = 0;
    std::cout << "Select File : " << command << std::endl;
    Full_Path = music_dir + "/" + command;
    pclose(fzf);
    closedir(dir);
    free(command);
  } else {
    UI::Install_Dependencies();
  }

  return UI::GetSelectedFile();
}
