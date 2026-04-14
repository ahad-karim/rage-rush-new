#include "iGraphics.h"

#include "GameData.h"
#include "Images.h"
#include "Level.h"
#include "Physics.h"

#include <mmsystem.h>
#include <math.h>
#include <string>
#include <time.h>

#pragma comment(lib, "winmm.lib")

// int gameState = 0;
bool vol = true;

char inputName[50] = "";
int nameIndex = 0;
int imageLoop = 0;

// Debounce array for name input key polling
bool prevKeyState[256] = {false};
bool hasSelectedPlayer = false; // Tracks if a player was chosen for 'Continue' 
bool isLeft = false;
int doi = 545;
int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
int screenHeight = glutGet(GLUT_SCREEN_HEIGHT) - 70;
int mouseX = 0, mouseY = 0;

// Do not remove this line!!!!!!
GameState currentGameState = STATE_MAIN_MENU;
int currentStoryAudioState = -1;
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

  // ========== NAME ENTRY SCREEN ==========
  else if (currentGameState == STATE_ENTER_NAME) {
    // 1. Draw menu background
    iShowImage(0, 0, screenWidth, screenHeight, menubg);

    // 2. Dark overlay
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // 3. Prompt text
    iSetColor(100, 200, 255);
    iText(370 * rw, 400 * rh, "ENTER YOUR NAME", GLUT_BITMAP_TIMES_ROMAN_24);

    // 4. Input box background
    iSetColor(30, 30, 30);
    iFilledRectangle(340 * rw, 300 * rh, 400 * rw, 50 * rh);
    iSetColor(100, 200, 255);
    iRectangle(340 * rw, 300 * rh, 400 * rw, 50 * rh);

    // 5. Typed name text
    iSetColor(255, 255, 255);
    iText(360 * rw, 318 * rh, inputName, GLUT_BITMAP_TIMES_ROMAN_24);

    // 6. Blinking cursor (simple underscore)
    char cursorText[55];
    strcpy_s(cursorText, sizeof(cursorText), inputName);
    strcat_s(cursorText, sizeof(cursorText), "_");
    iSetColor(100, 200, 255);
    // Draw cursor at end of text
    int textLen = strlen(inputName);
    iText((360 + textLen * 12) * rw, 318 * rh, "_", GLUT_BITMAP_TIMES_ROMAN_24);

    // 7. Instructions
    iSetColor(150, 150, 150);
    iText(390 * rw, 260 * rh, "Press ENTER to start", GLUT_BITMAP_HELVETICA_18);
  }

  // ========== SCOREBOARD SCREEN ==========
  else if (currentGameState == STATE_SCOREBOARD) {
    // 1. Draw menu background
    iShowImage(0, 0, screenWidth, screenHeight, menubg);

    // 2. Dark overlay for readability
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // 3. Header text
    iSetColor(100, 200, 255);
    iText(420 * rw, 500 * rh, "PLAYER SCORES", GLUT_BITMAP_TIMES_ROMAN_24);

    // 4. Table Headers
    iSetColor(200, 200, 200);
    iText(200 * rw, 440 * rh, "NAME", GLUT_BITMAP_HELVETICA_18);
    iText(500 * rw, 440 * rh, "LEVEL REACHED", GLUT_BITMAP_HELVETICA_18);
    iText(800 * rw, 440 * rh, "DEATHS", GLUT_BITMAP_HELVETICA_18);

    // 5. Lines separator
    iSetColor(100, 100, 100);
    iLine(180 * rw, 430 * rh, 900 * rw, 430 * rh);

    // 6. Draw Player Data
    iSetColor(255, 255, 255);
    double startY = 390 * rh;
    double gapY = 30 * rh;
    int displayLimit = (totalPlayers > 12) ? 12 : totalPlayers;

    if (totalPlayers == 0) {
      iSetColor(150, 150, 150);
      iText(400 * rw, 350 * rh, "No players registered yet.", GLUT_BITMAP_HELVETICA_18);
    } else {
      for (int i = 0; i < displayLimit; i++) {
        // Name
        iText(200 * rw, startY - (i * gapY), allPlayers[i].name, GLUT_BITMAP_HELVETICA_18);
        
        // Level
        char lvlStr[10];
        sprintf_s(lvlStr, sizeof(lvlStr), "%d", allPlayers[i].level);
        iText(550 * rw, startY - (i * gapY), lvlStr, GLUT_BITMAP_HELVETICA_18);
        
        // Deaths
        char dthStr[10];
        sprintf_s(dthStr, sizeof(dthStr), "%d", allPlayers[i].deaths);
        iText(820 * rw, startY - (i * gapY), dthStr, GLUT_BITMAP_HELVETICA_18);
      }
    }

    // 7. Return Instructions
    iSetColor(150, 150, 150);
    iText(380 * rw, 50 * rh, "Press ESC or BACKSPACE to return", GLUT_BITMAP_HELVETICA_18);
  }

  // ========== PLAYER SELECTION SCREEN (CONTINUE) ==========
  else if (currentGameState == STATE_CONTINUE) {
    // 1. Draw menu background
    iShowImage(0, 0, screenWidth, screenHeight, menubg);

    // 2. Dark overlay for readability
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();
    glDisable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // 3. Header text
    iSetColor(100, 200, 255);
    iText(420 * rw, 500 * rh, "SELECT A PLAYER", GLUT_BITMAP_TIMES_ROMAN_24);

    // 4. Table Headers
    iSetColor(200, 200, 200);
    iText(200 * rw, 440 * rh, "NAME", GLUT_BITMAP_HELVETICA_18);
    iText(500 * rw, 440 * rh, "LEVEL REACHED", GLUT_BITMAP_HELVETICA_18);
    iText(800 * rw, 440 * rh, "DEATHS", GLUT_BITMAP_HELVETICA_18);

    // 5. Lines separator
    iSetColor(100, 100, 100);
    iLine(180 * rw, 430 * rh, 900 * rw, 430 * rh);

    // 6. Draw Player Data (Clickable Rows)
    double startY = 390 * rh;
    double gapY = 30 * rh;
    double rowHeight = 25 * rh;
    int displayLimit = (totalPlayers > 12) ? 12 : totalPlayers;

    if (totalPlayers == 0) {
      iSetColor(150, 150, 150);
      iText(400 * rw, 350 * rh, "No players registered yet.", GLUT_BITMAP_HELVETICA_18);
    } else {
      for (int i = 0; i < displayLimit; i++) {
        double currentY = startY - (i * gapY);
        
        // Hover effect for row
        bool isHovering = (mouseX >= 180 * rw && mouseX <= 900 * rw && 
                           mouseY >= currentY - 5 * rh && mouseY <= currentY + rowHeight - 5 * rh);
        
        if (isHovering) {
          iSetColor(50, 50, 50); // Highlight background
          iFilledRectangle(180 * rw, currentY - 5 * rh, 720 * rw, rowHeight);
          iSetColor(255, 255, 100); // Yellow text on hover
        } else {
          iSetColor(255, 255, 255); // White text normally
        }

        // Name
        iText(200 * rw, currentY, allPlayers[i].name, GLUT_BITMAP_HELVETICA_18);
        
        // Level
        char lvlStr[10];
        sprintf_s(lvlStr, sizeof(lvlStr), "%d", allPlayers[i].level);
        iText(550 * rw, currentY, lvlStr, GLUT_BITMAP_HELVETICA_18);
        
        // Deaths
        char dthStr[10];
        sprintf_s(dthStr, sizeof(dthStr), "%d", allPlayers[i].deaths);
        iText(820 * rw, currentY, dthStr, GLUT_BITMAP_HELVETICA_18);
      }
    }

    // 7. Return Instructions
    iSetColor(150, 150, 150);
    iText(430 * rw, 50 * rh, "Press ESC to return", GLUT_BITMAP_HELVETICA_18);
  }

  else if (currentGameState == STATE_GAMEPLAY) {
    

    // Draw Header Text (Centered)
	if (levelCount == 1)
	{
		iShowImage(0, 0, screenWidth, screenHeight, l1bg[*subLevelCount - 1]);
		iText(490 * rw, 550 * rh, "SPIKES", GLUT_BITMAP_HELVETICA_18);
	}	
	else if (levelCount == 2) {
		iShowImage(0, 0, screenWidth, screenHeight, l2bg[*subLevelCount - 1]);
		iText(480 * rw, 550 * rh, "SAWBLADES", GLUT_BITMAP_HELVETICA_18);
	}
      
	else if (levelCount == 3) {
		iShowImage(0, 0, screenWidth, screenHeight, l3bg[*subLevelCount - 1]);
		iText(420 * rw, 550 * rh, "GHOSTS & ILLUSIONS", GLUT_BITMAP_HELVETICA_18);
	}
	else if (levelCount == 4) {
		iShowImage(0, 0, screenWidth, screenHeight, l4bg[*subLevelCount - 1]);
		iText(470 * rw, 550 * rh, "DARKNESS", GLUT_BITMAP_HELVETICA_18);
	}
	else if (levelCount == 5) {
		iShowImage(0, 0, screenWidth, screenHeight, l5bg[*subLevelCount - 1]);
		iText(430 * rw, 550 * rh, "MOVING MADNESS", GLUT_BITMAP_HELVETICA_18);
	}
      

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
	  }
	  else if (obj[i].type == 5) {
		  iShowImage((obj[i].x * rw)+5, (obj[i].y * rh)+5, (obj[i].width * rw)-5,
			  (obj[i].height * rh)-5, objImg[obj[i].type]);
	  }
	  
	  else {
        iShowImage(obj[i].x * rw, obj[i].y * rh, obj[i].width * rw,
                   obj[i].height * rh, objImg[obj[i].type]);
      }
    }

    // Hero: Standard 50x50 scaled
    iShowImage(hero.x * rw, hero.y * rh, 50 * rw, 50 * rh, currentImage);

    // Shield overlay — drawn on top of hero while active
    if (shieldActive) {
      iShowImage((hero.x - 5) * rw, (hero.y - 5) * rh, 60 * rw, 60 * rh, shieldImg);
    }

    if (hero.isDead) {
      iText(470 * rw, 250 * rh, "Game Over", GLUT_BITMAP_TIMES_ROMAN_24);
    }

    // ========== DARKNESS OVERLAY (Level 4) ==========
    if (levelCount == 4 && hero.x >= darknessTriggerX) {
      // Player center in screen coordinates
      double cx = (hero.x + 25) * rw;  // center of 50-wide hero
      double cy = (hero.y + 25) * rh;  // center of 50-tall hero
      double rad = darknessRadius * rw;
      int segments = 40;

      // Step 1: Clear stencil buffer
      glEnable(GL_STENCIL_TEST);
      glClearStencil(0);
      glClear(GL_STENCIL_BUFFER_BIT);

      // Step 2: Draw circle into stencil (mark circle area as 1)
      glStencilFunc(GL_ALWAYS, 1, 0xFF);
      glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Don't draw to color

      glBegin(GL_TRIANGLE_FAN);
      glVertex2f(cx, cy);
      for (int i = 0; i <= segments; i++) {
        double angle = 2.0 * 3.14159265 * i / segments;
        glVertex2f(cx + rad * cos(angle), cy + rad * sin(angle));
      }
      glEnd();

      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color

      // Step 3: Draw semi-transparent black overlay ONLY where stencil != 1 (outside circle)
      glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
      glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
      glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(screenWidth, 0);
      glVertex2f(screenWidth, screenHeight);
      glVertex2f(0, screenHeight);
      glEnd();
      glDisable(GL_BLEND);

      glDisable(GL_STENCIL_TEST);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Reset color
    }

    // ========== RAGE METER (top-right) ==========
    double meterW = 200 * rw;
    double meterH = 22 * rh;
    double meterX = screenWidth - meterW - 40 * rw;
    double meterY = screenHeight - 50 * rh;
    double fillRatio = (double)rageDeaths / 10.0;
    if (fillRatio > 1.0) fillRatio = 1.0;

    // Background (dark gray)
    iSetColor(40, 40, 40);
    iFilledRectangle(meterX, meterY, meterW, meterH);

    // Fill (green -> yellow -> red gradient based on ratio)
    int r = (int)(255 * fillRatio);
    int g = (int)(255 * (1.0 - fillRatio));
    iSetColor(r, g, 0);
    iFilledRectangle(meterX, meterY, meterW * fillRatio, meterH);

    // Border (white)
    iSetColor(200, 200, 200);
    iRectangle(meterX, meterY, meterW, meterH);

    // Label
    iSetColor(255, 255, 255);
    iText(meterX, meterY + meterH + 5 * rh, "RAGE", GLUT_BITMAP_HELVETICA_18);
  }

  // ... WIN and GAME_OVER states ...
  else if (currentGameState == STATE_WIN) {
    iShowImage(0, 0, screenWidth, screenHeight, intro4);
  } else if (currentGameState == STATE_GAME_OVER) {
    iShowImage(0, 0, screenWidth, screenHeight, gameover);
  }

  // ========== STORY SCREEN ==========
  else if (currentGameState == STATE_STORY) {
    // Black background
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, screenWidth, screenHeight);

    // ---- Story text data ----
    // Part 0 text (two lines)
    static const char* storyLines[3][5] = {
      {
        "The world was still bright. I stepped onto the university bus as usual,",
        "backpack heavy, head full of plans. I didn't even look twice at the driver.",
        "I just wanted to attend classes as usual.",
        NULL, NULL
      },
      {
        "Time slowed down. The roar of the train was deafening - a wall of blue and yellow steel",
        "screaming across the tracks. The bus felt like paper. Shattering glass,",
        "the smell of burning oil, and a crushing weight.",
        "That was the last thing I remember.",
        NULL
      },
      {
        "Cold. That's what woke me up. I wasn't on the bus anymore.",
        "I wasn't on the tracks. I opened my eyes to a ceiling of rusted pipes and shadows.",
        "My head throbbed, and the air tasted like copper and old machinery.",
        "\"Where am I...?\" I'm alive, but I'm not home.",
        "I don't know this place, but the heavy iron door in front of me is the only way out. It's time to move."
      }
    };
    static const int storyLineCount[3] = {3, 4, 5};

    // Audio durations (seconds) — measured from actual mp3s
    static const double storyDuration[3] = {13.636, 17.162, 26.331};

    // Story images
    static int storyImg[3];
    storyImg[0] = intro1; storyImg[1] = intro2; storyImg[2] = intro3;

    if (storyPhase == 0) {
      // --- Typewriter phase ---
      // Build a single concatenated string from the lines
      char fullText[1024] = "";
      for (int li = 0; li < storyLineCount[storyPart]; li++) {
        if (li > 0) strcat_s(fullText, sizeof(fullText), "\n");
        strcat_s(fullText, sizeof(fullText), storyLines[storyPart][li]);
      }
      int totalChars = (int)strlen(fullText);

      // Render each line up to storyCharsShown total chars
      int charsLeft = storyCharsShown;
      double lineSpacing = 32 * rh;
      double startY = screenHeight / 2.0 + (storyLineCount[storyPart] - 1) * lineSpacing / 2.0;

      iSetColor(220, 220, 220);
      for (int li = 0; li < storyLineCount[storyPart] && charsLeft > 0; li++) {
        int lineLen = (int)strlen(storyLines[storyPart][li]);
        int showLen = charsLeft < lineLen ? charsLeft : lineLen;

        char buf[300] = "";
        strncpy_s(buf, sizeof(buf), storyLines[storyPart][li], showLen);
        buf[showLen] = '\0';

        // Center the line horizontally
        double textWidth = showLen * 9.0 * rw;
        double lineX = (screenWidth - textWidth) / 2.0;
        iText(lineX, startY - li * lineSpacing, buf, GLUT_BITMAP_9_BY_15);

        charsLeft -= lineLen;
      }

      // Blinking cursor after last shown character
      if (storyCharsShown < totalChars) {
        iSetColor(180, 180, 180);
        iText(screenWidth / 2.0, 60 * rh, "_", GLUT_BITMAP_9_BY_15);
      }

    } else if (storyPhase == 1) {
      // --- Hold phase: full text stays on screen for 1.5s ---
      double lineSpacing = 32 * rh;
      double startY = screenHeight / 2.0 + (storyLineCount[storyPart] - 1) * lineSpacing / 2.0;

      iSetColor(220, 220, 220);
      for (int li = 0; li < storyLineCount[storyPart]; li++) {
        if (!storyLines[storyPart][li]) break;
        int lineLen = (int)strlen(storyLines[storyPart][li]);
        double textWidth = lineLen * 9.0 * rw;
        double lineX = (screenWidth - textWidth) / 2.0;
        iText(lineX, startY - li * lineSpacing,
              const_cast<char*>(storyLines[storyPart][li]), GLUT_BITMAP_9_BY_15);
      }

    } else {
      // --- Image phase (storyPhase == 2): fade in and hold ---
      double fadeT = storyTimer / 0.5; // 0.5s fade-in
      if (fadeT > 1.0) fadeT = 1.0;

      iShowImage(0, 0, screenWidth, screenHeight, storyImg[storyPart]);

      // Dim overlay fades out (start fully black, clear to transparent)
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0.0f, 0.0f, 0.0f, (float)(1.0 - fadeT));
      glBegin(GL_QUADS);
        glVertex2f(0, 0); glVertex2f(screenWidth, 0);
        glVertex2f(screenWidth, screenHeight); glVertex2f(0, screenHeight);
      glEnd();
      glDisable(GL_BLEND);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

      // "Skip" hint
      iSetColor(120, 120, 120);
      iText(20 * rw, 20 * rh, "Press SPACE to skip", GLUT_BITMAP_HELVETICA_12);
    }
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

    // 4. Level buttons (centered row)
    double btnSize = 130 * rw;
    double gap = 30 * rw;
    double totalW = 5 * btnSize + 4 * gap;
    double startX = (screenWidth - totalW) / 2.0;
    double btnY = 250 * rh;

    for (int i = 1; i <= 5; i++) {
        double currentX = startX + (i - 1) * (btnSize + gap);
        
        bool isHovering = (mouseX >= currentX && mouseX <= currentX + btnSize &&
                           mouseY >= btnY && mouseY <= btnY + btnSize);

        if (isHovering) {
            iSetColor(50, 50, 50); // Dark gray hover background
            iFilledRectangle(currentX, btnY, btnSize, btnSize);
            iSetColor(255, 255, 100); // Yellow border and text
            iRectangle(currentX, btnY, btnSize, btnSize);
        } else {
            iSetColor(30, 30, 30); // Very dark gray normal background
            iFilledRectangle(currentX, btnY, btnSize, btnSize);
            iSetColor(150, 150, 150); // Gray border and text
            iRectangle(currentX, btnY, btnSize, btnSize);
        }

        char lvlStr[20];
        sprintf_s(lvlStr, sizeof(lvlStr), "LEVEL %d", i);
        // Center text roughly
        iText(currentX + 30 * rw, btnY + 55 * rh, lvlStr, GLUT_BITMAP_HELVETICA_18);
    }

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
  // Name input is handled in fixedUpdate via isKeyPressed polling
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
        currentGameState = STATE_ENTER_NAME;
        nameIndex = 0;
        inputName[0] = '\0';
      }

      // Continue button (X: 430 to 650, Y: 90 to 160)
      if (mx >= 430 * rw && mx <= 650 * rw && my >= 90 * rh && my <= 160 * rh) {
        if (!hasSelectedPlayer) {
          currentGameState = STATE_CONTINUE;
        } else {
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
            obj[i].state = 0; // reset ping-pong direction
          }
          currentGameState = STATE_GAMEPLAY;
        }
      }

      // Scores button (X: 460 to 620, Y: 10 to 80)
      if (mx >= 460 * rw && mx <= 620 * rw && my >= 10 * rh && my <= 80 * rh) {
        currentGameState = STATE_SCOREBOARD;
      }

      // changing volume (X: 30 to 100, Y: 30 to 100)
      if (mx >= 30 * rw && mx <= 100 * rw && my >= 30 * rh && my <= 100 * rh) {
        vol = !vol;
        // Volume button: close first to handle any state, then reopen and play/stop
        mciSendString("stop bgsong", NULL, 0, NULL);
        mciSendString("close bgsong", NULL, 0, NULL);
        mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0, NULL);
        if (vol) {
          mciSendString("play bgsong repeat", NULL, 0, NULL);
        }
      }
      // Levels button click (X: 980 to 1050, Y: 30 to 100)
      if (mx >= 980 * rw && mx <= 1050 * rw && my >= 30 * rh &&
          my <= 100 * rh) {
        currentGameState = STATE_LEVEL_SELECT;
      }
    }
    // ========== PLAYER SELECTION CLICK HANDLING ==========
    else if (currentGameState == STATE_CONTINUE) {
      double startY = 390 * rh;
      double gapY = 30 * rh;
      double rowHeight = 25 * rh;
      int displayLimit = (totalPlayers > 12) ? 12 : totalPlayers;

      // Check if clicked inside the list bounds
      if (mx >= 180 * rw && mx <= 900 * rw) {
        for (int i = 0; i < displayLimit; i++) {
          double currentY = startY - (i * gapY);
          if (my >= currentY - 5 * rh && my <= currentY + rowHeight - 5 * rh) {
            // Player Selected!
            currentPlayerIndex = i;
            
            // Load their saved stats
            levelCount = allPlayers[i].level;
            rageDeaths = allPlayers[i].deaths;
            
            // Ensure they start at sublevel 1 of their saved level
            if (levelCount == 1) subLevelCount1 = 1;
            else if (levelCount == 2) subLevelCount2 = 1;
            else if (levelCount == 3) subLevelCount3 = 1;
            else if (levelCount == 4) subLevelCount4 = 1;

            hasSelectedPlayer = true;
            
            // Initialize Gameplay
            levelDefining();
            hero.isDead = false;
            hero.isDying = false;
            currentImage = staticChar;
            hero.x = 0;
            hero.y = obstacleHeight;
            imageLoop = 0;
            levelDone = false;
            for (int j = 0; j < noOfObj; j++) {
              obj[j].x = obj[j].innitialX;
              obj[j].y = obj[j].innitialY;
              obj[j].state = 0; // reset ping-pong direction
            }
            currentGameState = STATE_GAMEPLAY;
            break; // Stop checking rows
          }
        }
      }
    }
    // ========== LEVEL SELECT CLICK HANDLING ==========
    else if (currentGameState == STATE_LEVEL_SELECT) {
      double btnSize = 130 * rw;
      double gap = 30 * rw;
      double totalW = 5 * btnSize + 4 * gap;
      double startX = (screenWidth - totalW) / 2.0;
      double btnY = 250 * rh;
      
      bool levelClicked = false;
      int clickedLevel = 0;

      for (int i = 1; i <= 5; i++) {
        double currentX = startX + (i - 1) * (btnSize + gap);
        if (mx >= currentX && mx <= currentX + btnSize && my >= btnY && my <= btnY + btnSize) {
            levelClicked = true;
            clickedLevel = i;
            break;
        }
      }

      if (levelClicked) {
        levelCount = clickedLevel;
        rageDeaths = 0;
        
        if (levelCount == 1) subLevelCount1 = 1;
        else if (levelCount == 2) subLevelCount2 = 1;
        else if (levelCount == 3) subLevelCount3 = 1;
        else if (levelCount == 4) subLevelCount4 = 1;
        else if (levelCount == 5) subLevelCount5 = 1;
        
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
          obj[i].state = 0; // reset ping-pong direction
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

  // ========== NAME INPUT (key polling with debounce) ==========
  if (currentGameState == STATE_ENTER_NAME) {
    // Check Enter key (13)
    if (isKeyPressed(13) && !prevKeyState[13]) {
      if (nameIndex > 0) {
        registerNewPlayer(inputName);

        // Stop background music (keep the device open so the manager can seek+replay it later)
        mciSendString("stop bgsong", NULL, 0, NULL);
        // Reset the audio manager's tracking so it always re-evaluates on next fire
        currentStoryAudioState = -1;

        // Launch story
        storyPart = 0;
        storyPhase = 0;
        storyTimer = 0.0;
        storyCharsShown = 0;
        storyLastTick = clock();

        // Signal the audio manager to open + play part 0
        storyAudioAction = 1;
        storyAudioPlaying = false;

        currentGameState = STATE_STORY;
        nameIndex = 0;
        inputName[0] = '\0';
      }
    }
    prevKeyState[13] = isKeyPressed(13);

    // Check Backspace key (8)
    if (isKeyPressed(8) && !prevKeyState[8]) {
      if (nameIndex > 0) {
        nameIndex--;
        inputName[nameIndex] = '\0';
      }
    }
    prevKeyState[8] = isKeyPressed(8);

    // Check letter keys a-z
    for (char c = 'a'; c <= 'z'; c++) {
      if (isKeyPressed(c) && !prevKeyState[(unsigned char)c]) {
        if (nameIndex < 49) {
          // Check shift for uppercase
          bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
          inputName[nameIndex] = shift ? (c - 32) : c;
          nameIndex++;
          inputName[nameIndex] = '\0';
        }
      }
      prevKeyState[(unsigned char)c] = isKeyPressed(c);
    }

    // Check digit keys 0-9
    for (char c = '0'; c <= '9'; c++) {
      if (isKeyPressed(c) && !prevKeyState[(unsigned char)c]) {
        if (nameIndex < 49) {
          inputName[nameIndex] = c;
          nameIndex++;
          inputName[nameIndex] = '\0';
        }
      }
      prevKeyState[(unsigned char)c] = isKeyPressed(c);
    }

    // Check space key
    if (isKeyPressed(' ') && !prevKeyState[(unsigned char)' ']) {
      if (nameIndex < 49) {
        inputName[nameIndex] = ' ';
        nameIndex++;
        inputName[nameIndex] = '\0';
      }
    }
    prevKeyState[(unsigned char)' '] = isKeyPressed(' ');
  }

  // ========== SCOREBOARD NAVIGATION ==========
  if (currentGameState == STATE_SCOREBOARD) {
    // Esc (27) or Backspace (8) to return
    if ((isKeyPressed(27) && !prevKeyState[27]) || (isKeyPressed(8) && !prevKeyState[8])) {
      currentGameState = STATE_MAIN_MENU;
    }
    prevKeyState[27] = isKeyPressed(27);
    prevKeyState[8] = isKeyPressed(8);
  }

  // ========== PLAYER SELECTION NAVIGATION ==========
  if (currentGameState == STATE_CONTINUE) {
    // Esc to cancel and return to menu
    if (isKeyPressed(27) && !prevKeyState[27]) {
      currentGameState = STATE_MAIN_MENU;
    }
    prevKeyState[27] = isKeyPressed(27);
  }

  // ========== STORY UPDATE ==========
  if (currentGameState == STATE_STORY) {

    // Per-part data
    static const double storyDuration[3] = {14.636, 18.162, 27.331};
    static const int storyLineCount[3] = {3, 4, 5};

    static const char* storyLines[3][5] = {
      {
        "The world was still bright. I stepped onto the university bus as usual,",
        "backpack heavy, head full of plans. I didn't even look twice at the driver.",
        "I just wanted to attend classes as usual.",
        NULL, NULL
      },
      {
        "Time slowed down. The roar of the train was deafening - a wall of blue and yellow steel",
        "screaming across the tracks. The bus felt like paper. Shattering glass,",
        "the smell of burning oil, and a crushing weight.",
        "That was the last thing I remember.",
        NULL
      },
      {
        "Cold. That's what woke me up. I wasn't on the bus anymore.",
        "I wasn't on the tracks. I opened my eyes to a ceiling of rusted pipes and shadows.",
        "My head throbbed, and the air tasted like copper and old machinery.",
        "\"Where am I...?\" I'm alive, but I'm not home.",
        "I don't know this place, but the heavy iron door in front of me is the only way out. It's time to move."
      }
    };

    // Compute total character count for this part
    int totalChars = 0;
    for (int li = 0; li < storyLineCount[storyPart]; li++) {
      if (storyLines[storyPart][li]) totalChars += (int)strlen(storyLines[storyPart][li]);
    }

    // Delta time
    clock_t now = clock();
    double dt = (double)(now - storyLastTick) / CLOCKS_PER_SEC;
    storyLastTick = now;
    storyTimer += dt;

    // SPACE key skips the current phase
    bool spaceJustPressed = isKeyPressed(' ') && !prevKeyState[(unsigned char)' '];
    prevKeyState[(unsigned char)' '] = isKeyPressed(' ');

    if (storyPhase == 0) {
      // --- Typewriter phase ---
      double ratio = storyTimer / storyDuration[storyPart];
      if (ratio > 1.0) ratio = 1.0;
      storyCharsShown = (int)(ratio * totalChars);

      // Phase ends when audio duration elapsed (or SPACE)
      if (storyTimer >= storyDuration[storyPart] || spaceJustPressed) {
        storyCharsShown = totalChars;
        storyPhase = 1;       // enter 1.5s text-hold phase
        storyTimer = 0.0;
        // Signal audio manager: silence while text is held
        storyAudioAction = 4;
        storyAudioPlaying = false;
      }

    } else if (storyPhase == 1) {
      // --- Text hold phase: full text stays visible for 1.5s ---
      if (storyTimer >= 1.5 || spaceJustPressed) {
        storyPhase = 2;       // enter image phase
        storyTimer = 0.0;
      }

    } else {
      // --- Image display phase (storyPhase == 2, 3 seconds) ---
      if (storyTimer >= 3.0 || spaceJustPressed) {
        if (storyPart < 2) {
          // Advance to next part
          storyPart++;
          storyPhase = 0;
          storyTimer = 0.0;
          storyCharsShown = 0;
          // Signal audio manager to play next part
          storyAudioAction = storyPart + 1;

        } else {
          // Story done — signal manager to restart background music
          // Force-reset the tracker so the manager always re-triggers action 0
          currentStoryAudioState = -1;
          storyAudioAction = 0;

          hero.isDead = false;
          hero.isDying = false;
          currentImage = staticChar;
          hero.x = 0;
          hero.y = obstacleHeight;
          imageLoop = 0;
          levelDone = false;
          levelCount = 1;
          rageDeaths = 0;
          subLevelCount1 = 1;
          levelDefining();
          for (int i = 0; i < noOfObj; i++) {
            obj[i].x = obj[i].innitialX;
            obj[i].y = obj[i].innitialY;
            obj[i].state = 0; // reset ping-pong direction
          }
          currentGameState = STATE_GAMEPLAY;
        }
      }
    }
  }


  if (currentGameState == STATE_GAMEPLAY) {

    // Shield timer: deactivate after 5 seconds
    if (shieldActive) {
      double elapsed = (double)(clock() - shieldStartTime) / CLOCKS_PER_SEC;
      if (elapsed >= 5.0) {
        shieldActive = false;
      }
    }

    for (int i = 0; i < noOfObj; i++) {
      // Level 5 type-2 platforms use a dedicated oscillating function so
      // they move endlessly up/down.  Every other object in every level
      // (sawblades, doors, ghosts, and non-platform level-5 objects) still
      // goes through the original triggerTrap – nothing there changes.
      if (levelCount == 5 && obj[i].type == 2) {
        triggerMovingPlatform(obj[i], hero);
      } else {
        triggerTrap(obj[i], hero);
      }
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
      obj[i].state = 0; // reset ping-pong direction
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

  // SPACE stops background music only during gameplay (not during story)
  if (isKeyPressed(' ') && currentGameState == STATE_GAMEPLAY) {
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
    rageDeaths++;

    // Update global player death count and save
    if (currentPlayerIndex >= 0 && currentPlayerIndex < totalPlayers) {
      allPlayers[currentPlayerIndex].deaths++;
      saveGameData();
    }

    if (rageDeaths >= RAGE_MAX) {
      // Rage meter full — reset to sublevel 1 of current level
      rageDeaths = 0;
      if (levelCount == 1) subLevelCount1 = 1;
      else if (levelCount == 2) subLevelCount2 = 1;
      else if (levelCount == 3) subLevelCount3 = 1;
      levelDefining();
    }

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
      obj[i].state = 0; // reset ping-pong direction
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

// ========== STORY AUDIO MANAGER (runs on its own WM_TIMER) ==========
// Reads the global storyAudioAction flag and performs MCI operations.
// Actions: 0=idle/gameplay (bgsong), 1=play story1, 2=play story2, 3=play story3, 4=silence
// Uses a close/open guard for bgsong so it always works regardless of prior state.

void storyAudioManager() {
  if (currentStoryAudioState == storyAudioAction) return;

  // Stop all story tracks — these are always open so this is safe
  mciSendString("stop story1", NULL, 0, NULL);
  mciSendString("stop story2", NULL, 0, NULL);
  mciSendString("stop story3", NULL, 0, NULL);
  // Stop bgsong only if we are leaving gameplay (action was 0)
  if (currentStoryAudioState == 0) {
    mciSendString("stop bgsong", NULL, 0, NULL);
  }

  if (storyAudioAction == 0) {
    // Returning to gameplay: reopen bgsong (close first in case it is still open)
    mciSendString("close bgsong", NULL, 0, NULL);
    mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0, NULL);
    if (vol) {
      mciSendString("play bgsong repeat", NULL, 0, NULL);
    }
  } else if (storyAudioAction == 1) {
    mciSendString("seek story1 to start", NULL, 0, NULL);
    mciSendString("play story1", NULL, 0, NULL);
  } else if (storyAudioAction == 2) {
    mciSendString("seek story2 to start", NULL, 0, NULL);
    mciSendString("play story2", NULL, 0, NULL);
  } else if (storyAudioAction == 3) {
    mciSendString("seek story3 to start", NULL, 0, NULL);
    mciSendString("play story3", NULL, 0, NULL);
  } else if (storyAudioAction == 4) {
    // Absolute silence between phases — nothing to do
  }

  currentStoryAudioState = storyAudioAction;
}

int main() {

  // Opening/Loading all the audio devices in main
  mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0, NULL);
  mciSendString("open \"Audios//first_part_story.mp3\" alias story1", NULL, 0, NULL);
  mciSendString("open \"Audios//second_part_story.mp3\" alias story2", NULL, 0, NULL);
  mciSendString("open \"Audios//third_part_story.mp3\" alias story3", NULL, 0, NULL);

  storyAudioAction = 0; // Starts by playing BGM if vol acts

  iInitialize(screenWidth, screenHeight, "RageRush");

  glutKeyboardFunc(myKeyboard);

  initImages();
  loadGameData();
  levelDefining();

  iSetTimer(30, changeSawbladeFrame);
  iSetTimer(50, storyAudioManager);  // Poll for audio state changes

  iStart();
  return 0;
}