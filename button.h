#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include <vector>
#include <string>

enum button_type {TEXT_BUTTON, ARROW_BUTTON, RADIO_BUTTON, SAVE_BUTTON};
enum button_action {CHANGE_PAGE, EXIT_APP, SET_FULL_SCREEN, RESUME_GAME, RESET_GAME, SET_SELECTED, ERASE_SAVE, LOAD_SAVE};
enum button_id {FULL_SCREEN_BUTTON = 200, LOAD_SAVE_BUTTON, SELECT_SAVE_1, SELECT_SAVE_2, SELECT_SAVE_3, SELECT_SAVE_4, SELECT_SAVE_5};

class App;

class Button: public Element
{
private:
    std::string m_text;
    int m_type;
    bool m_isClickable; //On peut immaginer que le bouton soit non cliquable par exemple qu'il soit grisé.
    bool m_isOn;
    bool m_isSelected;
    int m_destinationPage;
    App *m_app;
    std::vector<int> m_actions;
public:
    Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, App *p, int type = button_type::TEXT_BUTTON, bool isClickable = 1);
    virtual ~Button() = default;
    bool isHover(int x, int y) const;
    void onClick();
    std::string getText() const;
    int getType() const;
    int getDestinationPage() const;
    bool isClickable() const;
    bool isOn() const;
    bool isSelected() const;
    void setSelected(bool selected);
    void setIsOn(bool on);
    void setText(std::string text);
    std::string getClassName() const;
    void addAction(int action);

    static void changePage(const Button *sender, App &app);
};

#endif // BUTTON_H
