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

	CreateDirectoryA("C:/NewRotation", NULL);
	newRotation.open("C:/NewRotation/newMappack.txt", std::ios::app);
	lm.readAvailableMaps(v);
	lm.loadBannedMaps(v2);
	
	int duplicates = 0;
	int length = (sizeof(v) / sizeof(v[0]));

	try_again:for (int i = 0; i < 12; i++) {
		newMaps[i] = v[rand() % length];
		if (newMaps[i] == v2[0] || v2[i] == v2[1] ||
			newMaps[i] == v2[2] || v2[i] == v2[3] ||
			newMaps[i] == v2[4] || v2[i] == v2[5] ||
			newMaps[i] == v2[6] || v2[i] == v2[7] ||
			newMaps[i] == v2[8] || v2[i] == v2[9] ||
			newMaps[i] == v2[10] || newMaps[i] == v2[11]) {
			v.clear();
			duplicates += 1;
			goto try_again;
		}
		else {
			if (newRotation.is_open()) {
				for (int i = 0; i < 12; i++) {
					newRotation << " map " << newMaps[i];
				}
				newRotation.close();
			}
			printf("redid the process %i times\n", duplicates);
		}
	}
}