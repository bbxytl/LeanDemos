#include "formtest.h"

FormTest::FormTest(QWidget *parent) :
    QMainWindow(parent)
{
    axw=new QAxWidget(this);
//    axw->setControl(DC_GridppReport );
//    axw->dynamicCall("LoadFromFile(string)","1.grf");
//    this->setCentralWidget(axw);
//    axw->dynamicCall("PrintPreview(Boolean)", true);

//    axw->show();
    Test();
}
FormTest::~FormTest(){
    delete axw;
}

void FormTest::Test()
{
//    IGridppReport *gp = new IGridppReport();
//    gp->LoadFromFile("1.grf");

//    IGRDisplayViewer *gv =new IGRDisplayViewer();
//    gv->SetReport(gp);
//    gv->Start();


//    delete gp;
}
