QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    database.cpp \
    gameboard.cpp \
    gamelogic.cpp \
    main.cpp \
    mainwindow.cpp \
    squarebutton.cpp

HEADERS += \
    database.h \
    gameboard.h \
    gamelogic.h \
    mainwindow.h \
    squarebutton.h

FORMS += \
    mainwindow.ui

DISTFILES +=

RESOURCES += \
    assets/darkstyle.qrc

