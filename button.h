#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include <vector>
#include <string>

enum button_type {TEXT_BUTTON, ARROW_BUTTON};
enum button_action {CHANGE_PAGE};

class Menu;

class Button: public Element
{
private:
    std::string m_text;
    button_type m_type;
    bool m_isClickable; //On peut immaginer que le bouton soit non cliquable par exemple qu'il soir grisé.
    int m_destinationPage;
    Menu *m_menu;
    std::vector<button_action> m_actions;
public:
    Button() = default;
    Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, Menu *m, button_type type = button_type::TEXT_BUTTON, bool isClickable = 1);
    virtual ~Button() = default;
    bool isHover(int x, int y) const;
    void onClick();
    std::string getText() const;
    button_type getType() const;
    int getDestinationPage() const;
    bool isClickable() const;
    std::string getClassName() const;
    void addAction(button_action action);

    static void changePage(Button *sender, Menu *menu);
    static void test(Button *sender, Menu *menu);
};

#endif // BUTTON_H
