#ifndef LEVELONE_H
#define LEVELONE_H
#include "GameData.h"
#include "Images.h"


int obstacleHeightLevel1 = 60;

int noOfObjLevel1;
int subLevelCount1 = 1;
GameObject obj1;
GameObject obj2;
GameObject objLevel1[50];







void subLevelDefining1() {
	if (subLevelCount1 == 1) {
		noOfObjLevel1 = 2;
		obj1 = { 300, 60, 50, 20, 0, 1, true, true, false, 0, 0, 0, 0, 300, 60, 300, 60 };
		//upto trigX
		obj2 = { 500, 60, 50, 20, 0, 1, true, true, true, 20, 0, 460, 60, 500, 60, 600, 60 };

		objLevel1[0] = obj1;
		objLevel1[1] = obj2;
	}
	else if (subLevelCount1 == 2) {
		noOfObjLevel1 = 1;
		obj1 = { 500, 60, 50, 20, 0, 1, true, true, true, 20, 0, 460, 60, 500, 60, 800, 60 };
		objLevel1[0] = obj1;
	}
}





#endif