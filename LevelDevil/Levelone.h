#ifndef LEVELONE_H
#define LEVELONE_H
#include "GameData.h"
#include "Images.h"


int obstacleHeightLevel1 = 60;

int noOfObjLevel1;
int subLevelCount1 = 1;
GameObject obj1;
GameObject obj2;
GameObject obj3;
GameObject obj4;
GameObject objLevel1[50];

void subLevelDefining1() {
	if (subLevelCount1 == 1) {
		noOfObjLevel1 = 3;
		obj1 = { 300, 60, 50, 20, 0, 1, true, true, false, 0, 0, 0, 0, 300, 60, 300, 60 };
		//upto trigX
		obj2 = { 500, 60, 50, 20, 0, 1, true, true, false, 0, 0, 0, 0, 500, 60, 500, 60 };
		obj3 = { 700, 60, 50, 20, 0, 1, true, true, true, 20, 0, 675, 60, 700, 60, 800, 60};//second last value works, and mode 

		objLevel1[0] = obj1;
		objLevel1[1] = obj2;
		objLevel1[2] = obj3;
	}
	else if (subLevelCount1 == 2) {
		noOfObjLevel1 = 3;
		obj1 = { 300, 60, 50, 20, 0, 1, true, true, true, 20, 0, 275, 60, 300, 60, 200, 60 };
		//upto trigX
		obj2 = { 500, 60, 50, 20, 0, 1, true, true, false, 0, 0, 500, 60, 500, 60, 500, 60 };
		obj3 = { 700, 60, 50, 20, 0, 1, true, true, true, 20, 0, 675, 60, 700, 60, 800, 60 };//second last value works, and mode 

		objLevel1[0] = obj1;
		objLevel1[1] = obj2;
		objLevel1[2] = obj3;
	}
	else if (subLevelCount1 == 3) {
		noOfObjLevel1 = 3;
		obj1 = { 500, 60, 50, 20, 0, 1, true, true, true, 20, 0, 400, 60, 500, 60, 350, 60 };
		//upto trigX
		obj2 = { 500, 60, 50, 20, 0, 1, true, true, false, 0, 0, 300, 60, 500, 60, 500, 60 };
		obj3 = { 700, 60, 50, 20, 0, 1, true, true, false, 20, 0, 650, 60, 700, 60, 600, 60 };//second last value works, and mode 

		objLevel1[0] = obj1;
		objLevel1[1] = obj2;
		objLevel1[2] = obj3;
	}

	else if (subLevelCount1 == 4) {
		noOfObjLevel1 = 4;
		obj1 = { 300, 60, 50, 20, 0, 1, true, true, true, 20, 0, 250, 60, 300, 60, 400, 60 };
		//upto trigX
		obj2 = { 550, 60, 50, 20, 0, 1, true, true, true, 30, 0, 700, 60, 550, 60, 800, 60 };
		obj3 = { 700, 60, 50, 20, 0, 1, true, true, true, 30, 0, 250, 60, 700, 60, 0, 60 };//second last value works, and mode 

		objLevel1[0] = obj1;
		objLevel1[1] = obj2;
		objLevel1[2] = obj3;
		

		obj4 = { 1000, 60, 100, 100, 1, 1, true, false, false, 0,0, 0,0, 1000 ,60 ,0 ,0};
		objLevel1[3] = obj4;


	}

}





#endif