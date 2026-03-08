#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 1024

bool install_dependencies(void) {
  if (system("which yt-dlp > /dev/null") != 0 ||
      system("which mpv > /dev/null") != 0) {
    printf("Required tools not found. Install yt-dlp and mpv? (y/n): ");
    string resp = get_string("Enter your choice");
    if (resp[0] == 'y' || resp[0] == 'Y') {
      if (system("sudo apt install -y yt-dlp mpv") != 0) {
        fprintf(stderr, "Installation failed. Please install manually.\n");
        free(resp);
        return false;
      }
      printf("Dependencies installed successfully.\n");
    } else {
      free(resp);
      return false;
    }
    free(resp);
  }
  return true;
}

bool is_valid_link(const char *link) {
  return strstr(link, "youtube.com/watch?v=") || strstr(link, "youtu.be/");
}

void get_unique_output(char *buffer, const char *extension) {
  for (int i = 0; i < 10; i++) {
    snprintf(buffer, MAX_PATH, "%s/Music/video%i.%s", getenv("HOME"), i,
             extension);
    if (access(buffer, F_OK) != 0)
      return;
  }
  snprintf(buffer, MAX_PATH, "/tmp/default_output.%s", extension);
}

void play_file(const char *path) {
  printf("Playing: %s\n", path);
  char command[MAX_PATH + 256];
  snprintf(command, sizeof(command), "mpv \"%s\"", path);
  if (system(command) != 0) {
    fprintf(stderr, "Failed to play file: %s\n", path);
  }
}

void download_mp4(void) {
  string link = get_string("Enter MP4 YouTube link: ");
  if (!is_valid_link(link)) {
    fprintf(stderr, "Invalid YouTube link.\n");
    free(link);
    return;
  }

  char output[MAX_PATH];
  get_unique_output(output, "mp4");

  char command[MAX_PATH + 256];
  snprintf(command, sizeof(command),
           "yt-dlp -f mp4/bestvideo+bestaudio/best --merge-output-format mp4 "
           "-o \"%s\" \"%s\"",
           output, link);

  printf("Downloading video...\n");
  if (system(command) == 0) {
    printf("Downloaded to %s\n", output);
    string choice = get_string("Play it now? (y/n): ");
    if (choice[0] == 'y' || choice[0] == 'Y') {
      play_file(output);
    }
    free(choice);
  } else {
    fprintf(stderr, "Download failed.\n");
  }

  free(link);
}

void download_mp3(void) {
  string link = get_string("Enter MP3 YouTube link: ");
  if (!is_valid_link(link)) {
    fprintf(stderr, "Invalid YouTube link.\n");
    free(link);
    return;
  }

  char output[MAX_PATH];
  get_unique_output(output, "mp3");

  char command[MAX_PATH + 256];
  snprintf(command, sizeof(command),
           "yt-dlp -x --audio-format mp3 -o \"%s\" \"%s\"", output, link);

  printf("Downloading audio...\n");
  if (system(command) == 0) {
    printf("Downloaded to %s\n", output);
    string choice = get_string("Play it now? (y/n): ");
    if (choice[0] == 'y' || choice[0] == 'Y') {
      play_file(output);
    }
    free(choice);
  } else {
    fprintf(stderr, "Download failed.\n");
  }

  free(link);
}
void download_wav(void) {
  string link = get_string("Enter WAV YouTube link: ");
  if (!is_valid_link(link)) {
    fprintf(stderr, "Invalid YouTube link.\n");
    free(link);
    return;
  }

  char output[MAX_PATH];
  get_unique_output(output, "wav");

  char command[MAX_PATH + 256];
  snprintf(command, sizeof(command),
           "yt-dlp -x --audio-format wav -o \"%s\" \"%s\"", output, link);

  printf("Downloading audio...\n");
  if (system(command) == 0) {
    printf("Downloaded to %s\n", output);
    string choice = get_string("Play it now? (y/n): ");
    if (choice[0] == 'y' || choice[0] == 'Y') {
      play_file(output);
    }
    free(choice);
  } else {
    fprintf(stderr, "Download failed.\n");
  }

  free(link);
}

void menu(void) {
  if (!install_dependencies()) {
    return;
  }

  do {
    printf("\n==== YouTube Media Downloader ====\n");
    printf("1. Download MP4 Video\n");
    printf("2. Download MP3 Audio\n");
    printf("3. Download WAV Audio\n");
    printf("4. Exit\n");

    string choice = get_string("Choose an option: ");
    if (choice == NULL)
      continue;

    switch (choice[0]) {
    case '1':
      download_mp4();
      break;
    case '2':
      download_mp3();
      break;
    case '3':
      download_wav();
      break;
    case '4':
      printf("Goodbye!\n");
      return;
      default:
      printf("Invalid choice. Try again.\n");
    }free(choice);
    }
    while (true);
}

int main(void) {
  menu();
  return 0;
}
