#include "mainwindow.h"
#include <QApplication>

#include "formtest.h"

#include "ui_displayview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    FormTest f;
//    f.show();

    UI_DisPlayView Udpv;
    Udpv.show();

    return a.exec();
}
