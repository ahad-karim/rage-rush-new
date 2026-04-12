#ifndef LEVELFIVE_H
#define LEVELFIVE_H

#include "GameData.h"

// Type 0=Spike, 1=Door, 2=Platform, 3=Sawblade, 4=Fake Platform,
//       5=Ghost, 6=Fake Door, 7=Orb
//
// Struct layout (positional init):
// { x, y, width, height, type, state, isVisible, willKill, willMove,
//   speed, mode, trigX, trigY, innitialX, innitialY, finX, finY }
//
// Traps move from (innitialX,innitialY) toward (finX,finY) once and stop.
// trigX == -200 → always active (hero.x is always > -200)

extern int subLevelCount5;

// ---------------------------------------------------------------------------
// SUBLEVEL 1 – Vertical Elevators + Orb introduction
// ---------------------------------------------------------------------------
void levelfiveS1(Level &level) {
  level.objectCount = 0;

  // Ground base (static)
  level.objects[level.objectCount++] = {0,   -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0,   0, -60,   0, -60};

  // Starting safe platform
  level.objects[level.objectCount++] = {0,    20, 130,  20, 2, 0, true, false, false, 0, 0, 0, 0,   0,  20,   0,  20};

  // Orb sitting on the starting platform
  level.objects[level.objectCount++] = {50,   55,  30,  30, 7, 0, true, false, false, 0, 0, 0, 0,  50,  55,  50,  55};

  // Elevator 1 – moves up (y=20 → y=110) once
  level.objects[level.objectCount++] = {210,  20, 120,  20, 2, 0, true, false, true,  3, 1, -200, 0, 210, 20, 210, 110};

  // Static landing ledge
  level.objects[level.objectCount++] = {390, 100, 100,  20, 2, 0, true, false, false, 0, 0, 0, 0, 390, 100, 390, 100};

  // Elevator 2 – moves up (y=20 → y=100) once
  level.objects[level.objectCount++] = {560,  20, 120,  20, 2, 0, true, false, true,  4, 1, -200, 0, 560, 20, 560, 100};

  // Static landing ledge 2
  level.objects[level.objectCount++] = {740,  90, 100,  20, 2, 0, true, false, false, 0, 0, 0, 0, 740, 90, 740, 90};

  // Exit door – slides right once to make player time the touch
  level.objects[level.objectCount++] = {740, 110,  50,  60, 1, 0, true, false, true,  2, 0, -200, 0, 740, 110, 820, 110};

  // Ground spikes between platforms
  level.objects[level.objectCount++] = {140,  20, 60,  20, 0, 0, true, true,  false, 0, 0, 0, 0, 140, 20, 140, 20};
  level.objects[level.objectCount++] = {340,  20, 60,  20, 0, 0, true, true,  false, 0, 0, 0, 0, 340, 20, 340, 20};
  level.objects[level.objectCount++] = {500,  20, 50,  20, 0, 0, true, true,  false, 0, 0, 0, 0, 500, 20, 500, 20};
  level.objects[level.objectCount++] = {690,  20, 50,  20, 0, 0, true, true,  false, 0, 0, 0, 0, 690, 20, 690, 20};
}

// ---------------------------------------------------------------------------
// SUBLEVEL 2 – Horizontal Sliding Platforms
// ---------------------------------------------------------------------------
void levelfiveS2(Level &level) {
  level.objectCount = 0;

  // Ground base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, -60, 0, -60};

  // Starting safe platform
  level.objects[level.objectCount++] = {0, 20, 120, 20, 2, 0, true, false, false, 0, 0, 0, 0, 0, 20, 0, 20};

  // Horizontal slider 1 – moves right once (x=150 → x=400)
  level.objects[level.objectCount++] = {150, 20, 120, 20, 2, 0, true, false, true, 3, 0, -200, 0, 150, 20, 400, 20};

  // Orb on a mid-height static perch
  level.objects[level.objectCount++] = {440, 90, 30, 30, 7, 0, true, false, false, 0, 0, 0, 0, 440, 90, 440, 90};

  // Static perch to place orb on
  level.objects[level.objectCount++] = {420, 70, 80, 20, 2, 0, true, false, false, 0, 0, 0, 0, 420, 70, 420, 70};

  // Horizontal slider 2 – moves right once (x=300 → x=650)
  level.objects[level.objectCount++] = {300, 110, 130, 20, 2, 0, true, false, true, 4, 0, -200, 0, 300, 110, 650, 110};

  // Static platform at far right to rest before door
  level.objects[level.objectCount++] = {800, 80, 150, 20, 2, 0, true, false, false, 0, 0, 0, 0, 800, 80, 800, 80};

  // Exit door – slides right once
  level.objects[level.objectCount++] = {800, 100, 50, 60, 1, 0, true, false, true, 2, 0, -200, 0, 800, 100, 900, 100};

  // Spikes on ground
  level.objects[level.objectCount++] = {125,  20, 20, 20, 0, 0, true, true, false, 0, 0, 0, 0, 125,  20, 125,  20};
  level.objects[level.objectCount++] = {280,  20, 20, 20, 0, 0, true, true, false, 0, 0, 0, 0, 280,  20, 280,  20};
  level.objects[level.objectCount++] = {570,  20, 60, 20, 0, 0, true, true, false, 0, 0, 0, 0, 570,  20, 570,  20};
  level.objects[level.objectCount++] = {700,  20, 90, 20, 0, 0, true, true, false, 0, 0, 0, 0, 700,  20, 700,  20};
}

