#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RunnerTest

/*#include <boost/test/unit_test.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include "game.h"
#include "model.h"
#include "menu.h"
#include "graphicelement.h"

// les tests groupes par "cas"

//On regarde que les obstacles et les bons se deplacent bien
BOOST_AUTO_TEST_CASE(test_moveObstacleBonus)
{
    Obstacle ob {GAME_SIZE_W, HAUTEUR_SOL- 30, 30,30, -PIXELPERBACKGROUNDMOVE, 0, 10, 50, 1};
    Bonus bonus1{GAME_SIZE_W, HAUTEUR_SOL-60, 30,30, -PIXELPERBACKGROUNDMOVE, 0, 10,PIECE };


    BOOST_CHECK(ob.getDammage()==50);
    BOOST_CHECK(ob.getPosition().first == GAME_SIZE_W);
    BOOST_CHECK(ob.getPosition().second==HAUTEUR_SOL-30);
    ob.move();
    BOOST_CHECK(ob.getPosition().first == GAME_SIZE_W-PIXELPERBACKGROUNDMOVE);
    BOOST_CHECK(ob.getPosition().second==HAUTEUR_SOL-30);

    BOOST_CHECK(bonus1.getPosition().first == GAME_SIZE_W);
    BOOST_CHECK(bonus1.getPosition().second==HAUTEUR_SOL-60);
    bonus1.move();
    BOOST_CHECK(bonus1.getPosition().first == GAME_SIZE_W-PIXELPERBACKGROUNDMOVE);
    BOOST_CHECK(bonus1.getPosition().second==HAUTEUR_SOL-60);


}

//On test la collision entre deux élements. Ici un character et un obstacle
BOOST_AUTO_TEST_CASE(test_collision)
{
    Player player{};
    GameCharacter gc {0, 50, 50, 50, 0, 0, &player};
    Obstacle ob {49, 50, 50, 50, 5, 0, 0, 5, 1};
    BOOST_CHECK(gc.collision(&ob) == true);
    ob.move();
    BOOST_CHECK(gc.collision(&ob) == false);
    ob.setPosition(0, 0);
    BOOST_CHECK(gc.collision(&ob) == false);
    ob.setPosition(0, 1);
    BOOST_CHECK(gc.collision(&ob) == true);
}

//On test pour voir si le character perd bien de la vie lorsqu'il rencontre un obstacle
BOOST_AUTO_TEST_CASE(test_gamelife)
{
    Game *gameModel= new Game{GAME_SIZE_W, GAME_SIZE_H, STARTSPEEDPERIODGAME};
    Player p1{};
    Obstacle *ob = new Obstacle{0, HAUTEUR_SOL-40, 40,40, 0, 0, 10, 50, 1};

    gameModel->getObstacles().push_back(std::make_pair(1,ob));
    gameModel->getCharacters()[0].second->setPosition(0,HAUTEUR_SOL-gameModel->getCharacters()[0].second->getSize().second);

    BOOST_CHECK(gameModel->getCharacters()[0].second->collision(ob)==true);
    gameModel->nextStep();

    BOOST_CHECK(gameModel->getCharacters()[0].second->getLife()==50);

    delete gameModel;
}

//Test de la fonction isHover qui vérifie si le curseur est sur le bouton puis on simule un clic et on s'assure que la page du menu a changé.
BOOST_AUTO_TEST_CASE(test_button)
{
    Menu *menu = new Menu{GAME_SIZE_W, GAME_SIZE_H, 1};
    Button *button = new Button{50, 50, 200, 50, "test", 1, menu};
    BOOST_CHECK(button->isHover(60, 60) == true);
    BOOST_CHECK(button->isHover(23, 60) == false);
    BOOST_CHECK(button->isHover(60, 13) == false);
    BOOST_CHECK(button->isHover(17, 42) == false);
    BOOST_CHECK(button->isHover(630, 64) == false);
    button->onClick();
    BOOST_CHECK(menu->getActivePage()==1);
}

//Ces deux fonctions convertissent une couleur format rgb au format hsl ou inversement. Cela est utile pour les dégradés de couleur. A cause des imprecisions de calcul on test si chaque valeur est bien comprise enre deux bornes.
BOOST_AUTO_TEST_CASE(test_hslColor)
{
    BOOST_CHECK(GraphicElement::color2hsl(255, 0, 0).h == 0);
    BOOST_CHECK(GraphicElement::color2hsl(255, 0, 0).l == 0.5);
    BOOST_CHECK(GraphicElement::color2hsl(255, 0, 0).s == 1.0);

    BOOST_CHECK(GraphicElement::color2hsl(212, 216, 43).h >= 60 && GraphicElement::color2hsl(212, 216, 43).h <= 62);
    BOOST_CHECK(GraphicElement::color2hsl(212, 216, 43).l >= 0.507 && GraphicElement::color2hsl(212, 216, 43).l <= 0.509);
    BOOST_CHECK(GraphicElement::color2hsl(212, 216, 43).s >= 0.688 && GraphicElement::color2hsl(212, 216, 43).s <= 0.690);

    BOOST_CHECK(GraphicElement::hsl2color(61, 0.688, 0.508).r >= 211 && GraphicElement::hsl2color(61, 0.688, 0.508).r <= 215);
    BOOST_CHECK(GraphicElement::hsl2color(61, 0.688, 0.508).g >= 215 && GraphicElement::hsl2color(61, 0.688, 0.508).g <= 217);
    BOOST_CHECK(GraphicElement::hsl2color(61, 0.688, 0.508).b >= 40 && GraphicElement::hsl2color(61, 0.688, 0.508).b <= 43);
}

//On test si l'appel de la fonction jump sur character fait bien monter le character jusqu'à se qu'il retombe
BOOST_AUTO_TEST_CASE(test_GameCharacterJump)
{
    Game *gameModel= new Game{GAME_SIZE_W, GAME_SIZE_H, STARTSPEEDPERIODGAME};
    std::pair<float, float> oldPosition = gameModel->getCharacters()[0].second->getPosition();
    gameModel->getCharacters()[0].second->jump();
    gameModel->getCharacters()[0].second->setMovePeriod(0);
    bool ok = true;
    for (unsigned int i=0; i<(5/GRAVITY)*2; i++)
    {
        gameModel->nextStep();
        if (i <= (5/GRAVITY))
        {
            if (gameModel->getCharacters()[0].second->getPosition().second > oldPosition.second)
            {
                ok = false;
            }
        } else {
            if (gameModel->getCharacters()[0].second->getPosition().second < oldPosition.second)
            {
                ok = false;
            }
        }
        oldPosition = gameModel->getCharacters()[0].second->getPosition();
    }

    BOOST_CHECK(ok);
    delete gameModel;
}

//On créé le character en l'ai et il doit retomber
BOOST_AUTO_TEST_CASE(test_Gravite)
{
    Game *gameModel= new Game{GAME_SIZE_W, GAME_SIZE_H, STARTSPEEDPERIODGAME};
    gameModel->getCharacters()[0].second->setPosition(200,200);
    gameModel->nextStep();

    BOOST_CHECK(gameModel->getCharacters()[0].second->getPosition().second > 200);

    delete gameModel;
}*/
