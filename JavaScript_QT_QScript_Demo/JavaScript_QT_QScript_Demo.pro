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
    jsdatabase.cpp \
    jsdataset.cpp \
    customdataset.cpp

HEADERS  += mainwindow.h \
    ahead.h \
    jsdatabase.h \
    jsdataset.h \
    customdataset.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../Build/JavaScript_QT_QScript_Demo-Debug/JSCode.js \
    ../Build/JavaScript_QT_QScript_Demo-Debug/JS_DBCon.js


#添加库文件路��?
LIBS += D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/lib/libNCReportDebug2.a

#添加包含路径
INCLUDEPATH += D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/include
INCLUDEPATH += C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QtCore/5.3.1
#添加搜索路径
DEPENDPATH += D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/include
DEPENDPATH += C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QtCore/5.3.1
