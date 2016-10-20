TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vector3.cpp \
    planet.cpp \
    solarsystem.cpp \
    euler.cpp \
    verlet.cpp

HEADERS += \
    vector3.h \
    planet.h \
    solarsystem.h \
    euler.h \
    verlet.h
