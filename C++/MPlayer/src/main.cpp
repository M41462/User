#include "../include/MP.hpp"
#include "../include/UI.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    
    UI ui;
    const std::string fileName = ui.Menu();
    
    MPlayer* mp = new (std::nothrow) MPlayer();
    if (!mp) {
        std::cerr << "Memory allocation failed" << std::endl;
        return EXIT_FAILURE;
    }
    
    mp->LoadAndPlay(const_cast<std::string&>(fileName));
    mp->Run();
    
    delete mp;
    return EXIT_SUCCESS;
}
