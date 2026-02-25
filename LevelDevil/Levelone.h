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
    // noOfObjLevel1 = 5:  2 platforms (type 2) + 3 spikes/traps
    noOfObjLevel1 = 5;

    // plat1: x=150, base y=60, width=200, height=60  -> top surface at y=120
    GameObject plat1 = {150, 60, 200, 60, 2,   0,  true, false, false,
                        0,   0,  0,   0,  150, 60, 150,  60};
    // plat2: x=550, base y=60, width=200, height=100 -> top surface at y=160
    // (higher step)
    GameObject plat2 = {550, 60, 200, 100, 2,   0,  true, false, false,
                        0,   0,  0,   0,   550, 60, 550,  60};

    // --- Spike traps (positioned to sit exactly ON the platforms) ---
    obj1 = {300, 60, 50, 20, 0,   1,   true, true, false,
            0,   0,   0,  0,  300, 120, 300,  60};
    obj2 = {600, 60, 50, 20, 0,   1,   true, true, false,
            0,   0,   0,  0,  600, 160, 600,  60};
    obj3 = {700, 60, 50,  20, 0,   1,  true, true, true,
            20,  0,  675, 60, 700, 60, 800,  60};

    objLevel1[0] = plat1;
    objLevel1[1] = plat2;
    objLevel1[2] = obj1;
    objLevel1[3] = obj2;
    objLevel1[4] = obj3;
  } else if (subLevelCount1 == 2) {
    noOfObjLevel1 = 3;
    obj1 = {300, 60, 50,  20, 0,   1,  true, true, true,
            20,  0,  275, 60, 300, 60, 200,  60};
    // upto trigX
    obj2 = {500, 60, 50,  20, 0,   1,  true, true, false,
            0,   0,  500, 60, 500, 60, 500,  60};
    obj3 = {700, 60, 50,  20, 0,   1,  true, true, true,
            20,  0,  675, 60, 700, 60, 800,  60}; // second last value works,
                                                  // and mode

    objLevel1[0] = obj1;
    objLevel1[1] = obj2;
    objLevel1[2] = obj3;
  } else if (subLevelCount1 == 3) {
    noOfObjLevel1 = 3;
    obj1 = {500, 60, 50,  20, 0,   1,  true, true, true,
            20,  0,  400, 60, 500, 60, 350,  60};
    // upto trigX
    obj2 = {500, 60, 50,  20, 0,   1,  true, true, false,
            0,   0,  300, 60, 500, 60, 500,  60};
    obj3 = {700, 60, 50,  20, 0,   1,  true, true, false,
            20,  0,  650, 60, 700, 60, 600,  60}; // second last value works,
                                                  // and mode

    objLevel1[0] = obj1;
    objLevel1[1] = obj2;
    objLevel1[2] = obj3;
  }

  else if (subLevelCount1 == 4) {
    noOfObjLevel1 = 4;
    obj1 = {300, 60, 50,  20, 0,   1,  true, true, true,
            20,  0,  250, 60, 300, 60, 400,  60};
    // upto trigX
    obj2 = {550, 60, 50,  20, 0,   1,  true, true, true,
            30,  0,  700, 60, 550, 60, 800,  60};
    obj3 = {700, 60, 50,  20, 0,   1,  true, true, true,
            30,  0,  250, 60, 700, 60, 0,    60}; // second last value works,
                                                  // and mode

    objLevel1[0] = obj1;
    objLevel1[1] = obj2;
    objLevel1[2] = obj3;

    obj4 = {1000, 60, 100, 100, 1,    1,  true, false, false,
            0,    0,  0,   0,   1000, 60, 0,    0};
    objLevel1[3] = obj4;
  }
}

#endif