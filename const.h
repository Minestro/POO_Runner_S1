#ifndef CONST_H
#define CONST_H

#include <string>


const std::string FONTS_LIST[] = {"score.ttf"};

const std::string PATTERNS_FILE = "Ressources/patternsList.xml";

enum text_effect{NOTHING, BREATH, FLASH};

const int MODEL_SIZE_W = 1280;
const int MODEL_SIZE_H = 720;
const unsigned int HUD_Z_INDEX = 10;
const unsigned int MENU_Z_INDEX = 15;
const unsigned int MAX_LIFE = 100;
const unsigned int HAUTEUR_SOL = 630;
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
