#include "loadMaps.h"
#include <cstdio>
loadMaps::loadMaps(){

}

void loadMaps::loadBannedMaps(std::vector<std::string> &unwantedMaps) {
	try_again:std::cin >> _fileName;
	_readFile.open(_fileName);

	if (_readFile.is_open()) {
		for (int i = 0; i < 12; i++) {
			_readFile >> unwantedMaps[i];
		}
		_readFile.close();
	}
	else {
		printf("this file does not exist, try again.");
		goto try_again;
	}

	printf("Skipping these maps: \n");
	for (unsigned int i = 0; i < unwantedMaps.size(); i++) {
		if (unwantedMaps[i] == "") continue; //excludes empty spots
		std::cout << unwantedMaps[i] << std::endl;
	}
}

void loadMaps::readAvailableMaps(std::vector<std::string> &availableMaps) {
	std::string name; try_again:std::cin >> name;
	if (name == "quit") exit(EXIT_SUCCESS);
	_map.open(name);
	
	if (_map.is_open()) {
		for (int i = 0; i < 130; i++) {
			_map >> availableMaps[i];
		}
		_map.close();
		_isGood = true;
	}
	else {
		printf("load a .txt file with the maps you wish to load.\n");
		goto try_again;
	}

	//print the content of the vector
	printf("Available maps:\n");
	for (unsigned int i = 0; i < availableMaps.size(); i++) {
		if (availableMaps[i] == "") continue; //excludes empty spots
			std::cout << availableMaps[i] << std::endl;
	}
	if (_isGood) {
		printf("%s initiated without a problem.\n", name.c_str());
	}
	else {
		printf("there was an error loading '%s'\n", name.c_str());
		exit(EXIT_FAILURE);
	}
}