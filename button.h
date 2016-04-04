#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include <vector>
#include <string>

class Button: public Element
{
private:
    std::string m_text;
    unsigned int m_actionOnClick;   //Code de l'action à réaliser après etre cliqué.
    bool m_isClickable; //On peut immaginer que le bouton soit non cliquable par exemple qu'il soir grisé.
public:
    virtual ~Button();
    bool isHover(std::pair <float, float>) const;   //Prend la position de la souris et retourne vraie si la souris se trouve sur le bouton
    void onClick();
    std::string getClassName() const;
};

#endif // BUTTON_H
