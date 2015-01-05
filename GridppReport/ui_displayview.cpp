#include "ui_displayview.h"
#include "ui_ui_displayview.h"
#include <QUuid>
#include <QAxBase>

UI_DisPlayView::UI_DisPlayView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UI_DisPlayView)
{
    ui->setupUi(this);
    setWindowTitle("报表设计和预览");
    ui->stackedWidget->setCurrentIndex(2);
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


    QAxObject * report=ui->axWidget_designer->querySubObject("Report");
//    detailGrid = *(QAxObject **)qax_result.constData();
//    QAxObject * recordSet =detailGrid->querySubObject("Recordset");
//    recordSet->dynamicCall("AddField(const QString, grproLib::tagGRFieldType)","Fwad",0);
//    ui->axWidget_designer->dynamicCall("Reload()");
//    ui->axWidget_designer->dynamicCall("");
//    IUnknown *iface = 0;
//    ui->axWidget_designer->queryInterface(QUuid(QString::fromUtf8("{f5efb38e-ebef-46e9-a9b5-051076391d75}")),(void**)&iface);
//    if (iface) {
//    // use the interface
////    iface->DetailGrid();
//        int i=0;
//    }

    /*Y*/QAxObject gridppReport(QString::fromUtf8(DC_GridppReport));
    /*N*/QVariant detailGrid = gridppReport.dynamicCall("DetailGrid");

    /*OK*/QAxObject *day=ui->axWidget->querySubObject("Value");



    QAxWidget outlook("Outlook.Application");
    QAxObject *session = outlook.querySubObject("Session");
    if (session) {
        QAxObject *defFolder = session->querySubObject(
                                "GetDefaultFolder(OlDefaultFolders)",
                                "olFolderContacts");
    }

     int i=0;
     i++;
}
