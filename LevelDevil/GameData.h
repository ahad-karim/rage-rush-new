#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <vector>
#include <string>

struct PlayerData {
	char name[50];
	int level;
	int deaths;
};

// Define the possible states of your game
enum GameState {
	STATE_MAIN_MENU,    // 0
	STATE_ENTER_NAME,   // 1
	STATE_CONTINUE,     // 2
	STATE_SCOREBOARD,   // 3
	STATE_GAMEPLAY      // 4
};

// This is the actual variable that tracks which state we are in
extern GameState currentGameState;

// Global list of all players
PlayerData allPlayers[100];
int totalPlayers = 0;
int currentPlayerIndex = -1; // To track who is currently playing

// 1. The Player Object
struct Player {
	double x, y;
	double dx, dy; // Velocity
	bool isGrounded;
	bool isDead;
	int width, height;
	bool isDying;
};



// Physics Constants
double gravity = -1;    // Pulls the player down every frame
double jumpForce = 15.0;

// 2. The Universal Object (for tiles, traps, goals)
struct GameObject {
	double x, y;
	double width, height;
	int type;       // 0=Empty, 1=Block, 2=Spike, 3=MovingTrap, 4=Goal
	int state;      // 0=Normal, 1=Triggered/Falling
	bool isVisible;
	bool willKill;
};


// 3. Global Game State
#define MAX_BLOCKS 100 // Max objects per level
struct Level {
	GameObject objects[MAX_BLOCKS]; // An array of blocks
	int objectCount;
	int startX, startY; // Where player spawns
};

#endif