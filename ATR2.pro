#-------------------------------------------------
#
# Project created by QtCreator 2018-03-22T15:23:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATR2
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
    filelib.cpp \
    main.cpp \
    arena.cpp \
    atr2.cpp \
    atr2func.cpp \
    atr2var.cpp \
    window.cpp \
    rgraph.cpp \
    cgraph.cpp \
    thread.cpp

HEADERS += \
    filelib.h \
    arena.h \
    atr2.h \
    atr2func.h \
    atr2var.h \
    window.h \
    rgraph.h \
    cgraph.h \
    thread.h

FORMS +=

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

RC_FILE = Extra\atr2.rc
ICON = Extra\atr2.icns

RESOURCES += \
    atr2.qrc
