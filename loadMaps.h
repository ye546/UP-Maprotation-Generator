
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
class loadMaps
{
public:
	loadMaps();
	void loadBannedMaps(std::vector<std::string> unwantedMaps);
	void readAvailableMaps(std::vector<std::string> availableMaps);
private:
	std::string _fileName;
	std::ifstream _readFile, _map;
	std::string _bannedMaps[12], _availableMaps[130];
	bool _isGood;
};