#include<iostream>
#include<string>
#include"../level.hpp"

int main(int argc, char **argv) {

	if(argc != 4) {
		std::cerr << "Error requires two arguments.\n";
		exit(EXIT_FAILURE);
	}

	if(std::string(argv[3]) == "-t") {
		game::Level level;
		if(!level.loadLevel(argv[1])) {
			std::cerr << "Error loading level: " << argv[1] << "\n";
			exit(EXIT_FAILURE);
		}
		if(level.saveLevelText(argv[2])) {
			std::cout << "level saved as text: " << argv[2] << "\n";
		} else {
			std::cerr << "Error level " << argv[2] << " could not be saved.\n";
		}
	} else if (std::string(argv[3]) == "-b") {
		game::Level level;
		if(!level.loadLevelText(argv[1])) {
			std::cerr << "Error loading level text..\n";
			exit(EXIT_FAILURE);
		}
		if(level.saveLevel(argv[2])) {
			std::cout << "Level saved as bin: " << argv[2] << "\n";
		} else {
			std::cerr << "Error level " << argv[2] << " could not be saved.\n";
		}
	}
	
	return 0;
}

