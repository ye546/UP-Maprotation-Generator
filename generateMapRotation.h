#pragma once
#include <string>
#include <vector>
#include <fstream>
class generateMapRotation
{
public:
	generateMapRotation();
	void generateMaps(std::vector<std::string> &v, std::vector<std::string> &v2);
	std::fstream newRotation;
};