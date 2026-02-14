#ifndef LEVELONE_H
#define LEVELONE_H
#include "GameData.h"
#include "Images.h"


int obstacleHeightLevel1 = 60;

int noOfObjLevel1 = 2;

GameObject obj1 = { 300, 60, 50, 20, 0, 1, true, true, false, 0, 0, 0, 0, 300, 60, 300, 60 };
//upto trigX
GameObject obj2 = { 500, 60, 50, 20, 0, 1, true, true, true, 20, 0, 460, 60,500,60, 600, 60 };

GameObject objLevel1[] = { obj1, obj2 };


void drawBase() {
	
}





#endif