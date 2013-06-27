TEMPLATE = app
TARGET = GoGo
INCLUDEPATH += . src obj

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS += src/gobanView.h \
           src/helper.h \
           src/goban.h \
           src/stoneItem.h \
           src/sidebar.h \
           src/controllerGTP.h \
           src/go.h 
           
FORMS += 
SOURCES += src/gobanView.cpp \
           src/main.cpp \
           src/helper.cpp \
           src/goban.cpp \
           src/stoneItem.cpp \
           src/sidebar.cpp \
           src/controllerGTP.cpp \
           src/go.cpp

CONFIG += debug

DESTDIR = bin
UI_DIR = obj
MOC_DIR = obj
OBJECTS_DIR = obj

