#ifndef LEVEL_H
#define LEVEL_H
#include "GameData.h"
#include "Images.h"
#include "Levelone.h"
#include "Leveltwo.h"

int noOfObj;
int obstacleHeight;
int *subLevelCount;
GameObject obj[50];
bool levelDone = false;

void levelDefining() {
  if (levelDone == true) {
    levelCount++;
    levelDone = false;
  }
  if (levelCount == 1) {
    subLevelDefining1();
    subLevelCount = &subLevelCount1;
    noOfObj = noOfObjLevel1;
    obstacleHeight = obstacleHeightLevel1;
    for (int i = 0; i < noOfObj; i++) {
      obj[i] = objLevel1[i];
    }
  } else if (levelCount == 2) {
    subLevelDefining2();
    subLevelCount = &subLevelCount2;
    noOfObj = noOfObjLevel2;
    obstacleHeight = obstacleHeightLevel2;
    for (int i = 0; i < noOfObj; i++) {
      obj[i] = objLevel2[i];
    }
  } else if (levelCount == 3) {
    currentGameState = STATE_WIN;
  }
  printf("Trigered\n");
}

#endif