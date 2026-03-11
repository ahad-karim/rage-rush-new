#ifndef LEVELFIVE_H
#define LEVELFIVE_H

#include "GameData.h"

// Define elements for Level 5
// Type 0=Spike, 1=Door, 2=Platform, 3=Sawblade, 4=Fake Platform, 5=Ghost, 6=Fake Door

extern int subLevelCount5; // Defined in Level.h

void levelfiveS1(Level &level) {
  level.objectCount = 0;

  // Base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Moving Platform acting as elevator (Y-axis)
  level.objects[level.objectCount++] = {150, 20, 150, 40, 2, 0, true, false, true, 3, 1, 0, 0, 150, 20, 150, 350};

  // Moving Platform (X-axis)
  level.objects[level.objectCount++] = {350, 350, 150, 40, 2, 0, true, false, true, 4, 0, 0, 0, 350, 350, 800, 350};

  // Safe landing zone
  level.objects[level.objectCount++] = {900, 350, 150, 40, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Exit Door
  level.objects[level.objectCount++] = {950, 390, 50, 60, 1, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Pit of Spikes below everything
  for (int i = 0; i < 10; i++) {
    level.objects[level.objectCount++] = {(double)(100 + i * 100), 20, 100, 40, 0, 0, true, true, false, 0, 0, 0, 0, 0, 0, 0};
  }
}

void levelfiveS2(Level &level) {
  level.objectCount = 0;

  // Base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Starting platform
  level.objects[level.objectCount++] = {0, 20, 200, 40, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Moving Platform (X-axis) back and forth slowly
  level.objects[level.objectCount++] = {250, 150, 150, 40, 2, 0, true, false, true, 2, 0, 0, 0, 250, 150, 600, 150};

  // Fake Platform (looks safe, but isn't)
  level.objects[level.objectCount++] = {400, 250, 150, 40, 4, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};
  
  // High Moving Platform
  level.objects[level.objectCount++] = {600, 350, 150, 40, 2, 0, true, false, true, 3, 0, 0, 0, 600, 350, 900, 350};

  // Exit Door
  level.objects[level.objectCount++] = {950, 390, 50, 60, 1, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Floor Spikes
  for (int i = 0; i < 9; i++) {
    level.objects[level.objectCount++] = {(double)(200 + i * 100), 20, 100, 40, 0, 0, true, true, false, 0, 0, 0, 0, 0, 0, 0};
  }
}

void levelfiveS3(Level &level) {
  level.objectCount = 0;

  // Base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Start Platform
  level.objects[level.objectCount++] = {0, 20, 150, 40, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Fast moving Sawblade on the ground waiting
  level.objects[level.objectCount++] = {150, 20, 50, 50, 3, 0, true, true, true, 5, 0, 100, 0, 150, 20, 1000, 20};

  // Series of Y-axis moving platforms (Elevators)
  level.objects[level.objectCount++] = {200, 20, 100, 40, 2, 0, true, false, true, 4, 1, 0, 0, 200, 20, 200, 450};
  level.objects[level.objectCount++] = {400, 450, 100, 40, 2, 0, true, false, true, 6, 1, 0, 0, 400, 20, 400, 450};
  level.objects[level.objectCount++] = {600, 20, 100, 40, 2, 0, true, false, true, 5, 1, 0, 0, 600, 20, 600, 450};
  level.objects[level.objectCount++] = {800, 450, 100, 40, 2, 0, true, false, true, 7, 1, 0, 0, 800, 20, 800, 450};

  // High Goal Platform
  level.objects[level.objectCount++] = {950, 300, 150, 40, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Exit Door
  level.objects[level.objectCount++] = {1000, 340, 50, 60, 1, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};
}

void levelfiveS4(Level &level) {
  // FINALE: Fake doors and Moving doors
  level.objectCount = 0;

  // Base
  level.objects[level.objectCount++] = {0, -60, 1080, 80, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Start Platform
  level.objects[level.objectCount++] = {0, 20, 200, 40, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Moving Platform (X-axis) across a huge gap
  level.objects[level.objectCount++] = {220, 200, 200, 40, 2, 0, true, false, true, 3, 0, 0, 0, 220, 200, 800, 200};

  // Fake Doors hovering in mid air to confuse the player while riding the platform
  level.objects[level.objectCount++] = {300, 350, 50, 60, 6, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};
  level.objects[level.objectCount++] = {500, 350, 50, 60, 6, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};
  level.objects[level.objectCount++] = {700, 350, 50, 60, 6, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Ground Spikes
  for (int i = 0; i < 9; i++) {
    level.objects[level.objectCount++] = {(double)(200 + i * 100), 20, 100, 40, 0, 0, true, true, false, 0, 0, 0, 0, 0, 0, 0};
  }

  // End Platform
  level.objects[level.objectCount++] = {900, 200, 180, 40, 2, 0, true, false, false, 0, 0, 0, 0, 0, 0, 0};

  // Real, Moving Door! Moves back and forth along the end platform
  level.objects[level.objectCount++] = {900, 240, 50, 60, 1, 0, true, false, true, 2, 0, 0, 0, 900, 240, 1000, 240};
}

void levelfive(Level &level) {
  if (subLevelCount5 == 1)
    levelfiveS1(level);
  else if (subLevelCount5 == 2)
    levelfiveS2(level);
  else if (subLevelCount5 == 3)
    levelfiveS3(level);
  else if (subLevelCount5 == 4)
    levelfiveS4(level);
}

#endif
