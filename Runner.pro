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
    renderwindow.cpp \
    obstacle.cpp \
    bonus.cpp \
    menupage.cpp

HEADERS += \
    game.h \
    gameview.h \
    player.h \
    menu.h \
    menuview.h \
    movableelement.h \
    button.h \
    renderwindow.h \
    obstacle.h \
    bonus.h \
    menupage.h

LIBS           += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
