/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#ifndef CONST_H
#define CONST_H

#include <string>
#include <set>

const std::string FILES_LIST[] = {"menuBackground.png", "FOND1.png", "FOND2.png", "FOND.png", "textBox.png", "buttons.png", "life.png", "logo.jpeg", "explosion.png", "coin.png", "plane.png", "mine.png", "leftKey.png", "rightKey.png", "downKey.png", "upKey.png","Soins.png", "radioButton.png", "nuages.png", "BarreObstacle.png", "Invincibility.png", "savesButton.png", "magnet.png", "Slow.png"};

const std::string FONTS_LIST[] = {"score.ttf", "Beautiful_Heartbeat.otf", "The_Happy_Giraffe.ttf"};

const std::string SOUNDS_LIST[] = {"coin.wav", "plane.wav", "explosion.wav", "crash.wav", "click.wav", "bonus.wav"};

const std::string MUSIC_GAME_FILE = "Ressources/Default/Musics/arcade.ogg";

const std::string MUSIC_MENU_FILE = "Ressources/Default/Musics/welcome_screen.ogg";

const std::string PATTERNS_FILE = "Ressources/patternsList.xml";
const std::string MENU_MODELS_FILE = "Ressources/menu.xml";
const std::string SAVE_FILE = "Ressources/save.xml";
const std::string SETTINGS_FILE = "settings.config";

const std::set<std::string> KEY_MESSAGES = {"ERASE", "LOAD", "NEW", "BSCORE", "MONEY", "EMPTY", "PLAY", "SHOP", "RULES", "SETTINGS", "QUIT", "DURATION", "UPGRADE", "COST", "INVINCIBILITY", "MAGNETISATION", "SLOWTIME", "RULESDES", "MOVEF", "MOVEB", "ASCEND", "BONUSLIST", "RETURN", "BONUS", "COINDES", "INVINDES", "MEDICDES", "MAGNETDES", "SLOWTIMEDES", "OBSTACLESLIST", "OBSTACLE", "CLOUDDES", "BARDES", "MINEDES", "FULLSCREEN", "MUSIQUE", "SOUND", "GAMEINTRO", "MENUINTRO", "RESUME", "PAUSE", "NEWHIGHSCORE", "SCORE", "SELECTPROFILE", "COMFIRM", "ENTERNICKNAME", "YOURDEAD"};

enum text_effect{NOTHING, BREATH, FLASH};

const int MODEL_SIZE_W = 1280;
const int MODEL_SIZE_H = 720;
const int FPS = 60;         //La limite de FPS

const unsigned int HUD_Z_INDEX = 10;    //ZIndex pour les éléments du HUD
const unsigned int MENU_Z_INDEX = 15;   //zIndex pour les éléments du menu

const unsigned int MAX_LIFE = 100;
const unsigned int INVINCIBILITY_TIME_AFTER_HIT_MS = 2000;      //Periode pendant laquelle le joueur se retrouve invincible après avoir été touché par un obstacle
const unsigned int ROOF_HEIGHT = 630;       //Hauteur du sol en y
const float GRAVITY = 0.15;                 //Ratio de gravité
const float CHARACTER_MAX_SPEED = 5;
const float ACCELERATION_CHARACTER = 0.2;
const int CHARACTERSPEEDPERIOD = 10;        //En quelque sorte la vitesse du joueur. C'est la période d'appel à la méthode move du joueur. A ceci s'ajoute CHARATER_MAX_SPEED qui définit la vitesse max mais en pixels par déplacement.
const int STARTSPEEDPERIODGAME = 15;        //Période de mouvement au début du jeu (donc sa vitesse)
const int PIXELPERBACKGROUNDMOVE = 3;
const int ACCELERATION_PERIOD = 30;     //Periode de l'accéleration du jeu en secondes

const float MAGNET_RADIUS = 200.0;      //Rayon d'action du bonus magnet en pixels
const unsigned int UPGRADE_COST = 1000;
const unsigned int SEC_PER_UPGRADE = 5;
const unsigned int MAX_UPGRADE_SEC = 30;
const unsigned int DEFAULT_UPGRADE_SEC = 5;
const unsigned int NB_MAX_SAVES = 5;
const unsigned int MAX_NICKNAME_LENGHT = 20;

const float PI = 3.14159265359;


#endif // CONST_H
