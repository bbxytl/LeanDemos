#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T15:09:10
#
#-------------------------------------------------

QT       += core gui axcontainer
CONFIG += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GridppReport
TEMPLATE = app


SOURCES += main.cpp\
    ui_displayview.cpp \
    Grid++ReportLib/gredes.cpp \
    Grid++ReportLib/gregn.cpp

HEADERS  += \
    ahead.h \
    ui_displayview.h \
    Grid++ReportLib/gredes.h \
    Grid++ReportLib/gregn.h

FORMS    += \
    ui_displayview.ui
