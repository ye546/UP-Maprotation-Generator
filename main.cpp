#include <cstdlib>
#include <iostream>
#include <vector>
#include <Windows.h>
#include "loadMaps.h"
int main() {
	loadMaps lm; lm.readAvailableMaps();
	system("pause");
	return 0;
}