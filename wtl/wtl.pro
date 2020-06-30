#-------------------------------------------------
#
# Project created by QtCreator 2020-06-27T09:44:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wtl
TEMPLATE = app
UI_DIR=./UI

CONFIG += resources_big

SOURCES += main.cpp\
    commandwidget.cpp \
    figurewidget.cpp \
    logindialog.cpp \
    mapwidget.cpp \
    mypushbutton.cpp \
        widget.cpp \
    timetable.cpp \
    schedule.cpp \
    travelerplan.cpp

HEADERS  += widget.h \
    commandwidget.h \
    figurewidget.h \
    logindialog.h \
    mapwidget.h \
    mypushbutton.h \
    timetable.h \
    log.h \
    schedule.h \
    travelerplan.h

FORMS    += widget.ui \
    commandwidget.ui \
    figurewidget.ui \
    logindialog.ui

CONFIG += c++11

RESOURCES += \
    res.qrc
