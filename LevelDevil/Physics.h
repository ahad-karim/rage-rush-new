#ifndef PHYSICS_H
#define PHYSICS_H
#include "GameData.h"
#include "Levelone.h"

bool jumpDone = false;
bool jumpStart = false;

// REUSABLE FUNCTION 1: Generic AABB Collision
// Returns true if two rectangles overlap
bool checkAABB(double x1, double y1, double w1, double h1,
	double x2, double y2, double w2, double h2) {
	return (x1 < x2 + w2 && x1 + w1 > x2 &&
		y1 < y2 + h2 && y1 + h1 > y2);
}

// REUSABLE FUNCTION 2: Physics Update
// Updates player and handles collisions with ANY level data
//void updatePlayerPhysics(Player &p, Level &lvl) {
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
		if (p.y <= obstacleHeight) {
			p.isGrounded = true;
			p.y = obstacleHeight;
			p.dy = 15;
			jumpDone = true;
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

if (obj.isVisible && checkAABB(p.x, p.y, 30, 30, obj.x, obj.y, obj.width, obj.height)) {
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