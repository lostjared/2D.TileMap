#include"window.hpp"
#include"game_level.hpp"
#include<iostream>


int main(int argc, char **argv) {
    int width = 1280-16, height = 720-16;
    std::string def_level = "levels/level1.lvl";
    std::string gfx_file = "img/level.gfx";
    std::string background = "img/backgrounds/bg1.bmp";
    switch(argc) {
        case 4: {
            def_level = argv[1];
            gfx_file = argv[2];
            background = argv[3];
        }
            break;
        case 1:
        case 2:
        case 3: {
            std::cout << argv[0] << "level.lvl file.gfx background.bmp\n";
            return 0;
        } 
            break;
        case 6: {
            def_level = argv[1];
            gfx_file = argv[2];
            background = argv[3];
            width = atoi(argv[4]);
            height = atoi(argv[5]);
        } 
            break;
        default:
            std::cout << argv[0] << "level.lvl file.gfx background.bmp\n";
            break;
    }
    if(!game::Window::createWindow("Game", width, height)) {
        std::cerr << "Error on init.\n";
        return EXIT_FAILURE;
    }
    game::GameLevel level;
    game::Window::init_object(&level);
    game::Window::setObject(&level);
    level.loadLevel(def_level,gfx_file,background);
    std::cout << "game: Level: " << def_level << " loaded.\n";
    fflush(stdout);
    return game::Window::loop();
}
