#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T09:41:32
#
#-------------------------------------------------

QT       += core gui script axcontainer sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JavaScript_QT_QScript_Demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jsdataset.cpp \
    customdataset.cpp \
    jsdbobject.cpp \
    old/jsdatabase.cpp \
    STL/stldataset.cpp

HEADERS  += mainwindow.h \
    ahead.h \
    jsdataset.h \
    customdataset.h \
    jsdbobject.h \
    old/jsdatabase.h \
    STL/stldataset.h

FORMS    += mainwindow.ui


#娣诲姞搴撴枃浠惰矾锟斤拷?
LIBS += D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/lib/libNCReportDebug2.a

#娣诲姞鍖呭惈璺緞
INCLUDEPATH += D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/include
INCLUDEPATH += C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QtCore/5.3.1
#娣诲姞鎼滅储璺緞
DEPENDPATH += D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/include
DEPENDPATH += C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QtCore/5.3.1

OTHER_FILES += \
    ../Build/JavaScript_QT_QScript_Demo-Debug/07分部分项工程和单价措施项目清单与计价表_GCLQD.js \
    ../Build/JavaScript_QT_QScript_Demo-Debug/工程量清单项目预算表.js \
    ../Build/JavaScript_QT_QScript_Demo-Debug/工程量清单项目预算表_GCLQD.js
