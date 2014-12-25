#include "ui_displayview.h"
#include "ui_ui_displayview.h"

UI_DisPlayView::UI_DisPlayView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UI_DisPlayView)
{
    ui->setupUi(this);
    setWindowTitle("报表设计和预览");
}

UI_DisPlayView::~UI_DisPlayView()
{
    delete ui;
}

void UI_DisPlayView::on_act_PreView_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void UI_DisPlayView::on_act_Disigner_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void UI_DisPlayView::on_act_FunTest_triggered()
{
    QString str=ui->axWidget_designer->dynamicCall("GetObjectName(int Index)",0).toString();
    DBG<<str;
}
