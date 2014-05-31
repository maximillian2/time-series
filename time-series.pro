#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T12:23:35
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

TARGET = time-series
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    builder.cpp \
    markovmodel.cpp

HEADERS  += mainwindow.h \
    tsPrediction.h \
    seriesReader.h \
    fileReader.h \
    consoleReader.h \
    scene.h \
    builder.h \
    bayesian.h \
    markovmodel.h

FORMS    += mainwindow.ui \
    scene.ui

RESOURCES += \
    images.qrc

CONFIG += c++11

OTHER_FILES +=
