#ifndef CONST_H
#define CONST_H

#include <string>

const std::string FILES_LIST[] = {"menuBackground.png", "FOND1.png", "FOND2.png","Rules.png","BonusList.png", "character.png", "bonus.png", "buttons.png", "obstacles_block.png", "life.png", "logo.jpeg", "explosion.png", "coin.png", "plane.png", "mine.png"};

const std::string FONTS_LIST[] = {"score.ttf"};

enum text_effect{NOTHING, BREATH, FLASH};


const std::string PATTERNS_FILE = "Ressources/patternsList.xml";
const int GAME_SIZE_W = 1280;
const int GAME_SIZE_H = 720;
const int MENU_SIZE_W = 800;
const int MENU_SIZE_H = 600;
const unsigned int MAX_LIFE = 100;
const unsigned int HAUTEUR_SOL = 520;
const float GRAVITY = 0.15;
const float CHARACTER_MAX_SPEED = 5;
const float ACCELERATION_CHARACTER = 0.2;
const int CHARACTERSPEEDPERIOD = 10;
const int FPS = 60;
const int STARTSPEEDPERIODGAME = 15;
const int PIXELPERBACKGROUNDMOVE = 3;
const int ACCELERATION_PERIOD = 30;     //en secondes
const float PI = 3.14159265359;


#endif // CONST_H
