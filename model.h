#ifndef MODEL_H
#define MODEL_H

#include "obstacle.h"
#include "bonus.h"
#include "background.h"
#include "gamecharacter.h"
#include "const.h"
#include "button.h"
#include "text.h"

class Model
{
protected:
    std::pair<float, float> m_size;
    std::vector<std::pair<bool, GameCharacter*> > m_characters;
    std::vector<std::pair<bool, Background*> > m_backgrounds;
    std::vector<std::pair<bool, Obstacle*> >m_obstacles;
    std::vector<std::pair<bool, Bonus*> > m_bonus;
    std::vector<std::pair<bool, Button*> > m_buttons;
    std::vector<std::pair<bool, Text*> >m_texts;
    std::vector<const Element*> m_deletedElements;
    std::pair<int, int> m_cursorPosition;
public:
    Model() = default;
    Model(float width, float height);
    virtual ~Model() = default;
    std::vector<const Element*> &getDeletedElements();
    std::vector<std::pair<bool, GameCharacter*> > &getCharacters();
    std::vector<std::pair<bool, Background*> > &getBackgrounds();
    std::vector<std::pair<bool, Obstacle*> > &getObstacles();
    std::vector<std::pair<bool, Bonus*> > &getBonus();
    std::vector<std::pair<bool, Button*> > &getButtons();
    std::vector<std::pair<bool, Text*> > &getTexts();
    std::pair<float, float> getSize() const;
    std::pair<int, int> getCursorPosition() const;
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const = 0;
    void setCursorPosition(int x, int y);
};

#endif // MODEL_H
