#include"window.hpp"
#include"game_level.hpp"
#include<iostream>


int main(int argc, char **argv) {
    int width = 1280-16, height = 720-16;
    std::string def_level = "levels/level1.lvl";
    std::string gfx_file = "img/level.gfx";
    switch(argc) {
        case 3: {
            def_level = argv[1];
            gfx_file = argv[2];
        }
        break;
        case 1:
        case 2:
        case 4: {
            std::cout << argv[0] << "level.lvl file.gfx\n";
            return 0;
        } 
        break;
        case 5: {
            def_level = argv[1];
            gfx_file = argv[2];
            width = atoi(argv[3]);
            height = atoi(argv[4]);
       } 
       break;
    }
    if(!game::Window::createWindow("Game", width, height)) {
        std::cerr << "Error on init.\n";
        return EXIT_FAILURE;
    }
    game::GameLevel level;
    game::Window::init_object(&level);
    game::Window::setObject(&level);
    level.loadLevel(def_level,gfx_file);
    std::cout << "game: Level: " << def_level << " loaded.\n";
    fflush(stdout);
    return game::Window::loop();
}