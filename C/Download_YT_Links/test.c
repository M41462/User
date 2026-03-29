#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#define MAX_FILENAME_LEN 256
#define MAX_COMMAND_LEN 1024

ma_engine engine;
bool audio_initialized = false;

bool DownloadMusic(const char *URL, const char *FILE_PATH) {
    if (URL == NULL || FILE_PATH == NULL) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return false;
    }
    
    char command[MAX_COMMAND_LEN];
    
#ifdef _WIN32
    for (int i = 0; i < 10; i++) {
        char output_file[MAX_FILENAME_LEN];
        snprintf(output_file, sizeof(output_file), "video%d.mp3", i);
        
        if (access(output_file, F_OK) == 0) {
            printf("%s already exists, skipping...\n", output_file);
            continue;
        }
        
        snprintf(command, sizeof(command),
                 "yt-dlp \"%s\" -x --audio-format mp3 -o \"video%d.%%(ext)s\" > nul 2> nul",
                 URL, i);
                 
        int status = system(command);
        if (status == 0) {
            return true;
        }
        break;
    }
#else
    snprintf(command, sizeof(command),
             "yt-dlp \"%s\" -x --audio-format mp3 -o \"%s\" > /dev/null 2>&1",
             URL, FILE_PATH);
#endif

    int status = system(command);
    
    if (status != 0) {
        fprintf(stderr, "Download failed\n");
        return false;
    }
    
    return true;
}

bool InitAudio(void) {
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        fprintf(stderr, "Audio init failed\n");
        return false;
    }
    audio_initialized = true;
    return true;
}

void PlayAudio(const char *FILE_PATH) {
    if (!audio_initialized || FILE_PATH == NULL) {
        fprintf(stderr, "Error: Audio not initialized or invalid file path\n");
        return;
    }
    ma_engine_play_sound(&engine, FILE_PATH, NULL);
}

void ShutdownAudio(void) {
    if (audio_initialized) {
        ma_engine_uninit(&engine);
        audio_initialized = false;
    }
}

int main(int argc, const char **argv) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *URL = argv[1];
    char FILE_PATH[MAX_FILENAME_LEN] = "video0";
    
    if (!DownloadMusic(URL, FILE_PATH)) {
        fprintf(stderr, "Invalid link or download failed\n");
        return EXIT_FAILURE;
    }
    
    if (!InitAudio()) {
        fprintf(stderr, "Failed to initialize audio\n");
        return EXIT_FAILURE;
    }
    
    strcat(FILE_PATH, ".mp3");
    printf("Download Music successfully!\n");
    printf("%s\n", FILE_PATH);
    
    PlayAudio(FILE_PATH);
    
    printf("Playing... press Enter to exit\n");
    getchar();
    
    ShutdownAudio();
    
    return EXIT_SUCCESS;
}
