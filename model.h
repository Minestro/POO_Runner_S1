#ifndef MODEL_H
#define MODEL_H

#include "obstacle.h"
#include "bonus.h"
#include "background.h"
#include "gamecharacter.h"
#include "const.h"

class Model
{
protected:
    std::pair<float, float> m_size;
    std::vector<GameCharacter*> m_characters;
    std::vector<Background*> m_backgrounds;
    std::vector<Obstacle*> m_obstacles;
    std::vector<Bonus*> m_bonus;
    std::vector<const Element*> m_newElements;
    std::vector<const Element*> m_deletedElements;
    std::pair<int, int> m_cursorPosition;
public:
    Model() = default;
    Model(float width, float height);
    std::vector<const Element*> &getDeletedElements();
    std::vector<const Element*> &getNewElements();
    std::vector<GameCharacter*> &getCharacters();
    std::vector<Background*> &getBackgrounds();
    std::vector<Obstacle*> &getObstacles();
    std::vector<Bonus*> &getBonus();
    std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const = 0;
    void setCursorPosition(int x, int y);
};

#endif // MODEL_H
