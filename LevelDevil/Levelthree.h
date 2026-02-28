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
    objLevel3[noOfObjLevel3++] = {150,  100,   150,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    150,   100,   150, 100};
    // Fake Platform
    objLevel3[noOfObjLevel3++] = {400,  100,   150,   40,  4,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    400,   100,   400, 100};
    // Real again
    objLevel3[noOfObjLevel3++] = {400, 50, 150, 40, 2,   0,  true, false, false,
                                  0,   0,  0,   0,  400, 50, 400,  50};
    objLevel3[noOfObjLevel3++] = {700,  100,   150,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    700,   100,   700, 100};
    // Sawblade moving vertically
    objLevel3[noOfObjLevel3++] = {550, 150, 50, 50, 3,   0,   true, true, true,
                                  5,   1,   0,  0,  550, 150, 550,  500};

    // Door (None until subLevelCount3 == 4)
  } else if (subLevelCount3 == 2) {
    // Sublevel 2: Intro to Ghost over a long pit
    noOfObjLevel3 = 0;
    objLevel3[noOfObjLevel3++] = {150, 60, 250, 40, 2,   0,  true, false, false,
                                  0,   0,  0,   0,  150, 60, 150,  60};
    objLevel3[noOfObjLevel3++] = {600, 60, 250, 40, 2,   0,  true, false, false,
                                  0,   0,  0,   0,  600, 60, 600,  60};
    // Vertical Sawblade
    objLevel3[noOfObjLevel3++] = {400, 300, 50, 50, 3,   0,  true, true, true,
                                  8,   1,   0,  0,  400, 60, 400,  500};
    // Ghost (Proper speed)
    objLevel3[noOfObjLevel3++] = {800, 200, 50, 50, 5,   0,   true, true, true,
                                  3,   0,   0,  0,  800, 200, 800,  200};
  } else if (subLevelCount3 == 3) {
    // Sublevel 3: Ghost chasing while deducing fake platforms
    noOfObjLevel3 = 0;
    // Ghost (Proper speed)
    objLevel3[noOfObjLevel3++] = {500, 250, 50, 50, 5,   0,   true, true, true,
                                  3,   0,   0,  0,  500, 250, 500,  250};

    // Horizontal Sawblade over Fake Platform
    objLevel3[noOfObjLevel3++] = {
        350, 200, 50, 50, 3,   0,   true, true, true,
        4,   0,   0,  0,  350, 200, 600,  200}; // Real
    objLevel3[noOfObjLevel3++] = {150,  100,   100,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    150,   100,   150, 100};
    // Fake
    objLevel3[noOfObjLevel3++] = {350,  150,   100,   40,  4,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    350,   150,   350, 150};
    // Real underneath
    objLevel3[noOfObjLevel3++] = {350, 60, 100, 40, 2,   0,  true, false, false,
                                  0,   0,  0,   0,  350, 60, 350,  60};
    // Real
    objLevel3[noOfObjLevel3++] = {600,  150,   100,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    600,   150,   600, 150};
    // Real
    objLevel3[noOfObjLevel3++] = {850,  150,   100,   40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    850,   150,   850, 150};
  } else if (subLevelCount3 == 4) {
    // Sublevel 4: The Finale
    noOfObjLevel3 = 0;
    // Two Ghosts!
    // Two Ghosts! (Proper speed)
    objLevel3[noOfObjLevel3++] = {500, 250, 50, 50, 5,   0,   true, true, true,
                                  2,   0,   0,  0,  500, 250, 500,  250};
    objLevel3[noOfObjLevel3++] = {100, 300, 50, 50, 5,   0,   true, true, true,
                                  2,   0,   0,  0,  100, 300, 100,  300};

    // Fast Vertical Sawblades
    objLevel3[noOfObjLevel3++] = {300, 250, 50, 50, 3,   0,  true, true, true,
                                  10,  1,   0,  0,  300, 60, 300,  500};
    objLevel3[noOfObjLevel3++] = {
        600, 450, 50, 50, 3,   0,  true, true, true,
        8,   1,   0,  0,  600, 60, 600,  500}; // Tiny tricky platforms
    objLevel3[noOfObjLevel3++] = {200,  120,   80,    40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    200,   120,   200, 120};
    objLevel3[noOfObjLevel3++] = {400,  180,   80,    40,  4,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    400,   180,   400, 180}; // fake
    objLevel3[noOfObjLevel3++] = {500, 80, 80, 40, 2,   0,  true, false, false,
                                  0,   0,  0,  0,  500, 80, 500,  80}; // catch
    objLevel3[noOfObjLevel3++] = {750,  120,   80,    40,  2,  0,
                                  true, false, false, 0,   0,  0,
                                  0,    750,   120,   750, 120};

    // Door
    objLevel3[noOfObjLevel3++] = {1000, 60,    100,   100,  1, 0,
                                  true, false, false, 0,    0, 0,
                                  0,    1000,  60,    1000, 60};
  }
}

#endif
