#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "ahead.h"
//#include "old\jsdatabase.h"
#include "jsdbobject.h"
#include "jsdataset.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_FunArgs_triggered();

    void on_action_RS_triggered();

    void on_action_Exit_triggered();

    void on_act_Open_triggered();

    void on_pushButton_Save_clicked();

    void Test();

    void on_action_Run_triggered();

    void on_action_Pre_triggered();

    void on_action_Clear_triggered();

public:
    QString getJSCode();
    void    setJSCode(QString fileName);
private:
    void EnableControl(bool bf);  //设置部分控件的可用性
    void setCustomData(int customDataId);

private:
    Ui::MainWindow *ui;

    QString         m_fileName;       //存放JS脚本文件路径
    QString         m_ScriptString; //存放读取的JS脚本

    QScriptEngine   m_engine;   //JS解析引擎

    QLabel        * m_label; //状态栏显示状态

    NCReport      * m_report;
    JSDBObject    * m_objects;
    QScriptValue    m_global;
};



#endif // MAINWINDOW_H
