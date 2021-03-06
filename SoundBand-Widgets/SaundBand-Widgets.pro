#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T20:43:57
#
#-------------------------------------------------

QT       += core gui network multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundBand-Widgets
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../sync/ETcpSocket.cpp \
    ../sync/LocalScanner.cpp \
    ../sync/node.cpp \
    ../sync/song.cpp \
    ../sync/sync.cpp \
    servermodel.cpp \
    songmodel.cpp \
    ../sync/player.cpp \
    ../sync/chronotime.cpp \
    ../sync/mysql.cpp \
    ../sync/Log.cpp \
    ../sync/exaptions.cpp

HEADERS += \
        mainwindow.h \
    ../sync/config.h \
    ../sync/ETcpSocket.h \
    ../sync/exaptions.h \
    ../sync/LocalScanner.h \
    ../sync/node.h \
    ../sync/song.h \
    ../sync/sync.h \
    servermodel.h \
    songmodel.h \
    ../sync/player.h \
    ../sync/chronotime.h \
    ../sync/mysql.h \
    ../sync/Log.h

FORMS += \
        mainwindow.ui

