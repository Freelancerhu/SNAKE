QT += core
QT -= gui

CONFIG += c++11

TARGET = SnakeUbuntu
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cursor.cpp \
    map.cpp \
    view.cpp \
    controlsnake.cpp \
    model.cpp

HEADERS += \
    cursor.h \
    coord.h \
    map.h \
    view.h \
    controlsnake.h \
    model.h
