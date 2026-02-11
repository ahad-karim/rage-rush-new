#include "iGraphics.h"
#include "GameData.h"
#include "Physics.h"
#include "Images.h"
#include "Levelone.h"
#include <mmsystem.h>
#include <string>
#include <time.h>
#pragma comment(lib, "winmm.lib")

//int gameState = 0;
bool vol = true;


char inputName[50] = "";
int nameIndex = 0;
int imageLoop = 0;
bool isLeft = false;
int doi = 0;
int diddy = 8;


//Do not remove this line!!!!!!
GameState currentGameState = STATE_MAIN_MENU;
Player hero = { 0, obstacleHeight, 5, 15, false, false, 50, 80, false };



void iDraw()
{
	iClear();

	if (currentGameState == STATE_MAIN_MENU) {
		// --- DRAW MAIN MENU ---
		//iSetColor(30, 30, 30); // Background Brown
		//iFilledRectangle(0, 0, 1080, 600);
		iShowImage(0, 0, 1080, 600, menubg);

		iSetColor(255, 255, 255); // White for boxes

		// Logo (Top Center)
		//iRectangle(390, 450, 300, 160);
		//iText(520, 525, "Logo");
		//iShowBMP(390, 450, "logo1.bmp");
		iShowImage(390, 325, 300, 300, logo);

		// Name Box (Middle)
		//iRectangle(390, 375, 300, 70);
		//iText(520, 405, "RageRush");

		// "Con" Button (Bottom Left)
		//iRectangle(215, 250, 240, 80);
		//iText(320, 285, "Continue");
		iShowImage(285, 255, 215, 65, continuebut);

		// "New Game" Button (Bottom Right)
		//iRectangle(550, 250, 240, 80);
		//iText(620, 285, "New Game");
		iShowImage(580, 250, 240, 80, newgamebut);

		//score button
		iShowImage(440, 165, 180, 95, scores);

		//levels button
		iShowImage(440, 90, 180, 95, levelbut);

		if (vol) {
			iShowImage(0, 0, 70, 70, volon);
		}
		else {
			iShowImage(0, -1, 70, 70, voloff);
		}
	}
	else if (currentGameState == STATE_ENTER_NAME) {
		// Brown Background
		iSetColor(180, 110, 80);
		iFilledRectangle(0, 0, 1080, 600);

		iSetColor(255, 255, 255);
		iText(420, 400, "ENTER YOUR NAME:", GLUT_BITMAP_HELVETICA_18);

		// Input Box
		iRectangle(390, 340, 300, 50);

		// Render the string we are building
		iText(405, 360, inputName, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (currentGameState == STATE_GAMEPLAY) {
		// Brown rectangular box of size 1080 * 200 (at the top)
		iFilledRectangle(0, 0, 1080, 200);
		// --- DRAW LEVEL 1 PAGE ---

		iSetColor(180, 110, 80); // Background Brown
		iFilledRectangle(0, 0, 1080, 600);
		//iShowImage(0, 0, 1080, 600, background1);

		iSetColor(120, 70, 50); // A slightly different brown for the UI box


		iSetColor(255, 255, 255);
		// "Level 1" at top center
		// Note: GLUT_BITMAP_TIMES_ROMAN_24 is the largest standard font.
		iText(490, 550, "Level 1", GLUT_BITMAP_TIMES_ROMAN_24);
		for (int i = 0; i < 20; i++) {
			iShowImage(i * 100, 0, 100, 20, brick1);
			iShowImage(i * 100-25, 20, 100, 20, brick1);
			iShowImage(i * 100, 40, 100, 20, brick1);
		}
		for (int i = 0; i < noOfObj; i++) {
			iShowImage(obj[i].x, obj[i].y, obj[i].width, obj[i].height, objImg[obj[i].type]);
		}
		iShowImage(hero.x, hero.y, 50, 50, currentImage);

		if (hero.isDead) {
			iText(470, 250, "Game Over", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

}


//New stuff start

void saveGameData() {
	FILE *fp;
	// fopen_s returns 0 if successful
	errno_t err = fopen_s(&fp, "savegame.txt", "w");

	if (err != 0 || fp == NULL) return;

	for (int i = 0; i < totalPlayers; i++) {
		fprintf(fp, "%s %d %d\n", allPlayers[i].name, allPlayers[i].level, allPlayers[i].deaths);
	}
	fclose(fp);
}

void loadGameData() {
	FILE *fp;
	errno_t err = fopen_s(&fp, "savegame.txt", "r");

	if (err != 0 || fp == NULL) return;

	totalPlayers = 0;
	// Check if totalPlayers is within bounds of your array (e.g., 100)
	while (totalPlayers < 100 && fscanf_s(fp, "%s %d %d", allPlayers[totalPlayers].name, (unsigned)_countof(allPlayers[totalPlayers].name),
		&allPlayers[totalPlayers].level, &allPlayers[totalPlayers].deaths) != EOF) {
		totalPlayers++;
	}
	fclose(fp);
}

//New stuff end


//New stuff

void registerNewPlayer(char* name) {
	// 1. Check if we have space in our array (max 100 players)
	if (totalPlayers >= 100) {
		printf("Error: Player database full!\n");
		return;
	}

	// 2. Copy the name from the input buffer to our permanent player list
	// We use strcpy_s for the safety Visual Studio requested earlier
	strcpy_s(allPlayers[totalPlayers].name, sizeof(allPlayers[totalPlayers].name), name);

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
		}
		else if (key == '\b') { // Backspace
			if (nameIndex > 0) {
				nameIndex--;
				inputName[nameIndex] = '\0';
			}
		}
		else if (key >= 32 && key <= 126) { // Printable characters
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



//end of new stuff

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Only check for clicks if we are currently on the menu
		if (currentGameState == STATE_MAIN_MENU) {
			

			//New game button click
			if (mx >= 550 && mx <= 790 && my >= 250 && my <= 330) {
				//currentGameState = STATE_ENTER_NAME; // Naming state
				currentGameState = STATE_GAMEPLAY;

				nameIndex = 0;
				inputName[0] = '\0';

				// Logic for "Registering new player"
				//printf("New Player Registered. Loading Level 1...\n");
			}

			//changing volume
			if (mx >= 0 && my >= 0 && mx <= 70 && my <= 70) {
				vol = !vol;
				// Opening/Loading the audio files
				mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0, NULL);
				//mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);




				// mciSendString("close ggsong", NULL, 0, NULL);
				if (vol) {
					// Playing the background audio on repeat
					mciSendString("play bgsong repeat", NULL, 0, NULL);
				}
				else {
					// If the use of an audio is finished, close it to free memory
					mciSendString("stop bgsong", NULL, 0, NULL);
				}
				
			}
		}
		else if (currentGameState == STATE_GAMEPLAY) {
			//Temporary
			currentGameState = STATE_MAIN_MENU;
		}
		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT


bool wasMovingLastFrame = false;
clock_t lastTime = 0;
double interval = 1.5;
void fixedUpdate()
{
	
	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP))
	{
		jumpStart = true;
		
		if (imageLoop == 9) {
			imageLoop = 0;
		}
		else {
			imageLoop++;
		}

		if (isLeft) {
			currentImage = characterLeftJumpArray[5];
			updatePlayerPhysics(hero, isLeft);
		}
		else {
			currentImage = rightjump3;
			updatePlayerPhysics(hero, isLeft);
		}
	}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
	{
		isLeft = true;
		
		if (imageLoop == 8) {
			imageLoop = 0;
		}
		else {
			imageLoop++;
		}
		if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {
				currentImage = characterLeftJumpArray[5];
			
		}
		else {
			currentImage = characterLeftArray[imageLoop];
		}
		
		hero.x -= hero.dx;
		if (hero.x <= 0) {
			hero.x = 0;
		}
	}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN))
	{
		if (imageLoop == 14) {
			imageLoop = 14;
			hero.isDead = true;
		}
		else {
			imageLoop++;
		}
		hero.isDying = true;

		currentImage = characterDieArray[imageLoop];
	}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{
		isLeft = false;
		if (imageLoop == 8) {
			imageLoop = 0;
		}
		else {
			imageLoop++;
		}

		if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			currentImage = rightjump3;

		}
		else {
			currentImage = characterRightArray[imageLoop];
		}

		hero.x += hero.dx;
		if (hero.x >= 980) {
			hero.x = 980;
		}
	}

	if (isKeyPressed(' ')) {
		// Playing the audio once
		//mciSendString("play ggsong from 0", NULL, 0, NULL);
		//currentImage = iLoadImage("Images//character/static.png");
	}
	bool isMoving = (isKeyPressed('a') || isKeyPressed('d') ||
		isSpecialKeyPressed(GLUT_KEY_LEFT) || isSpecialKeyPressed(GLUT_KEY_RIGHT) || isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP));

	if (hero.isDying) {
		if (imageLoop == 14) {
			imageLoop = 14;
			hero.isDead = true;
		}
		else {
			imageLoop++;
		}

		currentImage = characterDieArray[imageLoop];
	}

	if (hero.isDead) {
		currentGameState = STATE_MAIN_MENU;
		hero.isDead = false;
		hero.isDying = false;
		currentImage = staticChar;
		hero.x = 0;
		hero.y = obstacleHeight;
		imageLoop = 0;
	}
	

	if (hero.y > obstacleHeight || !hero.isGrounded) {
		// Apply gravity gradually
		if (hero.dy > obstacleHeight && !isMoving) {
			hero.dy = 0;
		}
		hero.dy += gravity;
		hero.y += hero.dy;
		imageLoop = 0;


		// Ground Collision
		if (hero.y <= obstacleHeight) {
			hero.y = obstacleHeight;
			hero.dy = 15; // Reset velocity
			hero.isGrounded = true;

			// Set landing image
			currentImage = staticChar;
			imageLoop = 0;
		}
	}

	if (wasMovingLastFrame && !isMoving && hero.y <= obstacleHeight) {
		printf("Movement Stopped!\n");
		currentImage = staticChar;
		imageLoop = 0;
		// We don't need a loop here anymore. 
		// The physics block above will catch that hero.y > 0 and start the fall.
	}



	wasMovingLastFrame = isMoving;
}











int main()
{
	
	// Opening/Loading the audio files
	mciSendString("open \"Audios//RageRush_bgm.mp3\" alias bgsong", NULL, 0, NULL);
	//mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);




	// mciSendString("close ggsong", NULL, 0, NULL);
	if (vol) {
		// Playing the background audio on repeat
		mciSendString("play bgsong repeat", NULL, 0, NULL);
	}
	else {
		// If the use of an audio is finished, close it to free memory
		mciSendString("stop bgsong", NULL, 0, NULL);
	}
	iInitialize(1080, 600, "RageRush");

	

	glutKeyboardFunc(myKeyboard);

	initImages();

	iStart();
	return 0;
}