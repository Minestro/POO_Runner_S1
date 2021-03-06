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

#ifndef TEXT_H
#define TEXT_H

#include <dirent.h>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>

#include <algorithm>
#include "element.h"

namespace runner
{
    class Text: public Element
    {
    private:
        bool m_lineBreak;
        bool m_autoRescale;
        std::string m_text;
        unsigned int m_fontSize;
        ColorRGBA m_color;
        std::string m_font;
        int m_effect;
        unsigned int m_effectPeriod;

        static std::unordered_map<std::string, std::string> m_langFileToName;       //Associe le nom d'une langue au fichier
        static std::vector<std::map<std::string, std::string> > m_messages;         //Assorcie un keyword à un texte pour chaque langue

    public:
        Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, bool autoRescale = 1, bool lineBreak = 1);
        Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, ColorRGBA color = ColorRGBA::Black, int effect = text_effect::NOTHING, unsigned int effectPeriod = 0, bool autoRescale = 1, bool lineBreak = 1);
        virtual ~Text() = default;
        void setText(std::string text);
        std::string &getText();
        unsigned int getFontSize() const;
        ColorRGBA getColor() const;
        std::string getFont() const;
        int getEffect() const;
        unsigned int getEffectPeriod() const;
        bool getlineBreak() const;
        bool getAutoRescale() const;
        virtual std::string getClassName() const;

        static void loadLanguages();
        static std::string getMessage(unsigned int langId, const std::string &messageKey);
        static std::vector<std::string> getLangsList();     //Renvoi la liste des noms de langues disponibles
    };
}


#endif // TEXT_H
