TEMPLATE = app
TARGET = GoGo
INCLUDEPATH += . src obj

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS += obj/ui_mainwindow.h \
           src/gobanView.h \
           src/mainwindow.h \
           src/helper.h \
           src/controller.h \
           src/stoneItem.h 
           
FORMS += src/mainwindow.ui
SOURCES += src/gobanView.cpp \
           src/main.cpp \
           src/mainwindow.cpp \
           src/helper.cpp \
           src/controller.cpp \
           src/stoneItem.cpp

CONFIG += debug

DESTDIR = bin
UI_DIR = obj
MOC_DIR = obj
OBJECTS_DIR = obj

