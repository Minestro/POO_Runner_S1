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
