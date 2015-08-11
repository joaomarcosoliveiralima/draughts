#-------------------------------------------------
#
# Project created by QtCreator 2011-09-09T01:04:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = xadrez
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/main.cpp \
    ../src/imageloader.cpp \
    ../src/cTexture.cpp \
    ../src/cPeca.cpp \
    ../src/cGame.cpp \
    ../src/cBoard.cpp \
    ../src/cAppararence.cpp

HEADERS += \
    ../src/imageloader.h \
    ../src/cTexture.h \
    ../src/cPeca.h \
    ../src/cGame.h \
    ../src/cCube.h \
    ../src/cCoord.h \
    ../src/cBoard.h \
    ../src/cApparance.h

LIBS += -lGLU -lglut
