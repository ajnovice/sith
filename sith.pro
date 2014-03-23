#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T02:37:13
#
#-------------------------------------------------

QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets

TARGET = sith
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    creategraphscene.cpp \
    graphcoloring.cpp \
    decryption.cpp \
    fakemessages.cpp \
    gcolor.cpp \
    basicdictionary.cpp \
    node.cpp \
    edge.cpp \
    edgemap.cpp

HEADERS  += mainwindow.h \
    creategraphscene.h \
    graphcoloring.h \
    decryption.h \
    fakemessages.h \
    gcolor.h \
    basicdictionary.h \
    node.h \
    edge.h \
    edgemap.h

FORMS    += mainwindow.ui
