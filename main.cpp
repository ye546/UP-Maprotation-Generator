#include <cstdlib>
#include <iostream>
#include <vector>
#include <Windows.h>
#include "generateMapRotation.h"
int main() {
	generateMapRotation gm;
	std::vector<std::string> v;
	gm.generateMaps(v);
	system("pause");
	return 0;
}