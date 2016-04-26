#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include <vector>
#include <string>

enum button_type {TEXT_BUTTON, ARROW_BUTTON};

class Menu;

class Button: public Element
{
private:
    std::string m_text;
    button_type m_type;
    bool m_isClickable; //On peut immaginer que le bouton soit non cliquable par exemple qu'il soir grisé.
    int m_destinationPage;
    Menu *m_menu;
public:
    Button() = default;
    Button(float x, float y, float width, float height, std::string text, int destinationPage, Menu *m, button_type type = button_type::TEXT_BUTTON, bool isClickable = 1);
    virtual ~Button() = default;
    bool isHover(int x, int y) const;
    void onClick();
    std::string getText() const;
    button_type getType() const;
    bool isClickable() const;
    std::string getClassName() const;
};

#endif // BUTTON_H
