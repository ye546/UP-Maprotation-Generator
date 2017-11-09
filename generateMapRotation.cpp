#include "generateMapRotation.h"
#include "loadMaps.h"
#include <Windows.h>
generateMapRotation::generateMapRotation(){

}

std::vector<std::string> generateMapRotation::generateMaps(std::vector<std::string> v) {
	loadMaps lm;
	CreateDirectoryA("C:/NewRotation", NULL);
	this->newRotation("newMappack.txt", std::ios::app);
	v = lm.readAvailableMaps(&lm.idk);
	return v;
}
