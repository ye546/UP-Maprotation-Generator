#pragma once
#include <string>
#include <vector>
#include <fstream>
class generateMapRotation
{
public:
	generateMapRotation();
	std::ifstream newRotation("", std::ifstream::app);
	std::vector<std::string> generateMaps(std::vector<std::string> v);
};

