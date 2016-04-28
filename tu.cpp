#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RunnerTest

#include <boost/test/unit_test.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include "game.h"
#include "model.h"
#include "menu.h"
#include "graphicelement.h"

// les tests groupes par "cas"

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

BOOST_AUTO_TEST_CASE(test_button)
{
    Menu *menu = new Menu{GAME_SIZE_W, GAME_SIZE_H, 1};
    Button *button = new Button{50, 50, 200, 50, "test", 0, menu};
    BOOST_CHECK(button->isHover(60, 60) == true);
    BOOST_CHECK(button->isHover(23, 60) == false);
    BOOST_CHECK(button->isHover(60, 13) == false);
    BOOST_CHECK(button->isHover(17, 42) == false);
    BOOST_CHECK(button->isHover(630, 64) == false);
}

BOOST_AUTO_TEST_CASE(test_hslColor)
{
    BOOST_CHECK(GraphicElement::color2hsl(255, 0, 0).h == 0);
    BOOST_CHECK(GraphicElement::color2hsl(255, 0, 0).l == 0.5);
    BOOST_CHECK(GraphicElement::color2hsl(255, 0, 0).s == 1.0);

    BOOST_CHECK((int)GraphicElement::color2hsl(212, 216, 43).h == 61);
    BOOST_CHECK(GraphicElement::color2hsl(212, 216, 43).l >= 0.507 && GraphicElement::color2hsl(212, 216, 43).l <= 0.509);
    BOOST_CHECK(GraphicElement::color2hsl(212, 216, 43).s >= 0.688 && GraphicElement::color2hsl(212, 216, 43).s <= 0.690);
/*
    std::cout << GraphicElement::color2hsl(98, 45, 234).l;
    BOOST_CHECK((int)GraphicElement::color2hsl(98, 45, 234).h == 257);
    BOOST_CHECK(GraphicElement::color2hsl(98, 45, 234).l >= 0.546 && GraphicElement::color2hsl(98, 45, 234).l <= 0.548);
    BOOST_CHECK(GraphicElement::color2hsl(98, 45, 234).s >= 0.817 && GraphicElement::color2hsl(98, 45, 234).s <= 0.819);*/
}
