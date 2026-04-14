#ifndef PHYSICS_H
#define PHYSICS_H
#include "GameData.h"
#include "Level.h"
#include <math.h>

bool jumpDone = false;
bool jumpStart = false;
bool onObj = false;
int objHeightWithBase = obstacleHeight;
int objHeight;
int curX, curY, curW, curH;

// Platform tracking: is the player standing on a type-2 platform right now?
bool onPlatform = false;
double platformTopY = 0;
// Which platform index the player is currently on (-1 = none)
int onPlatformIdx = -1;

// Returns true if two rectangles overlap
bool checkAABB(double x1, double y1, double w1, double h1, double x2, double y2,
               double w2, double h2) {
  return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

// deals with jumping
void updatePlayerPhysics(Player &p, bool isLeft) {
  // 1. Apply Gravity
  p.dy += gravity;

  // 2. Update Y Position & Check Vertical Collisions
  if (jumpDone && p.isGrounded) {
    jumpDone = false;
  }

  if (jumpDone == false) {
    p.y += p.dy;
    p.isGrounded = false;

    // Use platform top if on platform, otherwise base floor
    double curGround = onPlatform ? platformTopY : (double)obstacleHeight;

    if (p.y <= curGround) {
      p.isGrounded = true;
      p.y = curGround;
      p.dy = 15;
      jumpDone = true;
    }
  }
}

// deals with colliding with objects
void colisionDeal(Player &hero) {

  // --- Pass 1: One-Way Solid Platforms (type 2) ---
  // Reset each frame — will be set to true only if player is on a platform
  onPlatform = false;
  onPlatformIdx = -1;

  for (int i = 0; i < noOfObj; i++) {
    if (obj[i].type != 2)
      continue;
    if (!obj[i].isVisible)
      continue;

    double platTop = obj[i].y + obj[i].height;

    // Already standing on top surface
    if (hero.x + 45 > obj[i].x && hero.x + 5 < obj[i].x + obj[i].width &&
        hero.y >= platTop - 1 && hero.y <= platTop + 1) {
      hero.y = platTop;
      hero.isGrounded = true;
      jumpDone = true;
      onPlatform = true;
      platformTopY = platTop;
      onPlatformIdx = i;
      continue;
    }

    // Check AABB overlap (hero is inside the platform volume)
    if (checkAABB(hero.x, hero.y, 40, 50, obj[i].x, obj[i].y, obj[i].width,
                  obj[i].height)) {

      // TOP COLLISION: player falling onto the platform top surface
      if (hero.dy <= 0 && (hero.y - hero.dy) >= (platTop - 1) &&
          (hero.x + 45 > obj[i].x && hero.x + 5 < obj[i].x + obj[i].width)) {
        hero.y = platTop;
        hero.dy = 0;
        hero.isGrounded = true;
        jumpDone = true;
        onPlatform = true;
        platformTopY = platTop;
        onPlatformIdx = i;
      }
      // SIDE COLLISION (levels 1-4: solid walls) / (level 5: one-way, pass through)
      else if (levelCount != 5) {
        if (hero.dx > 0 && (hero.x + 50) > obj[i].x &&
            (hero.x + 50) < obj[i].x + 20)
          hero.x = obj[i].x - 50;
        else if (hero.dx < 0 && hero.x < (obj[i].x + obj[i].width) &&
                 hero.x > (obj[i].x + obj[i].width - 20))
          hero.x = obj[i].x + obj[i].width;
      }
      // Level 5: no side blocking – hero passes through from below/sides.
    }
  }


  // --- Pass 2: Orb Pickup (type 7), Spikes, Doors, Sawblades, Ghosts ---
  for (int i = 0; i < noOfObj; i++) {
    if (obj[i].type == 2 || obj[i].type == 4 || obj[i].type == 6)
      continue; // platforms or fake decoys — skip

    if (!obj[i].isVisible)
      continue;

    // ORB PICKUP
    if (obj[i].type == 7) {
      if (checkAABB(hero.x, hero.y, 40, 50, obj[i].x, obj[i].y,
                    obj[i].width, obj[i].height)) {
        obj[i].isVisible = false;  // orb disappears
        shieldActive = true;
        shieldStartTime = clock();
      }
      continue;
    }

    if (checkAABB(hero.x, hero.y, 40, 50, obj[i].x, obj[i].y, obj[i].width,
                  obj[i].height)) {

      // SHIELD IMMUNITY: lethal objects are ignored while shield is active
      if (obj[i].willKill) {
        if (!shieldActive) {
          hero.isDying = true;
        }
        break;
      }

      if (obj[i].type == 1) {
        levelDone = true;
        break;
      }

      if (hero.x + 45 > obj[i].x && hero.x + 5 < obj[i].x + obj[i].width) {
        onObj = true;
        objHeight = obj[i].height;
      } else {
        onObj = false;
      }

      // TOP COLLISION (Landing on a moving trap top)
      if (hero.dy <= 0 &&
          (hero.y - hero.dy) >= (obj[i].y + obj[i].height - 5) &&
          (hero.x + 45 > obj[i].x && hero.x + 5 < obj[i].x + obj[i].width)) {
        hero.y = obj[i].y + obj[i].height;
        hero.dy = 0;
        jumpDone = true;
        onObj = true;
        objHeightWithBase = obj[i].height + obstacleHeight;
        objHeight = obj[i].height;
        curX = obj[i].x;
        curY = obj[i].y;
        curW = obj[i].width;
        curH = obj[i].height;
      }
      // SIDE COLLISION
      else {
        onObj = false;
        if (hero.dx > 0 && (hero.x + 50) > obj[i].x &&
            (hero.x + 50) < obj[i].x + 20)
          hero.x = obj[i].x - 50;
        else if (hero.dx > 0 && hero.x < (obj[i].x + obj[i].width) &&
                 hero.x > (obj[i].x + obj[i].width - 20))
          hero.x = obj[i].x + obj[i].width;
      }
    }
  }

  // Keep track of moving-trap standing (original curX/curY logic)
  if (checkAABB(hero.x, hero.y, 50, 50, curX, curY, curW, curH)) {
    if (hero.dy <= 0 && (hero.y - hero.dy) >= (curY + curH - 5) &&
        (hero.x + 45 > curX && hero.x + 5 < curX + curW)) {
      onObj = true;
    }
  } else {
    onObj = false;
  }

  if (onObj) {
    obstacleHeight = objHeightWithBase;
  } else if (!onObj && obstacleHeight == objHeightWithBase) {
    obstacleHeight -= objHeight;
  }
}

// ---------------------------------------------------------------------------
// Moving Platform Physics (Level 5 only)
// Oscillates the platform endlessly between (innitialX,innitialY) and
// (finX,finY).  Uses trap.state as a direction flag:
//   state == 0  →  moving toward fin
//   state == 1  →  moving back toward initial
// The hero carry logic mirrors triggerTrap's type-2 carry exactly.
// ---------------------------------------------------------------------------
void triggerMovingPlatform(GameObject &trap, Player &hero) {
  if (!trap.willMove || trap.type != 2)
    return;

  double oldX = trap.x;
  double oldY = trap.y;

  // --- Horizontal oscillation ---
  if (trap.mode == 0 || trap.mode == 2) {
    if (trap.state == 0) {
      // Moving toward finX
      trap.x += trap.speed;
      if (trap.x >= trap.finX) {
        trap.x = trap.finX;
        trap.state = 1; // reverse
      }
    } else {
      // Moving back toward innitialX
      trap.x -= trap.speed;
      if (trap.x <= trap.innitialX) {
        trap.x = trap.innitialX;
        trap.state = 0; // reverse
      }
    }
  }

  // --- Vertical oscillation ---
  if (trap.mode == 1 || trap.mode == 2) {
    if (trap.state == 0) {
      // Moving toward finY
      trap.y += trap.speed;
      if (trap.y >= trap.finY) {
        trap.y = trap.finY;
        trap.state = 1; // reverse
      }
    } else {
      // Moving back toward innitialY
      trap.y -= trap.speed;
      if (trap.y <= trap.innitialY) {
        trap.y = trap.innitialY;
        trap.state = 0; // reverse
      }
    }
  }

  // --- Player carry (identical to triggerTrap type-2 carry) ---
  double deltaX = trap.x - oldX;
  double deltaY = trap.y - oldY;

  if ((deltaX != 0 || deltaY != 0) &&
      onPlatformIdx >= 0 && &obj[onPlatformIdx] == &trap) {
    hero.x += deltaX;
    hero.y += deltaY;
    platformTopY += deltaY;
  }
}

// trap moving
void triggerTrap(GameObject &trap, Player &hero) {
  if (!trap.willMove)
    return;

  // Homing Ghost Logic
  if (trap.type == 5) {
    double distX = hero.x - trap.x;
    double distY = hero.y - trap.y;
    double distance = sqrt(distX * distX + distY * distY);

    if (distance > 0) {
      trap.x += (distX / distance) * (double)trap.speed;
      trap.y += (distY / distance) * (double)trap.speed;
    }
    return;
  }

  // Standard moving traps (Sawblades, Platforms, Doors)
  double oldX = trap.x;
  double oldY = trap.y;

  if (hero.x > trap.trigX) {
    if (trap.mode == 0 || trap.mode == 2) {
      if (trap.x < trap.finX) {
        trap.x += trap.speed;
        if (trap.x > trap.finX) trap.x = trap.finX;
      } else if (trap.x > trap.finX) {
        trap.x -= trap.speed;
        if (trap.x < trap.finX) trap.x = trap.finX;
      }
    }

    if (trap.mode == 1 || trap.mode == 2) {
      if (trap.y < trap.finY) {
        trap.y += trap.speed;
        if (trap.y > trap.finY) trap.y = trap.finY;
      } else if (trap.y > trap.finY) {
        trap.y -= trap.speed;
        if (trap.y < trap.finY) trap.y = trap.finY;
      }
    }
  }



  // PLATFORM CARRY LOGIC
  double deltaX = trap.x - oldX;
  double deltaY = trap.y - oldY;

  if (deltaX != 0 || deltaY != 0) {
    // --- Type 2 (one-way platform) carry ---
    if (trap.type == 2 && onPlatformIdx >= 0 && &obj[onPlatformIdx] == &trap) {
      hero.x += deltaX;
      hero.y += deltaY;
      platformTopY += deltaY;
    }
    // --- Other moving traps carry (sawblades, etc.) ---
    else if (onObj && hero.dy == 0 &&
             (hero.y >= trap.y + trap.height - 5) &&
             (hero.x + 45 > trap.x && hero.x + 5 < trap.x + trap.width)) {
      hero.x += deltaX;
      hero.y += deltaY;
    }
  }
}
#endif