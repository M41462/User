#define SDL_MAIN_HANDLED
#ifndef SAVE_HPP
#define SAVE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <string>

#define MAX_SAVES 15

class Save {
public:
    std::string Set_Save_Name();
    bool Is_Save_Name_Valid();
    void Save_To_Png(SDL_Renderer* renderer, SDL_Texture* texture);

private:
    std::string Save_Name = "Untitled";
    static inline int Save_Number = 0;
    std::string Save_Path;
};

#endif
