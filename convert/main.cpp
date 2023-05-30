#include<iostream>
#include"../level.hpp"

int main(int argc, char **argv) {

	if(argc != 3) {
		std::cerr << "Error requires two arguments.\n";
		exit(EXIT_FAILURE);
	}

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
	
	return 0;
}

