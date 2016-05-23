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
    src/effect.h

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
    src/effect.cpp

