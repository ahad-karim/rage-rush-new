#ifndef IMAGES_H
#define IMAGES_H

int logo, newgamebut, newgameHover, continuebut, continueHover, volon, voloff,
    scores, scoresHover, levelbut, levelbutHover, background1, menubg,
    sublevel1bg, sublevel2bg, sublevel3bg, sublevel4bg, win, gameover;
int rightmove1, rightmove2, rightmove3, currentImage;
int leftmove1, leftmove2, leftmove3;
int leftjump1, leftjump2, leftjump3, leftjump4, leftjump5;
int rightjump3;
int characterRightArray[9] = {rightmove1, rightmove1, rightmove1,
                              rightmove2, rightmove2, rightmove2,
                              rightmove3, rightmove3, rightmove3};
int characterLeftArray[9];
int characterLeftJumpArray[10];
int characterDieArray[15];
int staticChar;
int platform, base, brick1, spikes1, door, sawblade, ghostImg;
int sawbladeArray[8];
int sawbladeFrame = 0;
int l1bg[4];
int l2bg[4];
int l3bg[4];
int l4bg[4];
int l5bg[4];
int orbImg, shieldImg;
int intro1, intro2, intro3, intro4; // Story / win images

int objImg[8] = {
    spikes1,  door,     platform,
    sawblade, platform, ghostImg, door, 0}; // 7=Orb
int sublevelbgArray[4];

void initImages() {
  logo = iLoadImage("Images//logo3.png");
  newgamebut = iLoadImage("Images//newgame.png");
  newgameHover = iLoadImage("Images//newgameHover.png");
  continuebut = iLoadImage("Images//continue.png");
  continueHover = iLoadImage("Images//continueHover.png");
  volon = iLoadImage("Images//volon.png");
  voloff = iLoadImage("Images//voloff.png");
  scores = iLoadImage("Images//score2.png");
  scoresHover = iLoadImage("Images//score2Hover.png");
  levelbut = iLoadImage("Images//levels.png");
  levelbutHover = iLoadImage("Images//levelsHover.png");
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
  menubg = iLoadImage("Images//menubg.png");
  sublevel1bg = iLoadImage("Images//sublevel1bg.png");
  sublevel2bg = iLoadImage("Images//sublevel2bg.png");
  sublevel3bg = iLoadImage("Images//sublevel3bg.png");
  sublevel4bg = iLoadImage("Images//sublevel4bg.png");
  door = iLoadImage("Images//door.png");
  // Story / win images
  intro1 = iLoadImage("Images//intro1.png");
  intro2 = iLoadImage("Images//intro2.png");
  intro3 = iLoadImage("Images//intro3.png");
  intro4 = iLoadImage("Images//intro4.png");

  win = iLoadImage("Images//win.png");
  gameover = iLoadImage("Images//gameover.jpg");

  l1bg[0] = iLoadImage("Images//l1s1bg.png");
  l1bg[1] = iLoadImage("Images//l1s2bg.png");
  l1bg[2] = iLoadImage("Images//l1s3bg.png");
  l1bg[3] = iLoadImage("Images//l1s4bg.png");

  l2bg[0] = iLoadImage("Images//l2s1bg.png");
  l2bg[1] = iLoadImage("Images//l2s2bg.png");
  l2bg[2] = iLoadImage("Images//l2s3bg.png");
  l2bg[3] = iLoadImage("Images//l2s4bg.png");

  l3bg[0] = iLoadImage("Images//l3s1bg.png");
  l3bg[1] = iLoadImage("Images//l3s2bg.png");
  l3bg[2] = iLoadImage("Images//l3s3bg.png");
  l3bg[3] = iLoadImage("Images//l3s4bg.png");

  // Level 4 backgrounds
  l4bg[0] = iLoadImage("Images//l4s1bg.png");
  l4bg[1] = iLoadImage("Images//l4s2bg.png");
  l4bg[2] = iLoadImage("Images//l4s3bg.png");
  l4bg[3] = iLoadImage("Images//l4s4bg.png");

  // Level 5 backgrounds
  l5bg[0] = iLoadImage("Images//l5s1bg.png");
  l5bg[1] = iLoadImage("Images//l5s2bg.png");
  l5bg[2] = iLoadImage("Images//l5s3bg.png");
  l5bg[3] = iLoadImage("Images//l5s4bg.png");

  // Orb and Shield
  orbImg   = iLoadImage("Images//orb.png");
  shieldImg = iLoadImage("Images//shield.png");


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
    // characterRightJumpArray[idx] =
    // iLoadImage("Images//character/rightmove1.png");
    characterLeftJumpArray[idx2] =
        iLoadImage("Images//character/leftjump1.png");
    idx2++;
  }
  for (int i = 0; i < 2; i++) {
    // characterRightArray[idx] =
    // iLoadImage("Images//character/rightmove2.png");
    characterLeftJumpArray[idx2] =
        iLoadImage("Images//character/leftjump2.png");
    idx2++;
  }
  for (int i = 0; i < 2; i++) {
    // characterRightArray[idx] =
    // iLoadImage("Images//character/rightmove3.png");
    characterLeftJumpArray[idx2] =
        iLoadImage("Images//character/leftjump3.png");
    idx2++;
  }
  for (int i = 0; i < 2; i++) {
    // characterRightArray[idx] =
    // iLoadImage("Images//character/rightmove3.png");
    characterLeftJumpArray[idx2] =
        iLoadImage("Images//character/leftjump4.png");
    idx2++;
  }
  for (int i = 0; i < 2; i++) {
    // characterRightArray[idx] =
    // iLoadImage("Images//character/rightmove3.png");
    characterLeftJumpArray[idx2] =
        iLoadImage("Images//character/leftjump5.png");
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
  objImg[1] = iLoadImage("Images//door.png");
  objImg[2] = iLoadImage("Images//platform.png");
  objImg[3] = iLoadImage("Images//sawblade1.png");
  objImg[4] = iLoadImage("Images//platform.png");

  ghostImg = iLoadImage("Images//ghost.png");
  objImg[5] = ghostImg;
  objImg[6] = iLoadImage("Images//door.png");
  objImg[7] = orbImg;

  sublevelbgArray[0] = sublevel1bg;
  sublevelbgArray[1] = sublevel2bg;
  sublevelbgArray[2] = sublevel3bg;
  sublevelbgArray[3] = sublevel4bg;

  sawbladeArray[0] = iLoadImage("Images//blade1.png");
  sawbladeArray[1] = iLoadImage("Images//blade2.png");
  sawbladeArray[2] = iLoadImage("Images//blade3.png");
  sawbladeArray[3] = iLoadImage("Images//blade4.png");
  sawbladeArray[4] = iLoadImage("Images//blade5.png");
  sawbladeArray[5] = iLoadImage("Images//blade6.png");
  sawbladeArray[6] = iLoadImage("Images//blade7.png");
  sawbladeArray[7] = iLoadImage("Images//blade8.png");
}

#endif