#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ahead.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void fun2ActiveX();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
//    QAxWidget * axw;
};

#endif // MAINWINDOW_H
