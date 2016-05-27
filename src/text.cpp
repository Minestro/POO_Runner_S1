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

#include "text.h"

using namespace runner;

std::unordered_map<std::string, std::string> Text::m_langFileToName;
std::vector<std::map<std::string, std::string> > Text::m_messages;

Text::Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, bool autoRescale, bool lineBreak): Element{x, y, width, height, rotation}, m_lineBreak{lineBreak}, m_autoRescale{autoRescale}, m_text{text}, m_fontSize{fontSize}, m_color{ColorRGBA::White}, m_font{font}, m_effect{text_effect::NOTHING}, m_effectPeriod{0}
{

}

Text::Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, ColorRGBA color, int effect, unsigned int effectPeriod, bool autoRescale, bool lineBreak): Element{x, y, width, height, rotation}, m_lineBreak{lineBreak}, m_autoRescale{autoRescale}, m_text{text}, m_fontSize{fontSize}, m_color{color}, m_font{font}, m_effect{effect}, m_effectPeriod{effectPeriod}
{

}

void Text::setText(std::string text)
{
    m_text = text;
}

std::string &Text::getText()
{
    return m_text;
}

std::string Text::getClassName() const
{
    return "Text";
}

unsigned int Text::getFontSize() const
{
    return m_fontSize;
}

ColorRGBA Text::getColor() const
{
    return m_color;
}

std::string Text::getFont() const
{
    return m_font;
}

int Text::getEffect() const
{
    return m_effect;
}

bool Text::getAutoRescale() const
{
    return m_autoRescale;
}

bool Text::getlineBreak() const
{
    return m_lineBreak;
}

unsigned int Text::getEffectPeriod() const
{
    return m_effectPeriod;
}

void Text::loadLanguages()
{
    DIR * rep = opendir("./Ressources/langs/");

    if (rep != nullptr)
    {
        struct dirent * ent;
        std::string fileName;
        while ((ent = readdir(rep)) != nullptr)
        {
            fileName = ent->d_name;
            if (fileName.find(".lang") != std::string::npos)
            {
                std::ifstream fileStream{std::string("Ressources/langs/" + fileName).c_str(), std::ios::in};
                if (!fileStream)
                {
                    std::cout << "Error when trying to open " << fileName << std::endl;
                } else {
                    std::string content;
                    std::map<std::string, std::string> messagesMap;
                    std::getline(fileStream, content);
                    m_langFileToName.insert(std::make_pair(content.substr(content.find('=')+1), fileName));
                    while (std::getline(fileStream, content))
                    {
                        if (KEY_MESSAGES.find(content.substr(0, content.find('='))) != KEY_MESSAGES.end())
                        {
                            messagesMap.insert(std::make_pair(content.substr(0, content.find('=')), content.substr(content.find('=')+1)));
                        }
                    }
                    m_messages.push_back(messagesMap);
                    fileStream.close();
                }
            }
        }
        std::vector<std::map<std::string, std::string> > messages = m_messages;
        closedir(rep);
    }
}

std::string Text::getMessage(unsigned int langId, const std::string &messageKey)
{
    if (langId > m_langFileToName.size()-1)
    {
        langId = 0;
    }
    if (m_messages[langId].find(messageKey) == m_messages[langId].end())
    {
        return "";
    } else {
        return m_messages[langId][messageKey];
    }
}

std::vector<std::string> Text::getLangsList()
{
    std::vector<std::string> langList;
    for (const std::pair<std::string, std::string> &lang : m_langFileToName)
    {
        langList.push_back(lang.first);
    }
    std::reverse(langList.begin(), langList.end());
    return langList;
}
