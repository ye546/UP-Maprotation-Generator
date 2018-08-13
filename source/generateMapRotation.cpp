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
	int length = sizeof(v);

	try_again:for (int i = 0; i < 12; i++) {
		newMaps.push_back(v[rand() % length]);
		if (newMaps[i] == v2[i]) {
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
