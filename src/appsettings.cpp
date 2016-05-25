#include "appsettings.h"

AppSettings::AppSettings(): m_isFullScreen{0}, m_musicVolume{100}, m_effectVolume{100}
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
