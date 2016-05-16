#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include <vector>
#include <string>

enum button_type {TEXT_BUTTON, ARROW_BUTTON, RADIO_BUTTON};
enum button_action {CHANGE_PAGE, EXIT_APP, SET_FULL_SCREEN, RESUME_GAME};
enum button_id {FULL_SCREEN_BUTTON = 200};

class App;

class Button: public Element
{
private:
    std::string m_text;
    button_type m_type;
    bool m_isClickable; //On peut immaginer que le bouton soit non cliquable par exemple qu'il soit grisé.
    bool m_isOn;
    int m_destinationPage;
    App *m_app;
    std::vector<button_action> m_actions;
public:
    Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, App *p, button_type type = button_type::TEXT_BUTTON, bool isClickable = 1);
    virtual ~Button() = default;
    bool isHover(int x, int y) const;
    void onClick();
    std::string getText() const;
    button_type getType() const;
    int getDestinationPage() const;
    bool isClickable() const;
    bool isOn() const;
    void setIsOn(bool on);
    std::string getClassName() const;
    void addAction(button_action action);

    static void changePage(const Button *sender, App &app);
};

#endif // BUTTON_H
