#include "loadMaps.h"
#include <cstdio>
loadMaps::loadMaps(){

}

void loadMaps::loadBannedMaps() {
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
		_unwantedMaps.push_back(_bannedMaps[i]);
	}

	printf("Skipping these maps: \n");
	for (int i = 0; i < _unwantedMaps.size(); i++) {
		std::cout << _unwantedMaps[i] << std::endl;
	}
}

void loadMaps::readAvailableMaps() {
	std::string name; try_again:std::cin >> name;
	if (name == "quit")
		exit(1);

	std::ifstream map(name);
	std::memset(_maps, 0, sizeof(std::string));
	if (map.is_open()) {
		//I'd rather just shove this into the vector immediately, but how?
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
	//move the content from the array to the vector, must be a better way to do this rather than copying it from an array?
	printf("moving files to the vector...\n");
	for (int i = 0; i < 130; i++) {
		_availableMaps.push_back(_maps[i]);
	}
	//printf content of the vector to see if it read the .txt file successfully
	printf("Available maps:\n");
	for (int i = 0; i < _availableMaps.size(); i++) {
		if (_availableMaps[i] == "") continue;
			std::cout << _availableMaps[i] << std::endl;
	}
	if (_isGood) {
		printf("%s initiated without a problem.\n", name.c_str());
	}
	else {
		printf("there was an error loading %s, try again.\n", name.c_str());
		exit(1);
	}
}