// ---------------------------------------------------------------------------
// SUBLEVEL 3 – Mixed heights + fast platforms + sawblade
// ---------------------------------------------------------------------------
void levelfiveS3(Level &level) {
  level.objectCount = 0;

  // Ground base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, -60, 0, -60};

  // Starting platform
  level.objects[level.objectCount++] = {0, 20, 100, 20, 2, 0, true, false, false, 0, 0, 0, 0, 0, 20, 0, 20};

  // Orb just above starting platform (jump to grab)
  level.objects[level.objectCount++] = {30, 80, 30, 30, 7, 0, true, false, false, 0, 0, 0, 0, 30, 80, 30, 80};

  // Fast Y-elevator – moves up once (y=20 → y=120)
  level.objects[level.objectCount++] = {160, 20, 100, 20, 2, 0, true, false, true, 5, 1, -200, 0, 160, 20, 160, 120};

  // Wide horizontal slider – moves right once (x=320 → x=620)
  level.objects[level.objectCount++] = {320, 90, 120, 20, 2, 0, true, false, true, 3, 0, -200, 0, 320, 90, 620, 90};

  // Y-elevator 2 – moves up once (y=20 → y=90)
  level.objects[level.objectCount++] = {680, 20, 100, 20, 2, 0, true, false, true, 4, 1, -200, 0, 680, 20, 680, 90};

  // Final landing ledge
  level.objects[level.objectCount++] = {840, 100, 120, 20, 2, 0, true, false, false, 0, 0, 0, 0, 840, 100, 840, 100};

  // Exit door – slides right once
  level.objects[level.objectCount++] = {840, 120, 50, 60, 1, 0, true, false, true, 2, 0, -200, 0, 840, 120, 920, 120};

  // Sawblade patrolling the ground
  level.objects[level.objectCount++] = {110, 20, 45, 45, 3, 0, true, true, true, 5, 0, -200, 0, 110, 20, 820, 20};

  // Spikes
  level.objects[level.objectCount++] = {110, 20, 40, 20, 0, 0, true, true, false, 0, 0, 0, 0, 110, 20, 110, 20};
  level.objects[level.objectCount++] = {270, 20, 40, 20, 0, 0, true, true, false, 0, 0, 0, 0, 270, 20, 270, 20};
  level.objects[level.objectCount++] = {630, 20, 40, 20, 0, 0, true, true, false, 0, 0, 0, 0, 630, 20, 630, 20};
}

// ---------------------------------------------------------------------------
// SUBLEVEL 4 – Finale: platforms + moving doors + dual sawblades
// ---------------------------------------------------------------------------
void levelfiveS4(Level &level) {
  level.objectCount = 0;

  // Ground base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, -60, 0, -60};

  // Starting platform
  level.objects[level.objectCount++] = {0, 20, 120, 20, 2, 0, true, false, false, 0, 0, 0, 0, 0, 20, 0, 20};

  // Orb on starting platform (shield powerup)
  level.objects[level.objectCount++] = {45, 55, 30, 30, 7, 0, true, false, false, 0, 0, 0, 0, 45, 55, 45, 55};

  // Long horizontal slider – moves right once (x=150 → x=600)
  level.objects[level.objectCount++] = {150, 20, 140, 20, 2, 0, true, false, true, 3, 0, -200, 0, 150, 20, 600, 20};

  // Y-elevator – moves up once (y=20 → y=100)
  level.objects[level.objectCount++] = {640, 20, 110, 20, 2, 0, true, false, true, 4, 1, -200, 0, 640, 20, 640, 100};

  // Final platform
  level.objects[level.objectCount++] = {800, 100, 200, 20, 2, 0, true, false, false, 0, 0, 0, 0, 800, 100, 800, 100};

  // Moving exit door – slides right once
  level.objects[level.objectCount++] = {800, 120, 50, 60, 1, 0, true, false, true, 3, 0, -200, 0, 800, 120, 950, 120};

  // Sawblade 1: sweeps low across the ground gap
  level.objects[level.objectCount++] = {140, 20, 45, 45, 3, 0, true, true, true, 6, 0, -200, 0, 140, 20, 790, 20};

  // Sawblade 2: sweeps at mid-height (opposite direction)
  level.objects[level.objectCount++] = {790, 70, 45, 45, 3, 0, true, true, true, 5, 0, -200, 0, 790, 70, 140, 70};

  // Ground spikes
  level.objects[level.objectCount++] = {120, 20, 20, 20, 0, 0, true, true, false, 0, 0, 0, 0, 120, 20, 120, 20};
  level.objects[level.objectCount++] = {300, 20, 60, 20, 0, 0, true, true, false, 0, 0, 0, 0, 300, 20, 300, 20};
  level.objects[level.objectCount++] = {520, 20, 60, 20, 0, 0, true, true, false, 0, 0, 0, 0, 520, 20, 520, 20};
  level.objects[level.objectCount++] = {750, 20, 40, 20, 0, 0, true, true, false, 0, 0, 0, 0, 750, 20, 750, 20};
}

void levelfive(Level &level) {
  if      (subLevelCount5 == 1) levelfiveS1(level);
  else if (subLevelCount5 == 2) levelfiveS2(level);
  else if (subLevelCount5 == 3) levelfiveS3(level);
  else if (subLevelCount5 == 4) levelfiveS4(level);
}

#endif
