#ifndef PHYSICS_H
#define PHYSICS_H
#include "GameData.h"
#include "Level.h"

bool jumpDone = false;
bool jumpStart = false;
bool onObj = false;
int objHeightWithBase = obstacleHeight;
int objHeight;
int curX, curY, curW, curH;

// Platform tracking: is the player standing on a type-2 platform right now?
bool onPlatform = false;
double platformTopY = 0;

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

  // --- Pass 1: Solid Platforms (type 2) ---
  // Reset each frame — will be set to true only if player is on a platform
  onPlatform = false;

  for (int i = 0; i < noOfObj; i++) {
    if (obj[i].type != 2)
      continue;
    if (!obj[i].isVisible)
      continue;

    double platTop = obj[i].y + obj[i].height;

    // Check if hero is already standing on this platform's surface
    // (hero.y is at or very close to the top, and horizontally within bounds)
    if (hero.x + 45 > obj[i].x && hero.x + 5 < obj[i].x + obj[i].width &&
        hero.y >= platTop - 1 && hero.y <= platTop + 1) {
      hero.y = platTop;
      hero.isGrounded = true;
      jumpDone = true;
      onPlatform = true;
      platformTopY = platTop;
      continue;
    }

    // Check AABB overlap (hero is inside the platform volume)
    if (checkAABB(hero.x, hero.y, 40, 50, obj[i].x, obj[i].y, obj[i].width,
                  obj[i].height)) {

      // TOP COLLISION: player falling onto the platform top surface
      if (hero.dy <= 0 && (hero.y - hero.dy) >= (platTop - 1) &&
          (hero.x + 45 > obj[i].x && hero.x + 5 < obj[i].x + obj[i].width)) {
        hero.y = platTop;
        hero.dy = 0; // Don't set to 15 (that's jump velocity — causes floating)
        hero.isGrounded = true;
        jumpDone = true;
        onPlatform = true;
        platformTopY = platTop;
      }
      // SIDE COLLISION: block horizontal clipping into the platform wall
      else {
        if (hero.dx > 0 && (hero.x + 50) > obj[i].x &&
            (hero.x + 50) < obj[i].x + 20)
          hero.x = obj[i].x - 50;
        else if (hero.dx < 0 && hero.x < (obj[i].x + obj[i].width) &&
                 hero.x > (obj[i].x + obj[i].width - 20))
          hero.x = obj[i].x + obj[i].width;
      }
    }
  }

  // --- Pass 2: Spikes, Doors, Moving Traps (original logic, unchanged) ---
  for (int i = 0; i < noOfObj; i++) {
    if (obj[i].type == 2)
      continue; // already handled above

    if (checkAABB(hero.x, hero.y, 40, 50, obj[i].x, obj[i].y, obj[i].width,
                  obj[i].height)) {

      if (obj[i].willKill) {
        hero.isDying = true;
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

// mode: 0 for X-axis movement, 1 for Y-axis movement
// trap moving
void triggerTrap(GameObject &trap, Player &hero, double triggerX,
                 double targetPos, double speed, int mode) {

  // Check if the hero has passed the trigger line
  if (hero.x > triggerX) {

    // Pointer to the coordinate we want to change
    double *currentPos = (mode == 0) ? &trap.x : &trap.y;

    if (*currentPos < targetPos) {
      *currentPos += speed;
      if (*currentPos > targetPos)
        *currentPos = targetPos;
    } else if (*currentPos > targetPos) {
      *currentPos -= speed;
      if (*currentPos < targetPos)
        *currentPos = targetPos;
    }
  }
}
#endif

/*
if (isLeft) {
p.x -= p.dx;
if (hero.x <= 0) {
hero.x = 0;
}
}
else {
p.x += p.dx;
if (hero.x >= 980) {
hero.x = 980;
}
}
*/

/*
for (int i = 0; i < lvl.objectCount; i++) {
GameObject &obj = lvl.objects[i];

if (obj.isVisible && checkAABB(p.x, p.y, 30, 30, obj.x, obj.y, obj.width,
obj.height)) {
// If hitting a spike, die
if (obj.type == 2) p.isDead = true;

// If hitting a solid block (Type 1), stop falling
if (obj.type == 1) {
if (p.dy < 0) { // Falling down
p.y = obj.y + obj.height;
p.isGrounded = true;
p.dy = 0;
}
}
}
}

*/

// 3. Update X Position (Similar logic for horizontal collision)

// ... (Horizontal collision code here)