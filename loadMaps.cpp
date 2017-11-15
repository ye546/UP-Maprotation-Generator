#include "loadMaps.h"
#include <cstdio>
loadMaps::loadMaps(){

}

void loadMaps::loadBannedMaps(std::vector<std::string> &unwantedMaps) {
	try_again:std::cin >> _fileName;
	std::ifstream readFile(_fileName);
	if (readFile.is_open()) {
		for (int i = 0; i < 12; i++) {
			readFile >> _bannedMaps[i];
		}
	}
	else {
		printf("this file does not exist, try again.");
		goto try_again;
	}

	printf("moving fiels to the vector...\n");
	for (int i = 0; i < 12; i++) {
		unwantedMaps.push_back(_bannedMaps[i]);
	}

	printf("Skipping these maps: \n");
	for (unsigned int i = 0; i < unwantedMaps.size(); i++) {
		std::cout << unwantedMaps[i] << std::endl;
	}
}

void loadMaps::readAvailableMaps(std::vector<std::string> &availableMaps) {
	std::string name; try_again:std::cin >> name;
	if (name == "quit") exit(1);
	std::ifstream map(name);
	//std::memset(_maps, 0, sizeof(std::string));
	
	if (map.is_open()) {
		for (int i = 0; i < 130; i++) {
			map >> _maps[i];
		}
		map.close();
		_isGood = true;
	}
	else {
		printf("load a .txt file with the maps you wish to load.\n");
		goto try_again;
	}

	printf("moving files to the vector...\n");
	//this moves the content from the array to the vector
	for (int i = 0; i < 130; i++) {
		availableMaps.push_back(_maps[i]);
	}

	//print the content of the vector
	printf("Available maps:\n");
	for (unsigned int i = 0; i < availableMaps.size(); i++) {
		if (availableMaps[i] == "") continue;
			std::cout << availableMaps[i] << std::endl;
	}
	if (_isGood) {
		printf("%s initiated without a problem.\n", name.c_str());
	
	}
	else {
		printf("there was an error loading '%s'\n", name.c_str());
		exit(1);
	}
}