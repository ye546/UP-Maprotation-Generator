#include "generateMapRotation.h"
#include "loadMaps.h"
#include <Windows.h>
#include <iostream>
generateMapRotation::generateMapRotation(){

}

void generateMapRotation::generateMaps(std::vector<std::string> &v) {
	loadMaps lm;
	CreateDirectoryA("C:/NewRotation", NULL);
	//newRotation("newMappack.txt", std::ios::app);
	lm.readAvailableMaps(v);
}
