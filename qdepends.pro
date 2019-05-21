#-------------------------------------------------
#
# Project created by QtCreator 2019-05-20T15:39:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qdepends
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
include("D:/Qt/Config.pri")
CONFIG += c++11

SOURCES += \
        main.cpp \
    PeModel.cpp \
    MainWindow.cpp

HEADERS += \
    PeModel.h \
    MainWindow.h

# Default rules for deployment.
INCLUDEPATH += D:/3rd/LIEF/include
DEPENDPATH += D:/3rd/LIEF/include
LIBS += -LD:/3rd/LIEF/lib -lLIEF

QMAKE_LFLAGS += /DEBUG /OPT:REF
QMAKE_CXXFLAGS += /Zi
