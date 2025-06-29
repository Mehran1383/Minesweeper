QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    custommode.cpp \
    database.cpp \
    gameboard.cpp \
    gamelogic.cpp \
    highscores.cpp \
    main.cpp \
    mainwindow.cpp \
    squarebutton.cpp

HEADERS += \
    custommode.h \
    database.h \
    gameboard.h \
    gamelogic.h \
    highscores.h \
    mainwindow.h \
    squarebutton.h

FORMS += \
    custommode.ui \
    highscores.ui \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    assets/darkstyle.qrc

