#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
//    delete axw;
    delete ui;
}

void MainWindow::fun2ActiveX()
{
    qDebug()<<(ui->axWidget->property("Name").toString());
    ui->axWidget->setProperty("Name","DisplyView");
    qDebug()<<(ui->axWidget->property("Name").toString());
    //GridppReport对象
    QAxObject object(QString::fromUtf8(GridppReport), ui->axWidget);
    object.dynamicCall("LoadFromFile(string)","1.grf");
//    object.dynamicCall("PrintPreview(Boolean)", true);

    qDebug()<<(object.objectName());
    qDebug()<<(object.property("Report"));

//    ui->axWidget->setProperty("Report",object);
    ui->axWidget->dynamicCall("Start()");

}


void MainWindow::on_pushButton_clicked()
{
    fun2ActiveX();
}


void FeiQi(){
    //    axw=new QAxWidget((QWidget *)(ui->gridLayout_Main));
    ////    axw->setControl(QString::fromUtf8("{F5EFB38E-EBEF-46E9-A9B5-051076391D75}"));
    //    axw->setControl(QString::fromUtf8("{8E27C92B-1264-101C-8A2F-040224009C02}"));
    ////    axw->resize(200,200);
    //    axw->show();


    //    ui->gridLayout_Main->addWidget(axw);
    //    Q_CHECK_PTR(axw);
    //    ui->gridLayout->addWidget(axw);

    //    QAxObject object(QString::fromUtf8("{13c28ad0-f195-4319-b7d7-a1bdaa329fb8}"), this);
    //    object.dynamicCall("LoadFromFile(string)","1.grf");
    //    object.dynamicCall("PrintPreview(Boolean)", true);

    //    axw=new QAxWidget();
    //    axw->setControl(QString::fromUtf8("{2564dce8-fedb-4eb6-b7f9-5026f7f1041e}"));

    //    axw->dynamicCall("LoadFromFile(string)","1.grf");
    //    axw->dynamicCall("PrintPreview(Boolean)", true);
    //    axw->show();
    //    ui->axWidget->dynamicCall("Report", object);

    //    ui->axWidget->property("Name").toString();
    //    qDebug()<<str;
}
