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

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "graphicelement.h"
#include "const.h"
#include "appsettings.h"

class Window: public sf::RenderWindow
{
private:
    sf::Event m_event;
    std::string m_title;
    bool m_isFullScreen;
public:
    Window(std::string title, int style, float modelSizeW, float modelSizeH);
    ~Window();
    sf::Event *getEvent();
    void saveConfig() const;
    void refreshSettings(AppSettings &settings);
};

#endif // WINDOW_H
