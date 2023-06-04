#include<iostream>
#include<string>
#include"../level.hpp"

int main(int argc, char **argv) {
	
	if(argc != 4) {
		std::cerr << "Error requires three arguments.\n";
		std::cerr << argv[0] << " -t level.lvl level.txt\n";
		std::cerr << argv[0] << " -b level.txt level.lvl\n";
		exit(EXIT_FAILURE);
	}

	if(std::string(argv[1]) == "-t") {
		game::Level level;
		if(!level.loadLevel(argv[2])) {
			std::cerr << "Error loading level: " << argv[2] << "\n";
			exit(EXIT_FAILURE);
		}
		if(level.saveLevelText(argv[3])) {
			std::cout << "level saved as text: " << argv[3] << "\n";
		} else {
			std::cerr << "Error level " << argv[3] << " could not be saved.\n";
		}
	} else if (std::string(argv[1]) == "-b") {
		game::Level level;
		if(!level.loadLevelText(argv[2])) {
			std::cerr << "Error loading level text..\n";
			exit(EXIT_FAILURE);
		}
		if(level.saveLevel(argv[3])) {
			std::cout << "Level saved as bin: " << argv[3] << "\n";
		} else {
			std::cerr << "Error level " << argv[3] << " could not be saved.\n";
		}
	}
	
	return 0;
}

