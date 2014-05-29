#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T12:23:35
#
#-------------------------------------------------

QT += core gui

TARGET = time-series
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS += mainwindow.h \
    tsPrediction.h \
    seriesReader.h \
    fileReader.h \
    consoleReader.h

FORMS += mainwindow.ui

RESOURCES += \
    images.qrc

CONFIG += c++11
