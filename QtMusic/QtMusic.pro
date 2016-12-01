#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T14:14:56
#
#-------------------------------------------------

QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMusic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    movablewidget.cpp \
    closablewidget.cpp \
    titlewidget.cpp \
    bottomwidget.cpp \
    customizebutton.cpp \
    centorwdiget.cpp \
    musciplayer.cpp \
    mouseslider.cpp \
    circlewidget.cpp \
    imagetool.cpp \
    fileoperate.cpp

HEADERS  += mainwindow.h \
    movablewidget.h \
    closablewidget.h \
    titlewidget.h \
    bottomwidget.h \
    customizebutton.h \
    centorwdiget.h \
    musciplayer.h \
    mouseslider.h \
    circlewidget.h \
    imagetool.h \
    fileoperate.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    source.qrc
