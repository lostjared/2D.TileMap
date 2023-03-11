#include"window.hpp"
#include"game_level.hpp"
#include<iostream>


int main(int argc, char **argv) {
    int width = 1280-16, height = 720-16;
    std::string def_level = "levels/level1.lvl";
    if(argc == 2) {
        def_level = argv[1];
    }
    if(argc == 3) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    } else if(argc == 4) {
        def_level = argv[1];
        width = atoi(argv[2]);
        height = atoi(argv[3]);
    } 
    if(!game::Window::createWindow("Game", width, height)) {
        std::cerr << "Error on init.\n";
        return EXIT_FAILURE;
    }
    game::GameLevel level;
    game::Window::init_object(&level);
    game::Window::setObject(&level);
    level.loadLevel(def_level);;
    std::cout << "Level: " << def_level << "loaded.\n";
    return game::Window::loop();
}