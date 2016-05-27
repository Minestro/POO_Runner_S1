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

#ifndef MODEL_H
#define MODEL_H

#include "obstacle.h"
#include "bonus.h"
#include "image.h"
#include "gamecharacter.h"
#include "const.h"
#include "button.h"
#include "text.h"

class App;

class Model
{
protected:
    std::pair<float, float> m_size;
    std::vector<std::pair<bool, GameCharacter*> > m_characters;
    std::vector<std::pair<bool, Image*> > m_images;
    std::vector<std::pair<bool, Obstacle*> >m_obstacles;
    std::vector<std::pair<bool, Bonus*> > m_bonus;
    std::vector<std::pair<bool, Button*> > m_buttons;
    std::vector<std::pair<bool, runner::Text*> >m_texts;
    std::vector<const Element*> m_deletedElements;
    std::pair<int, int> m_cursorPosition;
    App *m_app;
public:
    Model(float width, float height, App *app = nullptr);
    virtual ~Model();
    std::vector<const Element*> &getDeletedElements();
    std::vector<std::pair<bool, GameCharacter*> > &getCharacters();
    std::vector<std::pair<bool, Image*> > &getImages();
    std::vector<std::pair<bool, Obstacle*> > &getObstacles();
    std::vector<std::pair<bool, Bonus*> > &getBonus();
    std::vector<std::pair<bool, Button*> > &getButtons();
    std::vector<std::pair<bool, runner::Text*> > &getTexts();
    const std::vector<std::pair<bool, Button*> > &getButtons() const;

    std::pair<float, float> getSize() const;
    std::pair<int, int> getCursorPosition() const;
    virtual std::string getClassName() const = 0;

    App *getApp();
    void setCursorPosition(int x, int y);
    void setApp(App *app);
    Element *searchElementById(unsigned int id);
    void deleteElement(unsigned int id);
    void clearAll();
};

#endif // MODEL_H
