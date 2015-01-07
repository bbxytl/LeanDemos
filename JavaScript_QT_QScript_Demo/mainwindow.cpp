#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_fileName="JSCode.js";
    m_fileName="JS_DBCon.js";

    ui->stackedWidget->setCurrentIndex(0);
    ui->splitter->setStretchFactor(1,5);

    m_label = new QLabel();
    m_label->setText("编辑 JavaScript 文件...   |  编辑后保存文件切换到 Run 界面... ");
    ui->statusBar->addWidget(m_label);
    EnableControl(false);
    ui->pushButton_Save->setEnabled(false);
    ui->action_Pre->setEnabled(false);

    ui->lineEdit_Fun->setText("GetDataSource");


    m_report =new NCReport();
//    m_dataSet=new CustomDataSet();
    m_js = new JSDataSet();
}

MainWindow::~MainWindow()
{
    delete m_label;
//    delete m_dataSet;
    delete m_report;
    delete m_js;
    delete ui;
}

void MainWindow::on_action_FunArgs_triggered()
{
    //清空函数和参数
    ui->lineEdit_Fun->clear();
    ui->textEdit_Args->clear();
}

void MainWindow::on_action_RS_triggered()
{
    //清空结果
    ui->textEdit_RS->clear();
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

void MainWindow::on_act_Open_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    EnableControl(false);
    ui->action_Pre->setEnabled(false);
    try{
        QFile scriptFile(m_fileName);
        if(!scriptFile.exists()){
            qDebug()<<"文件不存在！进行新建。。。";
        }else{
            scriptFile.open(QIODevice::ReadOnly);
            QTextStream stream(&scriptFile);
            stream.setCodec("UTF-8");   //使用UTF-8编码读取文件
            m_ScriptString = stream.readAll();
            scriptFile.close();
        }
        ui->textEdit_EditJS->setText(m_ScriptString);
        m_label->setText("编辑 JavaScript 文件...   |  编辑后保存文件切换到 Run 界面... ");
        ui->pushButton_Save->setEnabled(true);
    }catch(...){
        qDebug()<<"读取JS文件错误";
    }
}

void MainWindow::on_pushButton_Save_clicked()
{
    m_ScriptString=ui->textEdit_EditJS->document()->toPlainText();
    try{
        QFile scriptFile(m_fileName);
        scriptFile.open(QIODevice::WriteOnly);
        QTextStream stream(&scriptFile);
        stream.setCodec("UTF-8");   //使用UTF-8编码写入文件
        stream<<m_ScriptString;
        scriptFile.close();

    }catch(...){
        qDebug()<<"保存JS文件错误";
    }
    ui->stackedWidget->setCurrentIndex(1);
    m_label->setText("输入要调用的 JS 函数名 和对应的 参数 ...  |   无参函数输入无效 ");
    EnableControl(true);

}

