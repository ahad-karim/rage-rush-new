#ifndef LEVELTWO_H
#define LEVELTWO_H
#include "GameData.h"
#include "Images.h"

int obstacleHeightLevel2 = 60;
int noOfObjLevel2;
int subLevelCount2 = 1;
GameObject objLevel2[50];



void subLevelDefining2() {
	if (subLevelCount2 == 1) {
		// floor-hugging saws
		noOfObjLevel2 = 0;

		// Platforms (Width=120, Height=60 is good for jumping)

		objLevel2[noOfObjLevel2++] = { 400, 130, 120, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 400, 130, 400, 130 };


		// Saws moving horizontally across the floor (y=60 is floor)
		// Saw 1
		//objLevel2[noOfObjLevel2++] = {0, 60, 50, 50, 3, 0,  true, true, true,
		//8, 0,  300,  0,  0, 60, 1000, 60};
		objLevel2[noOfObjLevel2++] = { 300, 60, 50, 20, 0, 1, true, true, true,
			20, 0, 275, 60, 300, 60, 250, 60 };
		objLevel2[noOfObjLevel2++] = { 550, 60, 50, 20, 0, 1, true, true, true,
			20, 0, 520, 0, 550, 60, 650, 60 };
		// Saw 2 (starts from right)
		objLevel2[noOfObjLevel2++] = { -100, 60, 50, 50, 3, 0, true, true, true,
			10, 0, 550, 60, -100, 60, 900, 60 };


		// Door
		/*objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
		true, false, false, 0,    0, 0,
		0,    1000,  60,    1000, 60};*/

	}
	else if (subLevelCount2 == 2) {
		// Sublevel 2: "The Gauntlet" - Vertical saws that trigger as you progress
		noOfObjLevel2 = 0;

		// Platforms at varying heights
		objLevel2[noOfObjLevel2++] = { 300, 60, 50, 20, 0, 1,
			true, true, false, 20, 0,
			520, 0, 300, 60, 300, 60 };
		objLevel2[noOfObjLevel2++] = { 400, 130, 120, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 400, 130, 400, 130 };
		objLevel2[noOfObjLevel2++] = { 550, 60, 50, 20, 0, 1, true, true, true,
			20, 0, 520, 0, 550, 60, 650, 60 };
		objLevel2[noOfObjLevel2++] = { 700, 130, 120, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 700, 130, 450, 130 };
		objLevel2[noOfObjLevel2++] = { 900, -100, 50, 20, 0, 1, true, true, true,
			10, 1, 820, -100, 900, -100, 900, 60 };



		// Falling Saws (trigger when player gets close)
		// Saw 1 (drops when hero.x > 100)
		objLevel2[noOfObjLevel2++] = { 950, 60, 50, 50, 3, 1, true, true, true,
			10, 0, 350, 0, 950, 60, -100, 60 };
		objLevel2[noOfObjLevel2++] = { -100, 60, 50, 50, 3, 1, true, true, true,
			10, 0, 550, 0, -100, 60, 1200, 60 };
		// Door
		/*objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
		true, false, false, 0,    0, 0,
		0,    1000,  60,    1000, 60};*/
	}
	else if (subLevelCount2 == 3) {
		// Sublevel 3: "Diagonal Death" - Crossing saws
		noOfObjLevel2 = 0;

		// Platforms
		objLevel2[noOfObjLevel2++] = { 400, 130, 120, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 400, 130, 400, 130 };
		objLevel2[noOfObjLevel2++] = { 700, 130, 120, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 700, 130, 450, 130 };
		objLevel2[noOfObjLevel2++] = { 435, 60, 50, 20, 0, 1, true, true, true,
			10, 1, 400, 0, 435, 60, 435, -100 };

		// Diagonal Saw 1 (triggered by hero.x > 150)
		objLevel2[noOfObjLevel2++] = { -100, 60, 50, 50, 3, 0, true, true, true,
			10, 2, 200, 60, -100, 60, 1200, 60 };
		// Diagonal Saw 2 (triggered by hero.x > 150) - Crosses the other one
		objLevel2[noOfObjLevel2++] = { 435, 750, 50, 50, 3, 1,
			true, true, true, 10, 1, 400,
			60, 435, 750, 435, -100 };
		objLevel2[noOfObjLevel2++] = { -100, 160, 50, 50, 3, 0,
			true, true, true, 10, 0, 550,
			130, -100, 160, 1200, 160 };


		// Door
		/*objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
		true, false, false, 0,    0, 0,
		0,    1000,  60,    1000, 60};*/
	}
	else if (subLevelCount2 == 4) {
		// Sublevel 4: "The Finale" - Precision Jumps + Fast Saws
		noOfObjLevel2 = 0;

		// Narrow risky platforms
		objLevel2[noOfObjLevel2++] = { 200, 130, 60, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 200, 130, 200, 130 };
		objLevel2[noOfObjLevel2++] = { 400, 130, 60, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 400, 130, 400, 130 };
		objLevel2[noOfObjLevel2++] = { 600, 130, 60, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 600, 130, 600, 130 };
		objLevel2[noOfObjLevel2++] = { 800, 130, 60, 30, 2, 0,
			true, false, false, 0, 0, 0,
			0, 600, 130, 800, 130 };

		/*objLevel2[noOfObjLevel2++] = {800,  200,   60,    40,  2,  0,
		true, false, false, 0,   0,  0,
		0,    800,   200,   800, 200};*/

		objLevel2[noOfObjLevel2++] = { 275, 60, 50, 20, 0, 1, true, true, false,
			20, 0, 520, 0, 275, 60, 275, 60 };
		objLevel2[noOfObjLevel2++] = { 475, 60, 50, 20, 0, 1, true, true, false,
			20, 0, 520, 0, 475, 60, 475, 60 };
		objLevel2[noOfObjLevel2++] = { 675, 60, 50, 20, 0, 1, true, true, false,
			20, 0, 520, 0, 675, 60, 675, 60 };

		// Fast Vertical Saws guarding the jumps
		objLevel2[noOfObjLevel2++] = { -100, 60, 50, 50, 3, 0, true, true, true,
			10, 0, 100, 0, -100, 60, 1200, 60 };
		objLevel2[noOfObjLevel2++] = { -100, 160, 50, 50, 3, 0, true, true, true,
			10, 0, 300, 0, -100, 160, 1200, 160 };
		objLevel2[noOfObjLevel2++] = { -100, 60, 50, 50, 3, 0, true, true, true,
			10, 0, 500, 0, -100, 60, 1200, 60 };
		objLevel2[noOfObjLevel2++] = { -100, 160, 50, 50, 3, 0, true, true, true,
			10, 0, 500, 0, -100, 160, 1200, 160 };
		objLevel2[noOfObjLevel2++] = { -100, 60, 50, 50, 3, 0, true, true, true,
			10, 0, 500, 0, -100, 60, 1200, 60 };
		objLevel2[noOfObjLevel2++] = { -1000, 160, 50, 50, 3, 0, true, true, true,
			10, 0, 500, 0, -100, 160, 1200, 160 };


		// Door
		objLevel2[noOfObjLevel2++] = { 1000, 60, 100, 100, 1, 0,
			true, false, false, 0, 0, 0,
			0, 1000, 60, 1000, 60 };
	}
}

#endif