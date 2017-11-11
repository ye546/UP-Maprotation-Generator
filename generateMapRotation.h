#pragma once
#include <string>
#include <vector>
#include <fstream>
class generateMapRotation
{
public:
	generateMapRotation();
	//std::ifstream newRotation("", std::ifstream::app);
	void generateMaps(std::vector<std::string> &v);
};

