QT += core gui multimedia widgets

CONFIG += c++17

TARGET = Soundgenerator
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    soundgenerator.cpp

HEADERS += \
    mainwindow.h \
    soundgenerator.h

FORMS += \
    mainwindow.ui
