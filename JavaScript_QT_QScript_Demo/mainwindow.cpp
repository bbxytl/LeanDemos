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

    ui->lineEdit_Fun->setText("GetDataSource");
}

MainWindow::~MainWindow()
{
    delete m_label;
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
    //链接准备
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
    JSDataSet * pds = new JSDataSet(con);  //没有设置SQL语句
    pds->setDatabase("QODBC",dbname);

    //向JS里添加全局变量
    QScriptValue js= m_engine.newQObject(pds);   //创建一个全局对象
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

    ui->textEdit_RS->append(pds->getInformationString("\n"));

//    pds->close();
//    pds->removeDatabase(dbname);
    delete pds;


#endif

#if 0

#if 1
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

void MainWindow::on_act_Open_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    EnableControl(false);
    try{
        QFile scriptFile(m_fileName);
        if(!scriptFile.exists()){
            qDebug()<<"文件不存在！进行新建。。。";
        }else{
            scriptFile.open(QIODevice::ReadOnly);
            QTextStream stream(&scriptFile);
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
        stream<<m_ScriptString;
        scriptFile.close();

    }catch(...){
        qDebug()<<"保存JS文件错误";
    }
    ui->stackedWidget->setCurrentIndex(1);
    m_label->setText("输入要调用的 JS 函数名 和对应的 参数 ...  |   无参函数输入无效 ");
    EnableControl(true);

}

void MainWindow::EnableControl(bool bf)
{
    ui->action_FunArgs->setEnabled(bf);
    ui->action_RS->setEnabled(bf);
    ui->action_Run->setEnabled(bf);
}
