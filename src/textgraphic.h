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

#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "graphicelement.h"
#include "const.h"

class TextGraphic: public GraphicElement, public sf::Text
{
private:
    void rescale(float width, float height);
    std::pair<float, float> m_realPosition;
    std::pair<float, float> m_realSize;
    bool m_autoRescale;                     //Si le texte est auto rescale il se mettra au centre du rectangle si il a de la place sinon il sera compressé.
    bool m_lineBreak;
    std::vector<std::string> m_textLines;       //Pour les textes avec un retour à la ligne uniquement. Contient le contenu ligne par ligne
    int m_effect;
    bool m_breath;
    sf::RenderTexture m_textForm;       //Pour les textes avec un retour à ligne uniquement. C'est un pré rendu sur lequel on effectura les transformations si il y en a.
    int m_alphaChannel;                 //Transparence du texte

    void generateTextForm();
public:
    TextGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, std::string text, const sf::Font *font, unsigned int fontSize, bool autoRescale = 1, bool lineBreak = 1, sf::Color color = sf::Color::Black, int style = 0, int effect = text_effect::NOTHING, unsigned int refreshPeriod = 0);
    virtual ~TextGraphic() = default;
    void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    void setText(std::string text);
    virtual std::pair<float, float> getSize() const;
    virtual std::string getClassName() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
    std::string getText() const;

    static std::map<std::string, sf::Font*> m_listFonts;
    static void loadFonts(std::string themeName="Default");
    static void clearFonts();
};

#endif // TEXTELEMENT_H
