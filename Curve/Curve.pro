#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T13:51:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Curve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    curve.cpp \
    curvemodel.cpp \
    curvemodelitem.cpp

HEADERS  += mainwindow.h \
    curve.h \
    curvemodel.h \
    curvemodelitem.h

FORMS    += mainwindow.ui
