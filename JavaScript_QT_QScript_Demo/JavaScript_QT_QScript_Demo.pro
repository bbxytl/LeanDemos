#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T09:41:32
#
#-------------------------------------------------

NCREPORT_INCLUDEPATH = "D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/include"
NCREPORT_INCLUDEPATH += "C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QtCore/5.3.1"
NCREPORT_LIBS = "D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/lib/libNCReportDebug2.a"

QT       += core gui script sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JavaScript_QT_QScript_Demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jsdataset.cpp \
    customdataset.cpp \
    jsdbobject.cpp \

HEADERS  += mainwindow.h \
    ahead.h \
    jsdataset.h \
    customdataset.h \
    jsdbobject.h \

FORMS    += mainwindow.ui

LIBS += $$NCREPORT_LIBS

INCLUDEPATH += $$NCREPORT_INCLUDEPATH
DEPENDPATH += $$NCREPORT_INCLUDEPATH

OTHER_FILES += \
    ../Build/JavaScript_QT_QScript_Demo-Debug/07分部分项工程和单价措施项目清单与计价表_GCLQD.js \
    ../Build/JavaScript_QT_QScript_Demo-Debug/工程量清单项目预算表.js \
    ../Build/JavaScript_QT_QScript_Demo-Debug/工程量清单项目预算表_GCLQD.js
