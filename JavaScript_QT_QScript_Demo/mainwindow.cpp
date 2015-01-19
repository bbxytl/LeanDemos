#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_fileName="JSCode.js";
    m_fileName="工程量清单项目预算表.js";       //无输出---最终的JS
//    m_fileName="工程量清单项目预算表_GCLQD.js";    //有输出

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
    m_objects =new JSDBObject();
//重要代码
    qScriptRegisterQObjectMetaType<JSDataSet*>(&m_engine);//注册 JSDataSet*
    //向JS里添加全局变量
    m_global = m_engine.globalObject();    //获取全局对象
    QScriptValue object= m_engine.newQObject(m_objects);   //创建一个全局对象
    m_global.setProperty("object",object);
}

MainWindow::~MainWindow()
{
    delete m_label;
    delete m_report;
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
            ui->textEdit_EditJS->append(
                        "\n//"+m_fileName+"  文件不存在！进行新建。。。\n");
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
        ui->textEdit_EditJS->append("\n//"+m_fileName+"读取JS文件错误\n");
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

void MainWindow::Test()
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
//    QString ip="192.168.0.150",name="sa",pass="engires",dbname="ER_BILL_10";
//    int     port=1433;
//    QString con=QString("Driver={sql server};SERVER=%1;PORT=%2;DATABASE=%3;\
//                        UID=%4;PWD=%5;").arg(ip).arg(port).arg(dbname)
//                        .arg(name).arg(pass);

    m_engine.evaluate(m_ScriptString);

    //调用执行JavaScript里的函数
    QScriptValue func = m_global.property(sFunName);       //根据函数名获取到函数
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
    ui->action_Pre->setEnabled(true);

#endif
}


void MainWindow::on_action_Run_triggered()
{
    Test();
}

void MainWindow::EnableControl(bool bf)
{
    ui->action_FunArgs->setEnabled(bf);
    ui->action_RS->setEnabled(bf);
    ui->action_Run->setEnabled(bf);
    ui->action_Clear->setEnabled(bf);
}

void MainWindow::setCustomData(int customDataId)
{
    m_report->addCustomDataSource(m_objects->
                                      getDSObject(customDataId)->
                                          getCustomDataObject());
}

void MainWindow::on_action_Pre_triggered()
{

//    QString templateFile="customdatasource_demo.xml";
//    QString templateFile="customdatasource_demo1.xml";
//    QString templateFile="E:/Documents/My-Doc/YinLei--WorkDoc/myReports/工程量清单项目预算表--ok-14121509-1.xml";
    QString templateFile=m_objects->getTemplate();

#if 1
    m_report->reset();

    setCustomData(m_objects->getUseDataSetID());

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
    m_report->reset();
}

QString MainWindow::getJSCode()
{
    m_fileName=m_objects->getJSCode();
    return m_fileName;
}

void MainWindow::setJSCode(QString fileName)
{
    m_objects->setJSCode(fileName);
}
