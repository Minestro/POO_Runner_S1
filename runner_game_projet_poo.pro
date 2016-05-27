#Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License along
#with this program; if not, write to the Free Software Foundation, Inc.,
#51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32 {
    LIBS += -LC:/SFML/lib
    INCLUDEPATH += C:/SFML/include
    LIBS += -lsfml-main
}

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

QMAKE_LFLAGS += -static-libgcc
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    src/app.h \
    src/appsettings.h \
    src/bonus.h \
    src/button.h \
    src/buttongraphic.h \
    src/circleshapeelement.h \
    src/const.h \
    src/convexshapeelement.h \
    src/element.h \
    src/elementslist.h \
    src/game.h \
    src/gamecharacter.h \
    src/gamecharactergraphic.h \
    src/gameview.h \
    src/graphicelement.h \
    src/image.h \
    src/lifebar.h \
    src/menu.h \
    src/menuview.h \
    src/model.h \
    src/movableelement.h \
    src/obstacle.h \
    src/player.h \
    src/rectangleshapeelement.h \
    src/scoregraphic.h \
    src/spriteelement.h \
    src/text.h \
    src/textgraphic.h \
    src/view.hpp \
    src/window.h \
    src/TinyXml2/tinyxml2.h \
    src/sound.h \

SOURCES += \
    src/app.cpp \
    src/appsettings.cpp \
    src/bonus.cpp \
    src/button.cpp \
    src/buttongraphic.cpp \
    src/circleshapeelement.cpp \
    src/element.cpp \
    src/elementslist.cpp \
    src/game.cpp \
    src/gamecharacter.cpp \
    src/gamecharactergraphic.cpp \
    src/gameview.cpp \
    src/graphicelement.cpp \
    src/image.cpp \
    src/lifebar.cpp \
    src/main.cpp \
    src/menu.cpp \
    src/menuview.cpp \
    src/model.cpp \
    src/movableelement.cpp \
    src/obstacle.cpp \
    src/player.cpp \
    src/rectangleshapeelement.cpp \
    src/scoregraphic.cpp \
    src/spriteelement.cpp \
    src/text.cpp \
    src/textgraphic.cpp \
    src/tu.cpp \
    src/window.cpp \
    src/TinyXml2/tinyxml2.cpp \
    src/sound.cpp \

