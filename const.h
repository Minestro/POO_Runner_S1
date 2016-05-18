#ifndef CONST_H
#define CONST_H

#include <string>

const std::string FILES_LIST[] = {"menuBackground.png", "FOND1.png", "FOND2.png", "FOND.png", "textBox.png", "buttons.png", "life.png", "logo.jpeg", "explosion.png", "coin.png", "plane.png", "mine.png", "leftKey.png", "rightKey.png", "downKey.png", "upKey.png","Soins.png", "radioButton.png", "nuages.png", "BarreObstacle.png", "Invincibility.png", "savesButton.png"};

const std::string FONTS_LIST[] = {"score.ttf", "Beautiful_Heartbeat.otf", "The_Happy_Giraffe.ttf"};

const std::string PATTERNS_FILE = "Ressources/patternsList.xml";
const std::string MENU_MODELS_FILE = "Ressources/menu.xml";
const std::string SAVE_FILE = "Ressources/save.xml";

enum text_effect{NOTHING, BREATH, FLASH};

const int MODEL_SIZE_W = 1280;
const int MODEL_SIZE_H = 720;
const int FPS = 60;

const unsigned int HUD_Z_INDEX = 10;
const unsigned int MENU_Z_INDEX = 15;
const unsigned int MAX_LIFE = 100;
const unsigned int HAUTEUR_SOL = 630;
const float GRAVITY = 0.15;
const float CHARACTER_MAX_SPEED = 5;
const float ACCELERATION_CHARACTER = 0.2;
const int CHARACTERSPEEDPERIOD = 10;
const int STARTSPEEDPERIODGAME = 15;
const int PIXELPERBACKGROUNDMOVE = 3;
const int ACCELERATION_PERIOD = 30;     //en secondes
const unsigned int UPGRADE_COST = 1000;
const unsigned int SEC_PER_UPGRADE = 3;
const unsigned int MAX_UPGRADE_SEC = 15;
const unsigned int DEFAULT_UPGRADE_SEC = 5;
const unsigned int NB_MAX_SAVES = 5;

const float PI = 3.14159265359;


#endif // CONST_H
