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
	void loadBannedMaps();
	void readAvailableMaps();
private:
	std::string _fileName;
	std::string _bannedMaps[12], _maps[130];
	std::vector<std::string> _unwantedMaps, _availableMaps;
	bool _isGood;
};

