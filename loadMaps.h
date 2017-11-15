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
	void loadBannedMaps(std::vector<std::string> &unwantedMaps);
	void readAvailableMaps(std::vector<std::string> &availableMaps);
private:
	std::string _fileName;
	std::vector<std::string> _bannedMaps, _bannedMaps, _maps;
	bool _isGood;
};