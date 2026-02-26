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
    // Sublevel 1: "Floor is Lava" - Small jumpable platforms above
    // floor-hugging saws
    noOfObjLevel2 = 0;

    // Platforms (Width=120, Height=60 is good for jumping)
    objLevel2[noOfObjLevel2++] = {150,  100,   120,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    150,   100,   150, 100};
    objLevel2[noOfObjLevel2++] = {400,  150,   120,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    400,   150,   400, 150};
    objLevel2[noOfObjLevel2++] = {650,  100,   120,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    650,   100,   650, 100};

    // Saws moving horizontally across the floor (y=60 is floor)
    // Saw 1
    objLevel2[noOfObjLevel2++] = {0, 60, 50, 50, 3, 0,  true, true, true,
                                  8, 0,  300,  0,  0, 60, 1000, 60};
    // Saw 2 (starts from right)
    objLevel2[noOfObjLevel2++] = {1000, 60, 50, 50, 3,    0,  true, true, true,
                                  8,    0,  0,  0,  1000, 60, 0,    60};

    // Door
    /*objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
                                  true, false, false, 0,    0, 0,
                                  0,    1000,  60,    1000, 60};*/
  } else if (subLevelCount2 == 2) {
    // Sublevel 2: "The Gauntlet" - Vertical saws that trigger as you progress
    noOfObjLevel2 = 0;

    // Platforms at varying heights
    objLevel2[noOfObjLevel2++] = {200,  120,   100,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    200,   120,   200, 120};
    objLevel2[noOfObjLevel2++] = {450,  180,   100,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    450,   180,   450, 180};
    objLevel2[noOfObjLevel2++] = {700,  120,   100,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    700,   120,   700, 120};

    // Falling Saws (trigger when player gets close)
    // Saw 1 (drops when hero.x > 100)
    objLevel2[noOfObjLevel2++] = {225, 500, 50,  50, 3,   0,   true, true, true,
                                  12,  1,   100, 0,  225, 500, 225,  60};
    // Saw 2 (drops when hero.x > 350)
    objLevel2[noOfObjLevel2++] = {475, 500, 50,  50, 3,   0,   true, true, true,
                                  12,  1,   350, 0,  475, 500, 475,  60};
    // Saw 3 (drops when hero.x > 600)
    objLevel2[noOfObjLevel2++] = {725, 500, 50,  50, 3,   0,   true, true, true,
                                  12,  1,   600, 0,  725, 500, 725,  60};

    // Door
    /*objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
                                  true, false, false, 0,    0, 0,
                                  0,    1000,  60,    1000, 60};*/
  } else if (subLevelCount2 == 3) {
    // Sublevel 3: "Diagonal Death" - Crossing saws
    noOfObjLevel2 = 0;

    // Platforms
    objLevel2[noOfObjLevel2++] = {300,  150,   150,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    300,   150,   300, 150};
    objLevel2[noOfObjLevel2++] = {600,  150,   150,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    600,   150,   600, 150};

    // Diagonal Saw 1 (triggered by hero.x > 150)
    objLevel2[noOfObjLevel2++] = {0, 500, 60,  60, 3, 0,   true, true, true,
                                  7, 2,   150, 0,  0, 500, 1000, 60};
    // Diagonal Saw 2 (triggered by hero.x > 150) - Crosses the other one
    objLevel2[noOfObjLevel2++] = {1000, 500,  60,   60, 3, 0,
                                  true, true, true, 7,  2, 150,
                                  0,    1000, 500,  0,  60};

    // Door
    /*objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
                                  true, false, false, 0,    0, 0,
                                  0,    1000,  60,    1000, 60};*/
  } else if (subLevelCount2 == 4) {
    // Sublevel 4: "The Finale" - Precision Jumps + Fast Saws
    noOfObjLevel2 = 0;

    // Narrow risky platforms
    objLevel2[noOfObjLevel2++] = {200,  130,   60,    40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    200,   130,   200, 130};
    objLevel2[noOfObjLevel2++] = {400,  200,   60,    40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    400,   200,   400, 200};
    objLevel2[noOfObjLevel2++] = {600,  130,   60,    40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    600,   130,   600, 130};
    /*objLevel2[noOfObjLevel2++] = {800,  200,   60,    40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    800,   200,   800, 200};*/

    // Fast Vertical Saws guarding the jumps
    objLevel2[noOfObjLevel2++] = {300, 60, 50,  50, 3,   0,  true, true, true,
                                  15,  1,  100, 0,  300, 60, 300,  500};
    objLevel2[noOfObjLevel2++] = {500, 500, 50,  50, 3,   0,   true, true, true,
                                  15,  1,   300, 0,  500, 500, 500,  60};
    objLevel2[noOfObjLevel2++] = {700, 60, 50,  50, 3,   0,  true, true, true,
                                  15,  1,  500, 0,  700, 60, 700,  500};

    // Door
    objLevel2[noOfObjLevel2++] = {1000, 60,    100,   100,  1, 0,
                                  true, false, false, 0,    0, 0,
                                  0,    1000,  60,    1000, 60};
  }
}

#endif
