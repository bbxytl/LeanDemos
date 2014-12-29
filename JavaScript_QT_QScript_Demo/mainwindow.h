#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ahead.h"
#include <QLabel>

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

    void on_action_Run_triggered();

    void on_act_Open_triggered();

    void on_pushButton_Save_clicked();

private:
    void EnableControl(bool bf);  //设置部分控件的可用性

private:
    Ui::MainWindow *ui;

    QString m_fileName;       //存放JS脚本文件路径
    QString m_ScriptString; //存放读取的JS脚本

    QScriptEngine m_engine;   //JS解析引擎

    QLabel * m_label; //状态栏显示状态
};


//测试使用的数据类
class Mes:public QObject{   //类必须继承自 QObject
    Q_OBJECT
public:
    explicit Mes(QObject * parent = 0):QObject(parent){
    }
    ~Mes(){}

    Q_INVOKABLE QString GetMessage(){   //方法前必须要有 Q_INVOKABLE
        return m_Text;
    }
    Q_INVOKABLE void SetMessage(QString text){
        m_Text=text;
    }

private:
    Q_INVOKABLE QString m_Text; //经测试，即使m_Text为public，也不能在JS里直接使用对象进行调用
                                //所以使用 Get 和 Set 函数进行处理
};

#endif // MAINWINDOW_H
