#ifndef IMAGES_H
#define IMAGES_H

int logo, newgamebut, continuebut, volon, voloff, scores, levelbut, background1;
int rightmove1, rightmove2, rightmove3, currentImage;
int leftmove1, leftmove2, leftmove3;
int leftjump1, leftjump2, leftjump3, leftjump4, leftjump5;
int rightjump3;
int characterRightArray[9] = { rightmove1, rightmove1, rightmove1, rightmove2, rightmove2, rightmove2, rightmove3, rightmove3, rightmove3 };
int characterLeftArray[9];
int characterLeftJumpArray[10];
int characterDieArray[15];
int staticChar;
int platform, base, brick1, spikes1;

int objImg[] = { spikes1 };


void initImages() {
	logo = iLoadImage("Images//logo3.png");
	newgamebut = iLoadImage("Images//newgame.png");
	continuebut = iLoadImage("Images//continue.png");
	volon = iLoadImage("Images//volon.png");
	voloff = iLoadImage("Images//voloff.png");
	scores = iLoadImage("Images//score2.png");
	levelbut = iLoadImage("Images//levels.png");
	rightmove1 = iLoadImage("Images//character/rightmove1.png");
	rightmove2 = iLoadImage("Images//character/rightmove2.png");
	rightmove3 = iLoadImage("Images//character/rightmove3.png");
	rightjump3 = iLoadImage("Images//character/rightjump3.png");
	background1 = iLoadImage("Images//background2.png");
	staticChar = iLoadImage("Images//character/static.png");
	currentImage = iLoadImage("Images//character/static.png");
	platform = iLoadImage("Images//platform.png");
	base = iLoadImage("Images//base.png");
	brick1 = iLoadImage("Images//brick1.png");
	spikes1 = iLoadImage("Images//spikes1.png");

	int idx = 0;
	for (int i = 0; i < 3; i++) {
		characterRightArray[idx] = iLoadImage("Images//character/rightmove1.png");
		characterLeftArray[idx] = iLoadImage("Images//character/leftmove1.png");
		idx++;
	}
	for (int i = 0; i < 3; i++) {
		characterRightArray[idx] = iLoadImage("Images//character/rightmove2.png");
		characterLeftArray[idx] = iLoadImage("Images//character/leftmove2.png");
		idx++;
	}
	for (int i = 0; i < 3; i++) {
		characterRightArray[idx] = iLoadImage("Images//character/rightmove3.png");
		characterLeftArray[idx] = iLoadImage("Images//character/leftmove3.png");
		idx++;
	}

	int idx2 = 0;
	for (int i = 0; i < 2; i++) {
		//characterRightJumpArray[idx] = iLoadImage("Images//character/rightmove1.png");
		characterLeftJumpArray[idx2] = iLoadImage("Images//character/leftjump1.png");
		idx2++;
	}
	for (int i = 0; i < 2; i++) {
		//characterRightArray[idx] = iLoadImage("Images//character/rightmove2.png");
		characterLeftJumpArray[idx2] = iLoadImage("Images//character/leftjump2.png");
		idx2++;
	}
	for (int i = 0; i < 2; i++) {
		//characterRightArray[idx] = iLoadImage("Images//character/rightmove3.png");
		characterLeftJumpArray[idx2] = iLoadImage("Images//character/leftjump3.png");
		idx2++;
	}
	for (int i = 0; i < 2; i++) {
		//characterRightArray[idx] = iLoadImage("Images//character/rightmove3.png");
		characterLeftJumpArray[idx2] = iLoadImage("Images//character/leftjump4.png");
		idx2++;
	}
	for (int i = 0; i < 2; i++) {
		//characterRightArray[idx] = iLoadImage("Images//character/rightmove3.png");
		characterLeftJumpArray[idx2] = iLoadImage("Images//character/leftjump5.png");
		idx2++;
	}

	int idx3 = 0;
	for (int i = 0; i < 3; i++) {
		characterDieArray[idx3] = iLoadImage("Images//character/death1.png");
		idx3++;
	}
	for (int i = 0; i < 3; i++) {
		characterDieArray[idx3] = iLoadImage("Images//character/death2.png");
		idx3++;
	}
	for (int i = 0; i < 3; i++) {
		characterDieArray[idx3] = iLoadImage("Images//character/death3.png");
		idx3++;
	}
	for (int i = 0; i < 3; i++) {
		characterDieArray[idx3] = iLoadImage("Images//character/death4.png");
		idx3++;
	}
	for (int i = 0; i < 3; i++) {
		characterDieArray[idx3] = iLoadImage("Images//character/death5.png");
		idx3++;
	}

	objImg[0] = iLoadImage("Images//spikes1.png");

}


#endif