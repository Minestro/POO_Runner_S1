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

#include "appsettings.h"

AppSettings::AppSettings(): m_isFullScreen{0}, m_musicVolume{100}, m_effectVolume{100}, m_lang{0}
{
    loadSettings();
}

AppSettings::~AppSettings()
{
    saveSettings();
}

void AppSettings::loadSettings()
{
    std::ifstream fileStream{SETTINGS_FILE.c_str(), std::ios::in};
    if (!fileStream)
    {
        std::cout << "Error when loading settings file" << std::endl;
        saveSettings();
    } else {
        std::string content;
        while (std::getline(fileStream, content))
        {
            std::string prefixe = content.substr(0, content.find('='));
            if (prefixe == "FULLSCREEN")
            {
                m_isFullScreen = std::stoi(content.substr(content.find('=')+1)) == 1;
            } else if (prefixe == "MUSICVOLUME")
            {
                m_musicVolume = std::stoi(content.substr(content.find('=')+1));
            } else if (prefixe == "SOUNDVOLUME")
            {
                m_effectVolume = std::stoi(content.substr(content.find('=')+1));
            } else if (prefixe == "LANG")
            {
                m_lang = std::stoi(content.substr(content.find('=')+1));
            }
        }
        fileStream.close();
    }
}

void AppSettings::saveSettings() const
{
    std::ofstream fileStream{SETTINGS_FILE.c_str(), std::ios::out | std::ios::trunc};
    if (!fileStream)
    {
        std::cout << "Error when writing settings file" << std::endl;
    } else {
        fileStream << "FULLSCREEN=" << m_isFullScreen << std::endl << "MUSICVOLUME=" << m_musicVolume << std::endl << "SOUNDVOLUME=" << m_effectVolume << std::endl << "LANG=" << m_lang << std::endl;
        fileStream.close();
    }
}
