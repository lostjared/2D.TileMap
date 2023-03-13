#include"window.hpp"
#include"game_level.hpp"
#include<iostream>


int main(int argc, char **argv) {
    int width = 1280-16, height = 720-16;
    std::string def_level = "levels/level1.lvl";
    switch(argc) {
        case 2: {
            def_level = argv[1];
        }
        break; 
        case 3: {
            width = atoi(argv[1]);
            height = atoi(argv[2]);
        } 
        break;
        case 4: {
            def_level = argv[1];
            width = atoi(argv[2]);
            height = atoi(argv[3]);
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
    level.loadLevel(def_level);;
    std::cout << "game: Level: " << def_level << " loaded.\n";
    fflush(stdout);
    return game::Window::loop();
}