#ifndef BUTTON_H
#define BUTTON_H

#include <vector>
#include <string>

class Button
{
private:
    std::pair <float, float> m_size;    //first : w, second : h
    std::pair <float, float> m_position;    //first : x, second : y
    std::string m_text;
    unsigned int m_actionOnClick;   //Code de l'action à réaliser après etre cliqué.
    bool m_isClickable; //On peut immaginer que le bouton soit non cliquable par exemple qu'il soir grisé.
public:
    bool isHover(std::pair <float, float>) const;   //Prend la position de la souris et retourne vraie si la souris se trouve sur le bouton
};

#endif // BUTTON_H
