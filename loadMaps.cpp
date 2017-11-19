#include "loadMaps.h"
#include <cstdio>
loadMaps::loadMaps() {

}

void loadMaps::loadBannedMaps(std::vector<std::string> unwantedMaps) {
	printf("\n--loadBannedMaps func--\n");
	std::memset(_bannedMaps, 0, sizeof(std::string));
	try_again:std::cin >> _fileName;
	_readFile.open(_fileName);

	if (_readFile.is_open()) {
		for (int i = 0; _readFile >> _bannedMaps[i]; i++) {
			unwantedMaps.push_back(_bannedMaps[i]);
		}
		_readFile.close();
	}
	else {
		printf("this file does not exist or is not accessable, try again.");
		goto try_again;
	}

	printf("Skipping these maps: \n");
	for (unsigned int i = 0; i < unwantedMaps.size(); i++) {
		if (unwantedMaps[i] == "") continue; //exclude empty slot
		std::cout << unwantedMaps[i] << std::endl;
	}

	printf("\n(%i indexes=\n", unwantedMaps.size());
}

void loadMaps::readAvailableMaps(std::vector<std::string> availableMaps) {
	printf("--readAvailableMaps func--\n");
	std::memset(_availableMaps, 0, sizeof(std::string));
	std::string name; try_again:std::cin >> name;
	
	if (name == "quit") exit(EXIT_SUCCESS);
	_map.open(name);

	if (_map.is_open()) {	
		for (int i=0; _map >> _availableMaps[i]; i++) {
			availableMaps.push_back(_availableMaps[i]);
		}
		_map.close();
		_isGood = true;
	}
	else {
		printf("load a .txt file with the maps you wish to load.\n");
		_isGood = false;
		goto try_again;
	}
	
	//print the content of the vector
	printf("\nAvailable maps:\n");
	for (unsigned int i = 0; i < availableMaps.size(); i++) {
		if (availableMaps[i] == "") continue; //exclude empty slot
		std::cout << availableMaps[i] << std::endl;
	}

	if (_isGood) {
		printf("\n%s initiated without a problem.\n", name.c_str());
	}
	else {
		printf("\nthere was an error loading '%s'\n", name.c_str());
		exit(EXIT_FAILURE);
	}

	printf("\n(%i indexes)\n", availableMaps.size());
}