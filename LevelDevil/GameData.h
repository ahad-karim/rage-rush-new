#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <time.h>
#include <vector>

int levelCount = 4;
int rageDeaths = 0;

// Shield / Orb mechanic
bool shieldActive = false;
clock_t shieldStartTime = 0;
#define RAGE_MAX 11

struct PlayerData {
  char name[50];
  int level;
  int deaths;
};

// Define the possible states of your game
enum GameState {
  STATE_MAIN_MENU,  // 0
  STATE_ENTER_NAME, // 1
  STATE_CONTINUE,   // 2
  STATE_SCOREBOARD, // 3
  STATE_GAMEPLAY,   // 4
  STATE_WIN,
  STATE_GAME_OVER,
  STATE_LEVEL_SELECT // 7
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
double gravity = -1; // Pulls the player down every frame

// 2. The Universal Object (for tiles, traps, goals)
struct GameObject {
  double x, y;
  double width, height;
  int type; // 0=Spike, 1=Door, 2=Platform, 3=Sawblade, 4=Fake Platform, 5=Ghost, 6=Fake Door, 7=Orb
  int state; // 0=Normal, 1=Triggered/Falling
  bool isVisible;
  bool willKill;
  bool willMove;
  int speed;
  int mode; // 0=move in x-axis, 1=move in y-axis
  int trigX, trigY;
  int innitialX, innitialY;
  int finX, finY;
};

// 3. Global Game State
#define MAX_BLOCKS 100 // Max objects per level
struct Level {
  GameObject objects[MAX_BLOCKS]; // An array of blocks
  int objectCount;
  int startX, startY; // Where player spawns
};

// Declared here so other files (like Level.h) can save data
void saveGameData();

#endif