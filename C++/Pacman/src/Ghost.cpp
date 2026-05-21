#include "../include/Ghost.hpp"
#include <string>

namespace pacman {

// TODO: implement ghost AI, movement patterns, and rendering
Ghost::Ghost() : ghostsSprite(ghostsTexture[0]) {
    ghostsPosition = {0,0}; 
}

Ghost::~Ghost() {}


bool Ghost::initGhostsTexture(){
    std::string path = ghostsTexturePath; 
    for(int i = 0 ; i < MAX_GHOSTS ; i++){
        path += std::to_string(i); 
        if (!ghostsTexture->loadFromFile(path)){
            return false;
        }
    }
    return true; 
}

} // namespace pacman
