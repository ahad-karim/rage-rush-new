#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include "GameData.h"
#include "Images.h"

int obstacleHeightLevel4 = 60;
int noOfObjLevel4;
int subLevelCount4 = 1;
GameObject objLevel4[50];

// Darkness mechanic settings
int darknessTriggerX = 200;   // x-coordinate that activates darkness
int darknessRadius = 80;      // radius of visible spotlight circle

void subLevelDefining4() {
  if (subLevelCount4 == 1) {
    // Sublevel 1: Spikes + platforms, gentle intro into darkness
    noOfObjLevel4 = 0;

    // Platform 1
    objLevel4[noOfObjLevel4++] = {250, 60, 150, 50, 2, 0,
        true, false, false, 0, 0, 0,
        0, 250, 60, 250, 60};

    // Platform 2
    objLevel4[noOfObjLevel4++] = {550, 60, 150, 80, 2, 0,
        true, false, false, 0, 0, 0,
        0, 550, 60, 550, 60};

    // Spike on ground
    objLevel4[noOfObjLevel4++] = {400, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 400, 60, 400, 60};

    // Spike on ground
    objLevel4[noOfObjLevel4++] = {700, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 700, 60, 700, 60};

    // Spike moving
    objLevel4[noOfObjLevel4++] = {850, 60, 50, 20, 0, 1,
        true, true, true, 15, 0, 500, 60,
        850, 60, 750, 60};
  }
  else if (subLevelCount4 == 2) {
    // Sublevel 2: Sawblades + platforms, tighter spacing
    noOfObjLevel4 = 0;

    // Platforms
    objLevel4[noOfObjLevel4++] = {200, 60, 100, 50, 2, 0,
        true, false, false, 0, 0, 0,
        0, 200, 60, 200, 60};

    objLevel4[noOfObjLevel4++] = {500, 60, 100, 80, 2, 0,
        true, false, false, 0, 0, 0,
        0, 500, 60, 500, 60};

    objLevel4[noOfObjLevel4++] = {750, 60, 100, 50, 2, 0,
        true, false, false, 0, 0, 0,
        0, 750, 60, 750, 60};

    // Sawblade on floor
    objLevel4[noOfObjLevel4++] = {-100, 60, 50, 50, 3, 0,
        true, true, true, 8, 0, 300, 60,
        -100, 60, 1100, 60};

    // Spike
    objLevel4[noOfObjLevel4++] = {400, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 400, 60, 400, 60};

    // Spike
    objLevel4[noOfObjLevel4++] = {650, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 650, 60, 650, 60};
  }
  else if (subLevelCount4 == 3) {
    // Sublevel 3: Fake platforms + sawblades + spikes
    noOfObjLevel4 = 0;

    // Real platform
    objLevel4[noOfObjLevel4++] = {200, 60, 120, 50, 2, 0,
        true, false, false, 0, 0, 0,
        0, 200, 60, 200, 60};

    // Fake platform (type 4) - looks like platform but falls
    objLevel4[noOfObjLevel4++] = {400, 60, 120, 50, 4, 0,
        true, false, false, 0, 0, 0,
        0, 400, 60, 400, 60};

    // Real platform
    objLevel4[noOfObjLevel4++] = {600, 60, 120, 70, 2, 0,
        true, false, false, 0, 0, 0,
        0, 600, 60, 600, 60};

    // Fake platform
    objLevel4[noOfObjLevel4++] = {800, 60, 120, 50, 4, 0,
        true, false, false, 0, 0, 0,
        0, 800, 60, 800, 60};

    // Spikes between platforms
    objLevel4[noOfObjLevel4++] = {330, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 330, 60, 330, 60};

    objLevel4[noOfObjLevel4++] = {530, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 530, 60, 530, 60};

    // Sawblade
    objLevel4[noOfObjLevel4++] = {-100, 60, 50, 50, 3, 0,
        true, true, true, 10, 0, 450, 60,
        -100, 60, 1200, 60};
  }
  else if (subLevelCount4 == 4) {
    // Sublevel 4: All traps combined + door
    noOfObjLevel4 = 0;

    // Platforms
    objLevel4[noOfObjLevel4++] = {180, 60, 80, 50, 2, 0,
        true, false, false, 0, 0, 0,
        0, 180, 60, 180, 60};

    objLevel4[noOfObjLevel4++] = {380, 60, 80, 80, 2, 0,
        true, false, false, 0, 0, 0,
        0, 380, 60, 380, 60};

    // Fake platform
    objLevel4[noOfObjLevel4++] = {560, 60, 80, 50, 4, 0,
        true, false, false, 0, 0, 0,
        0, 560, 60, 560, 60};

    objLevel4[noOfObjLevel4++] = {720, 60, 80, 60, 2, 0,
        true, false, false, 0, 0, 0,
        0, 720, 60, 720, 60};

    // Spikes
    objLevel4[noOfObjLevel4++] = {280, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 280, 60, 280, 60};

    objLevel4[noOfObjLevel4++] = {480, 60, 50, 20, 0, 1,
        true, true, true, 15, 0, 450, 60,
        480, 60, 600, 60};

    objLevel4[noOfObjLevel4++] = {650, 60, 50, 20, 0, 1,
        true, true, false, 0, 0, 0,
        0, 650, 60, 650, 60};

    // Sawblades
    objLevel4[noOfObjLevel4++] = {-100, 60, 50, 50, 3, 0,
        true, true, true, 10, 0, 200, 60,
        -100, 60, 1200, 60};

    objLevel4[noOfObjLevel4++] = {1200, 130, 50, 50, 3, 0,
        true, true, true, 8, 0, 500, 60,
        1200, 130, -100, 130};

    // Door
    objLevel4[noOfObjLevel4++] = {1000, 60, 100, 100, 1, 0,
        true, false, false, 0, 0, 0,
        0, 1000, 60, 1000, 60};
  }
}

#endif
