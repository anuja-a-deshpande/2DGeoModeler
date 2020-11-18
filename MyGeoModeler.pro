#-------------------------------------------------
#
# Project created by QtCreator 2016-02-22T20:08:06
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyGeoModeler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Polygon.cpp \
    Point.cpp \
    Line.cpp \
    glwidget.cpp \
    CModeler.cpp \
    Circle.cpp

HEADERS  += mainwindow.h \
    Two_d_shape.h \
    Shape.h \
    Polygon.h \
    Point.h \
    Line.h \
    glwidget.h \
    CModeler.h \
    Circle.h

FORMS    += mainwindow.ui

CONFIG += c++11

LIBS += -lm
        -lGL
        -lglut
