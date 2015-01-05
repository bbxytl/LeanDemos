#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T09:41:32
#
#-------------------------------------------------

QT       += core gui script axcontainer sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JavaScript_QT_QScript_Demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jsdatabase.cpp \
    jsdataset.cpp

HEADERS  += mainwindow.h \
    ahead.h \
    jsdatabase.h \
    jsdataset.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../Build/JavaScript_QT_QScript_Demo-Debug/JSCode.js \
    ../Build/JavaScript_QT_QScript_Demo-Debug/JS_DBCon.js
