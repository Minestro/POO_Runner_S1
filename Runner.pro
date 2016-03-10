TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp \
    gameview.cpp \
    player.cpp \
    menu.cpp \
    menuview.cpp \
    movableelement.cpp \
    button.cpp \
    obstacle.cpp \
    bonus.cpp \
    menupage.cpp \
    slidingbackground.cpp \
    graphicelement.cpp \
    gamecharacter.cpp \
    window.cpp

HEADERS += \
    game.h \
    gameview.h \
    player.h \
    menu.h \
    menuview.h \
    movableelement.h \
    button.h \
    obstacle.h \
    bonus.h \
    menupage.h \
    slidingbackground.h \
    graphicelement.h \
    gamecharacter.h \
    window.h

LIBS           += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