void MainWindow::on_action_Run_triggered()
{
#if 1
    //所有调用的头准备
    QString sFunName=ui->lineEdit_Fun->text().trimmed(); //设置要调用的JS函数名
    //给函数设置参数
    QStringList sl=ui->textEdit_Args->document()->toPlainText().split("\n");
    QScriptValueList args;
    foreach (QString var, sl) {
        if(var.trimmed()!=""){
            QString v=var.at(0);
            if(v =="d")   //数字
                args<<var.mid(1).toInt();
            else if(v == "s")  //文本
                args<<var.mid(1);
            else{//错误格式
                ui->textEdit_RS->append("参数个数错误！数字前加'd' 文本前加 's'");
                return ;
            }
        }
    }
    //链接准备---可以在JS中设定传入
    QString ip="192.168.0.150";
    int     port=1433;
    QString name="sa";
    QString pass="engires";
    QString dbname="ER_BILL_10";
    QString con=QString("Driver={sql server};\
                        SERVER=%1;\
                        PORT=%2;\
                        DATABASE=%3;\
                        UID=%4;\
                        PWD=%5;")
                        .arg(ip)
                        .arg(port)
                        .arg(dbname)
                        .arg(name)
                        .arg(pass);

    m_engine.evaluate(m_ScriptString);
    QScriptValue global = m_engine.globalObject();    //获取全局对象

#endif

#if 1
    //使用类JSDataSet调用--最终的类
    m_js->clear();
    delete m_js;
    m_js = new JSDataSet(con);  //没有设置SQL语句
//    m_js->setID("cds0");      //放到JS里设置
    m_js->setDatabase("QODBC",dbname);

    //向JS里添加全局变量
    QScriptValue js= m_engine.newQObject(m_js);   //创建一个全局对象
    global.setProperty("pds",js);               //绑定到js里的全局对象名

    //调用执行JavaScript里的函数
    QScriptValue func = global.property(sFunName);       //根据函数名获取到函数
    QScriptValue result = func.call(QScriptValue(),args);//传入参数执行函数

    //输出显示部分
    ui->textEdit_RS->append("调用函数 : "+sFunName);
    QString str;
    foreach (QString var, sl) {
        str=str+var+"  ";
    }
    ui->textEdit_RS->append("函数参数 : "+str);
    ui->textEdit_RS->append("运行结果 :");
    ui->textEdit_RS->append(result.toString());

    ui->textEdit_RS->append(m_js->getInformationString("\n"));

//    m_js->close();
//    m_js->removeDatabase(dbname);
//    delete m_js;


    ui->action_Pre->setEnabled(true);
#endif

    {
#if 0


#if 1
    //测试时使用的类----已废弃
    //使用类JSDatabase的调用---测试类
    //正确的调用方法------  最重要的部分--Begin      JS_DBCon.js

    JSDatabase * pm = new JSDatabase( );

    pm->dbs=QSqlDatabase::addDatabase("QODBC",dbname);

    pm->dbs.setDatabaseName(dsn);

    QScriptValue mes1=m_engine.newQObject(pm);
    global.setProperty("pDS",mes1);

    //调用执行JavaScript里的函数
    QScriptValue func = global.property(sFunName);       //根据函数名获取到函数
    QScriptValue result = func.call(QScriptValue(),args);//传入参数执行函数

    // ------ 最重要的部分 End

    //输出显示部分
    ui->textEdit_RS->append("调用函数 : "+sFunName);
    QString str;
    foreach (QString var, sl) {
        str=str+var+"  ";
    }
    ui->textEdit_RS->append("函数参数 : "+str);
    ui->textEdit_RS->append("运行结果 :");
    ui->textEdit_RS->append(result.toString());


    foreach(QString var,pm->ls){
        ui->textEdit_RS->append(var);
    }

    delete pm;
#endif
#if 1
    //一个简单的调用流程
    //正确的调用方法------  最重要的部分--Begin      JSCode.js    
    JSDatabase * pm = new JSDatabase( );
    pm->SetMessage("TL--HELLo");
    QScriptValue mes1=m_engine.newQObject(pm);
    global.setProperty("pDS",mes1);

#endif

#if 0
    //失败的调用方法    
    QString m_Mes="TL--HELLo";
    QObject * qo = (QObject *)(&m_Mes); //QString不是继承自QObject，转换失败
    qDebug()<<(&m_Mes);
    QScriptValue mes=engine.newQObject(qo); //这里需要传入一个QObject指针对象
    global.setProperty("msg",mes);
#endif

    //调用执行JavaScript里的函数
    QScriptValue func = global.property(sFunName);       //根据函数名获取到函数
    QScriptValue result = func.call(QScriptValue(),args);//传入参数执行函数


    //输出显示部分
    ui->textEdit_RS->append("调用函数 : "+sFunName);
    QString str;
    foreach (QString var, sl) {
        str=str+var+"  ";
    }
    ui->textEdit_RS->append("函数参数 : "+str);
    ui->textEdit_RS->append("运行结果 :");
    ui->textEdit_RS->append(result.toString());

#endif
    }
}

void MainWindow::EnableControl(bool bf)
{
    ui->action_FunArgs->setEnabled(bf);
    ui->action_RS->setEnabled(bf);
    ui->action_Run->setEnabled(bf);
    ui->action_Clear->setEnabled(bf);
}

