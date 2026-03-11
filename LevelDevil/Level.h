#ifndef LEVEL_H
#define LEVEL_H
#include "GameData.h"
#include "Images.h"
#include "Levelone.h"
#include "Levelthree.h"
#include "Leveltwo.h"
#include "Levelfour.h"
#include "Levelfive.h"

int noOfObjLevel5 = 0; // Updated by Levelfive.h dynamically
int obstacleHeightLevel5 = 20;
int subLevelCount5 = 1;
GameObject objLevel5[50];


int noOfObj;
int obstacleHeight;
int *subLevelCount;
GameObject obj[50];
bool levelDone = false;

void levelDefining() {
  if (levelDone == true) {
    levelCount++;
    levelDone = false;
    rageDeaths = 0;
    
    // Update player stats and save
    if (currentPlayerIndex >= 0 && currentPlayerIndex < totalPlayers) {
      allPlayers[currentPlayerIndex].level = levelCount;
      saveGameData();
    }
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
    subLevelDefining3();
    subLevelCount = &subLevelCount3;
    noOfObj = noOfObjLevel3;
    obstacleHeight = obstacleHeightLevel3;
    for (int i = 0; i < noOfObj; i++) {
      obj[i] = objLevel3[i];
    }
  } else if (levelCount == 4) {
    subLevelDefining4();
    subLevelCount = &subLevelCount4;
    noOfObj = noOfObjLevel4;
    obstacleHeight = obstacleHeightLevel4;
    for (int i = 0; i < noOfObj; i++) {
      obj[i] = objLevel4[i];
    }
  } else if (levelCount == 5) {
    Level levelObj; // Need an instance to pass in
    levelfive(levelObj);
    subLevelCount = &subLevelCount5;
    noOfObj = levelObj.objectCount;
    obstacleHeight = obstacleHeightLevel5;
    for (int i = 0; i < noOfObj; i++) {
      obj[i] = levelObj.objects[i];
    }
  } else if (levelCount == 6) {
    currentGameState = STATE_WIN;
  }
  printf("Trigered\n");
}

#endif