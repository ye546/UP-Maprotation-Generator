#include <cstdlib>
#include <iostream>
#include <vector>
#include <Windows.h>
#include "generateMapRotation.h"
#include "loadMaps.h"
int main() {
	generateMapRotation gm;
	std::vector<std::string> v, v2;
	gm.generateMaps(v, v2);

	system("pause");
	return 0;
}