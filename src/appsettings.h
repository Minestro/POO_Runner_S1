#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <fstream>
#include <iostream>
#include "const.h"

struct AppSettings
{
    bool m_isFullScreen;
    unsigned int m_musicVolume;
    unsigned int m_effectVolume;
    unsigned int m_lang;
    AppSettings();
    ~AppSettings();

    void loadSettings();
    void saveSettings() const;
};

#endif // APPSETTINGS_H
