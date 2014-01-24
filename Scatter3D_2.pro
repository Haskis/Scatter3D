#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T11:47:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scatter3D_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scatterwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    scatterwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
