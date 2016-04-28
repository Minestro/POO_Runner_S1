#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RunnerTest

#include <boost/test/unit_test.hpp>
#include "game.h"
#include "bonus.h"
#include"gamecharacter.h"







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
