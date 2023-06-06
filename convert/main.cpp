#include<iostream>
#include<string>
#include"../level.hpp"
#include<unistd.h>

int main(int argc, char **argv) {
    
    int opt = 0;
    int mode = 0;
    std::string input, output;
    while((opt = getopt(argc, argv, "i:o:tb")) != -1) {
        switch(opt) {
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case 't':
                mode = 1;
                break;
            case 'b':
                mode = 2;
                break;
        }
    }
    
    if(mode == 0 || input.length() == 0 || output.length() == 0) {
        std::cerr << argv[0] << " -i input.lvl-o output.txt-t\n";
        std::cerr << argv[0] << " -i input.txt -o output.lvl -b\n";
        exit(EXIT_FAILURE);
    }
    
    if(mode == 1) {
        game::Level level;
        if(!level.loadLevel(input)) {
            std::cerr << "Error loading level: " << argv[2] << "\n";
            exit(EXIT_FAILURE);
        }
        if(level.saveLevelText(output)) {
            std::cout << "level saved as text: " <<  output << "\n";
        } else {
            std::cerr << "Error level " << output << " could not be saved.\n";
        }
    } else if (mode == 2) {
        game::Level level;
        if(!level.loadLevelText(input)) {
            std::cerr << "Error loading level text..\n";
            exit(EXIT_FAILURE);
        }
        if(level.saveLevel(output)) {
            std::cout << "Level saved as bin: " << output << "\n";
        } else {
            std::cerr << "Error level " << output << " could not be saved.\n";
        }
    }
    return 0;
}