void MainWindow::setCustomData()
{
    m_report->addCustomDataSource( m_js->getCustomDataObject());
#if 0
    m_dataSet=m_js->getCustomDataObject();

    m_report->addCustomDataSource( m_dataSet );
#endif

#if 0
    CustomDataSet*dvs = new CustomDataSet();
    dvs->setID("cds0");
    QStringList cols;
    cols<<"id"<<"name"<<"test";
    dvs->addCols(cols);
    QList<QVariantList> datas;
    QList<QVariant> lsv;
    lsv<<157<<"Julius"<<"Coronado, CA";
    datas.append(lsv);

    lsv.clear();
    lsv<<127<<"VILLAGE, CA"<<"Peter";
    datas.append(lsv);

    lsv.clear();
    lsv<<157<<"Alexander"<<"San, CA";
    datas.append(lsv);

    dvs->addData(datas);

    m_report->addCustomDataSource( dvs );
#endif

#if 0
    CustomDataSet*dvs = new CustomDataSet();
    dvs->setID("cds0");
    QStringList cols;
    cols<<"id"<<"name"<<"address"<<"valid"<<"date"<<"test";
    dvs->addCols(cols);
    QList<QVariantList> datas;
    QList<QVariant> lsv;
    lsv<<157<<"Julius"<<"Coronado, CA"
         <<false<<QDate(2008,01,12)<<"Test";
    datas.append(lsv);

    lsv.clear();
    lsv<<127<<"VILLAGE, CA"<<"Peter"
         <<"Test"<<QDate(2011,06,10)<<true;
    datas.append(lsv);

    lsv.clear();
    lsv<<157<<"Alexander"<<"San, CA"
         <<false<<QDate(2018,11,23);
    datas.append(lsv);

    dvs->addData(datas);

    m_report->addCustomDataSource( dvs );
#endif
}

void MainWindow::on_action_Pre_triggered()
{

    QString templateFile="customdatasource_demo.xml";
//    QString templateFile="customdatasource_demo1.xml";
#if 0
    NCReport *report = new NCReport();
    report->reset();

//    setCustomData();
#if 1
    CustomDataSet*dvs = new CustomDataSet();
    dvs->setID("cds0");
    QStringList cols;
    cols<<"id"<<"name"<<"address"<<"valid"<<"date"<<"test";
    dvs->addCols(cols);
    QList<QVariantList> datas;
    QList<QVariant> lsv;
    lsv<<157<<"Julius"<<"Coronado, CA"
         <<false<<QDate(2008,01,12)<<"Test";
    datas.append(lsv);

    lsv.clear();
    lsv<<127<<"VILLAGE, CA"<<"Peter"
         <<"Test"<<QDate(2011,06,10)<<true;
    datas.append(lsv);

    lsv.clear();
    lsv<<157<<"Alexander"<<"San, CA"
         <<false<<QDate(2018,11,23);
    datas.append(lsv);

    dvs->addData(datas);

    report->addCustomDataSource( dvs );
#endif

    report->setReportSource( NCReportSource::File );
    report->setReportFile(templateFile);//模板文件
    report->runReportToPreview();

    if(report->hasError()){
        qDebug()<<"Error: customPreView";
        qDebug()<<report->lastErrorMsg();
    }else{
        NCReportPreviewWindow *pv = new NCReportPreviewWindow();
        pv->setOutput((NCReportPreviewOutput *)report->output());
        pv->setWindowModality(Qt::ApplicationModal);
        pv->setAttribute(Qt::WA_DeleteOnClose);
        pv->show();

    }
#endif

#if 1
    m_report->reset();

    setCustomData();

    m_report->setReportSource( NCReportSource::File );
    m_report->setReportFile(templateFile);//模板文件
    m_report->runReportToPreview();

    if(m_report->hasError()){
        qDebug()<<"Error: customPreView";
        qDebug()<<m_report->lastErrorMsg();
    }else{
        NCReportPreviewWindow *pv = new NCReportPreviewWindow();
        pv->setOutput((NCReportPreviewOutput *)m_report->output());
        pv->setWindowModality(Qt::ApplicationModal);
        pv->setAttribute(Qt::WA_DeleteOnClose);
        pv->show();

    }
#endif

}

void MainWindow::on_action_Clear_triggered()
{
    m_js->clear();
    m_report->reset();
}
