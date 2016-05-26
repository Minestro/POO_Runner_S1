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

        static std::unordered_map<std::string, std::string> m_langFileToName;
        static std::vector<std::map<std::string, std::string> > m_messages;

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
        static std::vector<std::string> getLangsList();
    };
}


#endif // TEXT_H
