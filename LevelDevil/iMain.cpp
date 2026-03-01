#include "iGraphics.h"

#include "GameData.h"
#include "Images.h"
#include "Level.h"
#include "Physics.h"

#include <mmsystem.h>
#include <string>
#include <time.h>

#pragma comment(lib, "winmm.lib")

// int gameState = 0;
bool vol = true;

char inputName[50] = "";
int nameIndex = 0;
int imageLoop = 0;
bool isLeft = false;
int doi = 545;
int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
int screenHeight = glutGet(GLUT_SCREEN_HEIGHT) - 70;
int mouseX = 0, mouseY = 0;

// Do not remove this line!!!!!!
GameState currentGameState = STATE_MAIN_MENU;
Player hero = {0, obstacleHeight, 5, 15, false, false, 40, 40, false};

void iDraw() {
  iClear();
  double rw = screenWidth / 1080.0;
  double rh = screenHeight / 600.0;

  if (currentGameState == STATE_MAIN_MENU) {
    // Background scales to full screen
    iShowImage(0, 0, screenWidth, screenHeight, menubg);

    // Logo (Centered Top)
    iShowImage(370 * rw, 260 * rh, 340 * rw, 340 * rh, logo);

    // New Game (Centered Middle)
    if (mouseX >= 430 * rw && mouseX <= 650 * rw && mouseY >= 170 * rh &&
        mouseY <= 260 * rh)
      iShowImage(430 * rw, 170 * rh, 220 * rw, 90 * rh, newgameHover);
    else
      iShowImage(430 * rw, 170 * rh, 220 * rw, 90 * rh, newgamebut);

    // Continue (Centered Lower)
    if (mouseX >= 430 * rw && mouseX <= 650 * rw && mouseY >= 90 * rh &&
        mouseY <= 160 * rh)
      iShowImage(430 * rw, 90 * rh, 220 * rw, 70 * rh, continueHover);
    else
      iShowImage(430 * rw, 90 * rh, 220 * rw, 70 * rh, continuebut);

    // Scores (Centered Bottom)
    if (mouseX >= 460 * rw && mouseX <= 620 * rw && mouseY >= 10 * rh &&
        mouseY <= 80 * rh)
      iShowImage(460 * rw, 10 * rh, 160 * rw, 70 * rh, scoresHover);
    else
      iShowImage(460 * rw, 10 * rh, 160 * rw, 70 * rh, scores);

    // Levels (Bottom Right)
    if (mouseX >= 980 * rw && mouseX <= 1050 * rw && mouseY >= 30 * rh &&
        mouseY <= 100 * rh)
      iShowImage(980 * rw, 30 * rh, 70 * rw, 40 * rh, levelbutHover);
    else
      iShowImage(980 * rw, 30 * rh, 70 * rw, 40 * rh, levelbut);

    // Volume Button (Bottom Left)
    if (vol)
      iShowImage(30 * rw, 30 * rh, 70 * rw, 70 * rh, volon);
    else
      iShowImage(30 * rw, 30 * rh, 70 * rw, 70 * rh, voloff);
  }

  else if (currentGameState == STATE_GAMEPLAY) {
    // Draw the moving background
    iShowImage(0, 0, screenWidth, screenHeight,
               sublevelbgArray[*subLevelCount - 1]);

    // Draw Header Text (Centered)
    if (levelCount == 1)
      iText(490 * rw, 550 * rh, "SPIKES", GLUT_BITMAP_HELVETICA_18);
    else if (levelCount == 2)
      iText(480 * rw, 550 * rh, "SAWBLADES", GLUT_BITMAP_HELVETICA_18);
    else if (levelCount == 3)
      iText(420 * rw, 550 * rh, "GHOSTS & ILLUSIONS", GLUT_BITMAP_HELVETICA_18);

    // Floor Bricks - Use a loop that fills the screen width dynamically
    for (int x = 0; x < screenWidth; x += 100 * rw) {
      iShowImage(x, 0, 100 * rw, 20 * rh, brick1);
      iShowImage(x - (25 * rw), 20 * rh, 100 * rw, 20 * rh, brick1);
      iShowImage(x, 40 * rh, 100 * rw, 20 * rh, brick1);
    }

    // Traps: These already have x/y coordinates.
    // IMPORTANT: When loading levels, multiply their initial x/y by rw/rh!
    for (int i = 0; i < noOfObj; i++) {
      if (!obj[i].isVisible)
        continue;
      if (obj[i].type == 3) {
        iShowImage(obj[i].x * rw, obj[i].y * rh, obj[i].width * rw,
                   obj[i].height * rh, sawbladeArray[sawbladeFrame]);
      } else {
        iShowImage(obj[i].x * rw, obj[i].y * rh, obj[i].width * rw,
                   obj[i].height * rh, objImg[obj[i].type]);
      }
    }

    // Hero: Standard 50x50 scaled
    iShowImage(hero.x * rw, hero.y * rh, 50 * rw, 50 * rh, currentImage);

    if (hero.isDead) {
      iText(470 * rw, 250 * rh, "Game Over", GLUT_BITMAP_TIMES_ROMAN_24);
    }
  }

  // ... Repeat for WIN and GAME_OVER states ...
  else if (currentGameState == STATE_WIN) {
    iShowImage(0, 0, screenWidth, screenHeight, win);
  } else if (currentGameState == STATE_GAME_OVER) {
    iShowImage(0, 0, screenWidth, screenHeight, gameover);
  }

  // ========== LEVEL SELECT PAGE ==========
  else if (currentGameState == STATE_LEVEL_SELECT) {
    // 1. Draw menu background
    iShowImage(0, 0, screenWidth, screenHeight, menubg);

    // 2. Dark overlay using OpenGL blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.55f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Reset color

    // 3. Header text
    iSetColor(100, 200, 255);
    iText(410 * rw, 500 * rh, "SELECT LEVEL", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 255, 255);

    // 4. Level buttons (centered row, square)
    double btnSize = 150 * rw;
    double gap = 40 * rw;
    double totalW = 3 * btnSize + 2 * gap;
    double startX = (screenWidth - totalW) / 2.0;
    double btnY = 200 * rh;
    double btn1X = startX;
    double btn2X = startX + btnSize + gap;
    double btn3X = startX + 2 * (btnSize + gap);

    // Level 1
    iShowImage(btn1X, btnY, btnSize, btnSize, level1Img);

    // Level 2
    iShowImage(btn2X, btnY, btnSize, btnSize, level2Img);

    // Level 3
    iShowImage(btn3X, btnY, btnSize, btnSize, level3Img);

    // 5. Back button (text at bottom)
    bool hovBack = (mouseX >= 480 * rw && mouseX <= 600 * rw &&
                    mouseY >= 30 * rh && mouseY <= 70 * rh);
    if (hovBack)
      iSetColor(100, 200, 255);
    else
      iSetColor(180, 180, 180);
    iText(500 * rw, 40 * rh, "< BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 255, 255);
  }
}

// New stuff start

void saveGameData() {
  FILE *fp;
  // fopen_s returns 0 if successful
  errno_t err = fopen_s(&fp, "savegame.txt", "w");

  if (err != 0 || fp == NULL)
    return;

  for (int i = 0; i < totalPlayers; i++) {
    fprintf(fp, "%s %d %d\n", allPlayers[i].name, allPlayers[i].level,
            allPlayers[i].deaths);
  }
  fclose(fp);
}

void loadGameData() {
  FILE *fp;
  errno_t err = fopen_s(&fp, "savegame.txt", "r");

  if (err != 0 || fp == NULL)
    return;

  totalPlayers = 0;
  // Check if totalPlayers is within bounds of your array (e.g., 100)
  while (totalPlayers < 100 &&
         fscanf_s(fp, "%s %d %d", allPlayers[totalPlayers].name,
                  (unsigned)_countof(allPlayers[totalPlayers].name),
                  &allPlayers[totalPlayers].level,
                  &allPlayers[totalPlayers].deaths) != EOF) {
    totalPlayers++;
  }
  fclose(fp);
}

// New stuff end

// New stuff

void registerNewPlayer(char *name) {
  // 1. Check if we have space in our array (max 100 players)
  if (totalPlayers >= 100) {
    printf("Error: Player database full!\n");
    return;
  }

  // 2. Copy the name from the input buffer to our permanent player list
  // We use strcpy_s for the safety Visual Studio requested earlier
  strcpy_s(allPlayers[totalPlayers].name, sizeof(allPlayers[totalPlayers].name),
           name);

  // 3. Set starting stats for a "New Game"
  allPlayers[totalPlayers].level = 1;
  allPlayers[totalPlayers].deaths = 0;

  // 4. Set this new person as the active player
  currentPlayerIndex = totalPlayers;

  // 5. Increase the count of total registered players
  totalPlayers++;

  // 6. Save the updated list to "savegame.txt" immediately
  // This ensures that even if the game crashes, the player is registered
  saveGameData();

  printf("Registered Player: %s at Index: %d\n", name, currentPlayerIndex);
}

void myKeyboard(unsigned char key, int x, int y) {
  if (currentGameState == STATE_ENTER_NAME) {
    if (key == '\r') { // Enter key
      if (nameIndex > 0) {
        // Save and start game
        registerNewPlayer(inputName);
        currentGameState = STATE_GAMEPLAY;

        // Clear for next time
        nameIndex = 0;
        inputName[0] = '\0';
      }
    } else if (key == '\b') { // Backspace
      if (nameIndex > 0) {
        nameIndex--;
        inputName[nameIndex] = '\0';
      }
    } else if (key >= 32 && key <= 126) { // Printable characters
      if (nameIndex < 49) {
        inputName[nameIndex] = key;
        nameIndex++;
        inputName[nameIndex] = '\0';
      }
    }
  }

  // This tells the window to refresh after typing a letter
  glutPostRedisplay();
}

// end of new stuff

void iMouseMove(int mx, int my) {}

void iPassiveMouseMove(int mx, int my) {
  mouseX = mx;
  mouseY = my;
}

void iMouse(int button, int state, int mx, int my) {

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    double rw = screenWidth / 1080.0;
    double rh = screenHeight / 600.0;

    // Only check for clicks if we are currently on the menu
    if (currentGameState == STATE_MAIN_MENU) {

      // New game button click (X: 430 to 650, Y: 170 to 260)
      if (mx >= 430 * rw && mx <= 650 * rw && my >= 170 * rh &&
          my <= 260 * rh) {
        // currentGameState = STATE_ENTER_NAME; // Naming state
        currentGameState = STATE_GAMEPLAY;

        nameIndex = 0;
        inputName[0] = '\0';
        hero.isDead = false;
        hero.isDying = false;
        currentImage = staticChar;
        hero.x = 0;
        hero.y = obstacleHeight;
        imageLoop = 0;
        levelDone = false;
        levelCount = 1;

        // Need to be changed for level 2
        subLevelCount1 = 1;
        levelDefining();

        for (int i = 0; i < noOfObj; i++) {
          obj[i].x = obj[i].innitialX;
          obj[i].y = obj[i].innitialY;
        }
      }

      // Continue button (X: 430 to 650, Y: 90 to 160)
      if (mx >= 430 * rw && mx <= 650 * rw && my >= 90 * rh && my <= 160 * rh) {
        // Resume from the current level/sublevel (don't reset counters)
        levelDefining();
        hero.isDead = false;
        hero.isDying = false;
        currentImage = staticChar;
        hero.x = 0;
        hero.y = obstacleHeight;
        imageLoop = 0;
        levelDone = false;
        for (int i = 0; i < noOfObj; i++) {
          obj[i].x = obj[i].innitialX;
          obj[i].y = obj[i].innitialY;
        }
        currentGameState = STATE_GAMEPLAY;
      }

      // changing volume (X: 30 to 100, Y: 30 to 100)
      if (mx >= 30 * rw && mx <= 100 * rw && my >= 30 * rh && my <= 100 * rh) {
        vol = !vol;
        // Opening/Loading the audio files
        mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0,
                      NULL);
        // mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0,
        // NULL);

        // mciSendString("close ggsong", NULL, 0, NULL);
        if (vol) {
          // Playing the background audio on repeat
          mciSendString("play bgsong repeat", NULL, 0, NULL);
        } else {
          // If the use of an audio is finished, close it to free memory
          mciSendString("stop bgsong", NULL, 0, NULL);
        }
      }
      // Levels button click (X: 980 to 1050, Y: 30 to 100)
      if (mx >= 980 * rw && mx <= 1050 * rw && my >= 30 * rh &&
          my <= 100 * rh) {
        currentGameState = STATE_LEVEL_SELECT;
      }
    }
    // ========== LEVEL SELECT CLICK HANDLING ==========
    else if (currentGameState == STATE_LEVEL_SELECT) {
      double btnSize = 150 * rw;
      double gap = 40 * rw;
      double totalW = 3 * btnSize + 2 * gap;
      double startX = (screenWidth - totalW) / 2.0;
      double btnY = 200 * rh;
      double btn1X = startX;
      double btn2X = startX + btnSize + gap;
      double btn3X = startX + 2 * (btnSize + gap);

      // Level 1 click
      if (mx >= btn1X && mx <= btn1X + btnSize && my >= btnY &&
          my <= btnY + btnSize) {
        levelCount = 1;
        subLevelCount1 = 1;
        levelDone = false;
        levelDefining();
        hero.isDead = false;
        hero.isDying = false;
        currentImage = staticChar;
        hero.x = 0;
        hero.y = obstacleHeight;
        imageLoop = 0;
        for (int i = 0; i < noOfObj; i++) {
          obj[i].x = obj[i].innitialX;
          obj[i].y = obj[i].innitialY;
        }
        currentGameState = STATE_GAMEPLAY;
      }
      // Level 2 click
      else if (mx >= btn2X && mx <= btn2X + btnSize && my >= btnY &&
               my <= btnY + btnSize) {
        levelCount = 2;
        subLevelCount2 = 1;
        levelDone = false;
        levelDefining();
        hero.isDead = false;
        hero.isDying = false;
        currentImage = staticChar;
        hero.x = 0;
        hero.y = obstacleHeight;
        imageLoop = 0;
        for (int i = 0; i < noOfObj; i++) {
          obj[i].x = obj[i].innitialX;
          obj[i].y = obj[i].innitialY;
        }
        currentGameState = STATE_GAMEPLAY;
      }
      // Level 3 click
      else if (mx >= btn3X && mx <= btn3X + btnSize && my >= btnY &&
               my <= btnY + btnSize) {
        levelCount = 3;
        subLevelCount3 = 1;
        levelDone = false;
        levelDefining();
        hero.isDead = false;
        hero.isDying = false;
        currentImage = staticChar;
        hero.x = 0;
        hero.y = obstacleHeight;
        imageLoop = 0;
        for (int i = 0; i < noOfObj; i++) {
          obj[i].x = obj[i].innitialX;
          obj[i].y = obj[i].innitialY;
        }
        currentGameState = STATE_GAMEPLAY;
      }
      // Back button click
      else if (mx >= 480 * rw && mx <= 600 * rw && my >= 30 * rh &&
               my <= 70 * rh) {
        currentGameState = STATE_MAIN_MENU;
      }
    } else if (currentGameState == STATE_GAMEPLAY) {
      // Temporary
      currentGameState = STATE_MAIN_MENU;
    } else if (currentGameState == STATE_WIN) {
      currentGameState = STATE_MAIN_MENU;
    } else if (currentGameState == STATE_GAME_OVER) {
      currentGameState = STATE_MAIN_MENU;
    }
  }

  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
  }
}

// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
// GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
// GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
// GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
// GLUT_KEY_INSERT

bool wasMovingLastFrame = false;
clock_t lastTime = 0;
double interval = 1.5;
void fixedUpdate() {
  if (currentGameState == STATE_GAMEPLAY) {

    for (int i = 0; i < noOfObj; i++) {
      triggerTrap(obj[i], hero);
    }

    colisionDeal(hero);
  }

  if (currentGameState == STATE_WIN) {
    hero.isDead = false;
    hero.isDying = false;
    currentImage = staticChar;
    hero.x = 0;
    hero.y = obstacleHeight;
    imageLoop = 0;
    levelDone = false;
    levelCount = 1;

    // Need to be changed for level 2
    subLevelCount1 = 1;
    levelDefining();

    for (int i = 0; i < noOfObj; i++) {
      obj[i].x = obj[i].innitialX;
      obj[i].y = obj[i].innitialY;
    }
  }

  if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP) ||
      isKeyPressed(' ')) {
    jumpStart = true;

    if (imageLoop == 9) {
      imageLoop = 0;
    } else {
      imageLoop++;
    }

    if (isLeft) {
      currentImage = characterLeftJumpArray[5];
      updatePlayerPhysics(hero, isLeft);
    } else {
      currentImage = rightjump3;
      updatePlayerPhysics(hero, isLeft);
    }
  }
  if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
    isLeft = true;

    if (imageLoop == 8) {
      imageLoop = 0;
    } else {
      imageLoop++;
    }
    if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP) ||
        isKeyPressed(' ')) {
      currentImage = characterLeftJumpArray[5];

    } else {
      currentImage = characterLeftArray[imageLoop];
    }

    hero.x -= hero.dx;
    if (hero.x <= 0) {
      hero.x = 0;
    }
  }
  if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
    // For debugging only
    /*
    if (imageLoop == 14) {
            imageLoop = 14;
            hero.isDead = true;
    }
    else {
            imageLoop++;
    }
    hero.isDying = true;

    currentImage = characterDieArray[imageLoop];
    */
  }
  if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
    isLeft = false;
    if (imageLoop == 8) {
      imageLoop = 0;
    } else {
      imageLoop++;
    }

    if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP) ||
        isKeyPressed(' ')) {
      currentImage = rightjump3;

    } else {
      currentImage = characterRightArray[imageLoop];
    }

    hero.x += hero.dx;
    if (hero.x >= 1030 && *subLevelCount >= 4) {
      hero.x = 1030;
    } else if (hero.x >= 1000) {
      //*subLevelCount++;
      if (*subLevelCount < 4) {
        (*subLevelCount)++;
      } else {
        (*subLevelCount) = 1;
      }

      levelDefining();
      hero.x = 0;
      hero.isDead = false;
      hero.isDying = false;
      currentImage = staticChar;

      hero.y = obstacleHeight;
      imageLoop = 0;
    }
  }

  if (isKeyPressed(' ')) {
    vol = false;

    mciSendString("stop bgsong", NULL, 0, NULL);
  }
  bool isMoving = (isKeyPressed('a') || isKeyPressed('d') ||
                   isSpecialKeyPressed(GLUT_KEY_LEFT) ||
                   isSpecialKeyPressed(GLUT_KEY_RIGHT) || isKeyPressed('w') ||
                   isSpecialKeyPressed(GLUT_KEY_UP) || isKeyPressed(' '));

  if (hero.isDying) {
    if (imageLoop == 14) {
      imageLoop = 14;
      hero.isDead = true;
    } else {
      imageLoop++;
    }

    currentImage = characterDieArray[imageLoop];
  }

  if (hero.isDead) {
    currentGameState = STATE_GAME_OVER;
    hero.isDead = false;
    hero.isDying = false;
    currentImage = staticChar;
    hero.x = 0;
    hero.y = obstacleHeight;
    imageLoop = 0;
    for (int i = 0; i < noOfObj; i++) {
      obj[i].x = obj[i].innitialX;
      obj[i].y = obj[i].innitialY;
    }
  }

  // Use platform top as ground when on a platform, otherwise base floor
  double groundLevel = onPlatform ? platformTopY : (double)obstacleHeight;

  // 1. Detect walking off edges
  if (hero.y > groundLevel + 1) { // Small buffer to avoid jitter
    hero.isGrounded = false;
  }

  // 2. Gravity and Falling Animation
  if (!hero.isGrounded) {
    if (!(isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP) ||
          isKeyPressed(' '))) {
      hero.dy += gravity;
      hero.y += hero.dy;
    }
    // Only reset animation if truly in air (prevents freeze on platforms)
    imageLoop = 0;
  }

  // 3. Ground Landing
  if (hero.y <= groundLevel + 0.1) {
    hero.y = groundLevel;
    hero.dy = 15; // Reset velocity for next jump

    if (!hero.isGrounded) {
      hero.isGrounded = true;
      currentImage = staticChar;
      imageLoop = 0;
    }
  }

  if (wasMovingLastFrame && !isMoving && hero.y <= groundLevel) {
    printf("Movement Stopped!\n");
    currentImage = staticChar;
    imageLoop = 0;
  }

  wasMovingLastFrame = isMoving;
}

void changeSawbladeFrame() {
  sawbladeFrame++;
  if (sawbladeFrame >= 8) {
    sawbladeFrame = 0;
  }
}

int main() {

  // Opening/Loading the audio files
  mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0,
                NULL);
  // mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);

  // mciSendString("close ggsong", NULL, 0, NULL);
  if (vol) {
    // Playing the background audio on repeat
    mciSendString("play bgsong repeat", NULL, 0, NULL);
  } else {
    // If the use of an audio is finished, close it to free memory
    mciSendString("stop bgsong", NULL, 0, NULL);
  }
  iInitialize(screenWidth, screenHeight, "RageRush");

  glutKeyboardFunc(myKeyboard);

  initImages();
  levelDefining();

  iSetTimer(30, changeSawbladeFrame); // Animate sawblade nicely

  iStart();
  return 0;
}