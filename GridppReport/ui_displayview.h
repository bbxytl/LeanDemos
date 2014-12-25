#ifndef UI_DISPLAYVIEW_H
#define UI_DISPLAYVIEW_H

#include <QMainWindow>
#include "ahead.h"

namespace Ui {
class UI_DisPlayView;
}

class UI_DisPlayView : public QMainWindow
{
    Q_OBJECT

public:
    explicit UI_DisPlayView(QWidget *parent = 0);
    ~UI_DisPlayView();

private slots:
    void on_act_PreView_triggered();

    void on_act_Disigner_triggered();

    void on_act_FunTest_triggered();

private:
    Ui::UI_DisPlayView *ui;
};

#endif // UI_DISPLAYVIEW_H
