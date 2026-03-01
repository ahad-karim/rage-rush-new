#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include "GameData.h"

int obstacleHeightLevel3 = 60;
int noOfObjLevel3;
int subLevelCount3 = 1;

GameObject objLevel3[50];

void subLevelDefining3() {
	if (subLevelCount3 == 1) {
		// Sublevel 1: Introduction to Fake Platforms
		noOfObjLevel3 = 0;
		// Platform (Real)
		objLevel3[noOfObjLevel3++] = { 200, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 200, 120, 200, 120 };
		objLevel3[noOfObjLevel3++] = { 500, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 500, 120, 500, 120 };
		objLevel3[noOfObjLevel3++] = { 800, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 800, 120, 800, 120 };
		//Spikes
		objLevel3[noOfObjLevel3++] = { 400, 60, 50, 20, 0, 1,
			true, true, false, 0, 0, 0,
			0, 400, 60, 400, 60 };

		// Fake Platform
		/*objLevel3[noOfObjLevel3++] = {400,  100,   150,   40,  4,  0,
		true, false, false, 0,   0,  0,
		0,    400,   100,   400, 100};*/


		// Sawblade moving vertically
		objLevel3[noOfObjLevel3++] = { -100, 140, 50, 50, 3, 0, true, true, true,
			10, 0, 200, 100, -100, 140, 1200, 140 };


		//Ghost
		objLevel3[noOfObjLevel3++] = { 1200, 200, 40, 40, 5, 0, true, true, true,
			2, 0, 350, 100, 800, 200, 800, 200 };

		// Door (None until subLevelCount3 == 4)
	}
	else if (subLevelCount3 == 2) {
		// Sublevel 2: Intro to Ghost over a long pit
		// Sublevel 1: Introduction to Fake Platforms
		noOfObjLevel3 = 0;
		// Platform (Real)
		objLevel3[noOfObjLevel3++] = { 200, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 200, 120, 200, 120 };
		objLevel3[noOfObjLevel3++] = { 500, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 500, 120, 500, 120 };
		objLevel3[noOfObjLevel3++] = { 800, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 800, 120, 800, 120 };
		// Fake Platform
		/*objLevel3[noOfObjLevel3++] = {400,  100,   150,   40,  4,  0,
		true, false, false, 0,   0,  0,
		0,    400,   100,   400, 100};*/

		objLevel3[noOfObjLevel3++] = { 700, 60, 50, 20, 0, 1,
			true, true, false, 0, 0, 0,
			0, 400, 60, 400, 60 };


		// Sawblade moving vertically
		objLevel3[noOfObjLevel3++] = { -100, 140, 50, 50, 3, 0, true, true, true,
			10, 0, 200, 100, -100, 140, 1200, 140 };
		objLevel3[noOfObjLevel3++] = { 1200, 60, 50, 50, 3, 0, true, true, true,
			10, 0, 200, 100, 1200, 60, -100, 60 };
		objLevel3[noOfObjLevel3++] = { 700, 750, 50, 50, 3, 0, true, true, true,
			15, 1, 550, 0, 700, 750, 700, 60 };


		//Ghost
		objLevel3[noOfObjLevel3++] = { 1200, 200, 40, 40, 5, 0, true, true, true,
			2, 0, 350, 100, 800, 200, 800, 200 };
	}

	else if (subLevelCount3 == 3) {
		// Sublevel 2: Intro to Ghost over a long pit
		// Sublevel 1: Introduction to Fake Platforms
		noOfObjLevel3 = 0;
		// Platform (Real)
		objLevel3[noOfObjLevel3++] = { 200, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 200, 120, 200, 120 };
		objLevel3[noOfObjLevel3++] = { 500, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 500, 120, 500, 120 };
		objLevel3[noOfObjLevel3++] = { 800, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 800, 120, 800, 120 };
		// Fake Platform
		/*objLevel3[noOfObjLevel3++] = {400,  100,   150,   40,  4,  0,
		true, false, false, 0,   0,  0,
		0,    400,   100,   400, 100};*/

		objLevel3[noOfObjLevel3++] = { 350, 60, 50, 20, 0, 1,
			true, true, true, 10, 0, 350,
			0, 350, 60, 450, 60 };

		objLevel3[noOfObjLevel3++] = { 650, 60, 50, 20, 0, 1,
			true, true, true, 10, 0, 650,
			0, 650, 60, 750, 60 };
		objLevel3[noOfObjLevel3++] = { 850, 155, 50, 20, 0, 1,
			true, true, false, 0, 0, 0,
			0, 850, 155, 850, 155 };


		// Sawblade moving vertically
		objLevel3[noOfObjLevel3++] = { -100, 140, 50, 50, 3, 0, true, true, true,
			10, 0, 200, 100, -100, 140, 1200, 140 };
		objLevel3[noOfObjLevel3++] = { -100, 140, 50, 50, 3, 0, true, true, true,
			10, 0, 500, 100, -100, 140, 1200, 140 };
		objLevel3[noOfObjLevel3++] = { -100, 140, 50, 50, 3, 0, true, true, true,
			10, 0, 800, 100, -100, 140, 1200, 140 };





		//Ghost
		objLevel3[noOfObjLevel3++] = { 1200, 200, 40, 40, 5, 0, true, true, true,
			2, 0, 350, 100, 800, 200, 800, 200 };
	}


	else if (subLevelCount3 == 4) {
		// Sublevel 4: The Finale
		noOfObjLevel3 = 0;
		// Platform (Real)
		objLevel3[noOfObjLevel3++] = { 200, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 200, 120, 200, 120 };
		objLevel3[noOfObjLevel3++] = { 400, 120, 150, 40, 4, 0,
			true, false, false, 0, 0, 0,
			0, 400, 120, 350, 120 };
		objLevel3[noOfObjLevel3++] = { 600, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 600, 120, 500, 120 };
		objLevel3[noOfObjLevel3++] = { 800, 120, 150, 40, 2, 0,
			true, false, false, 0, 0, 0,
			0, 800, 120, 800, 120 };


		// Fake Platform
		/*objLevel3[noOfObjLevel3++] = {400,  100,   150,   40,  4,  0,
		true, false, false, 0,   0,  0,
		0,    400,   100,   400, 100};*/

		objLevel3[noOfObjLevel3++] = { 350, 60, 50, 20, 0, 1,
			true, true, false, 0, 0, 0,
			0, 350, 60, 350, 60 };
		objLevel3[noOfObjLevel3++] = { 550, 60, 50, 20, 0, 1,
			true, true, false, 0, 0, 350,
			0, 550, 160, 850, 160 };
		objLevel3[noOfObjLevel3++] = { 750, 60, 50, 20, 0, 1,
			true, true, false, 0, 0, 350,
			0, 750, 160, 850, 160 };





		// Sawblade moving vertically
		objLevel3[noOfObjLevel3++] = { -100, 140, 50, 50, 3, 0, true, true, true,
			10, 0, 400, 100, -100, 140, 1200, 140 };






		//Ghost
		objLevel3[noOfObjLevel3++] = { 1200, 200, 40, 40, 5, 0, true, true, true,
			2, 0, 350, 100, 800, 200, 800, 200 };
		objLevel3[noOfObjLevel3++] = { 0, 200, 40, 40, 5, 0, true, true, true,
			2, 0, 350, 100, 800, 200, 800, 200 };


		// Door
		objLevel3[noOfObjLevel3++] = { 1000, 60, 100, 100, 1, 0,
			true, false, false, 0, 0, 0,
			0, 1000, 60, 1000, 60 };
	}
}

#endif