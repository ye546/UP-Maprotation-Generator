#include "generateMapRotation.h"
#include "loadMaps.h"
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
generateMapRotation::generateMapRotation(){

}

void generateMapRotation::generateMaps(std::vector<std::string> &v, std::vector<std::string> &v2) {
	srand(time(NULL));
	std::vector<std::string> newMaps;
	loadMaps lm;
	//CreateDirectoryA("C:/NewRotation", NULL);
	//newRotation("newMappack.txt", std::ios::app);
	lm.readAvailableMaps(v);
	lm.loadBannedMaps(v2);
	int length = (sizeof(v) / sizeof(v[0]));

	for (int i = 0; i < 12; i++) {
		newMaps[i] = v[rand() % length];
		if (newMaps[i] == v[0] || v[i] == v[1] ||
			newMaps[i] == v[2] || v[i] == v[3] ||
			newMaps[i] == v[4] || v[i] == v[5] ||
			newMaps[i] == v[6] || v[i] == v[7] ||
			newMaps[i] == v[8] || v[i] == v[9] ||
			newMaps[i] == v[10] || newMaps[i] == v[11]) {
			continue;
		}
		else {
			//write to file
		}
	}
}
