#ifndef JSDATASET_H
#define JSDATASET_H

#include "ahead.h"

#include <QObject>

class JSDataSet : public QObject
{
    Q_OBJECT
public:
    explicit JSDataSet(QObject *parent=0);
    explicit JSDataSet(const QString &con,QObject *parent=0);
    explicit JSDataSet(const QString &con,
                       const QString &sql,
                       QObject *parent = 0);
    ~JSDataSet(){}

    //数据获取--包装方法
    Q_INVOKABLE void open();
    Q_INVOKABLE void close();
    Q_INVOKABLE bool isOpen();
    Q_INVOKABLE bool isClose();
    Q_INVOKABLE QString databaseName() ;
    Q_INVOKABLE QString driverName();
    Q_INVOKABLE bool contains(const QString & connectionName);
    Q_INVOKABLE QString connectionName();

    QStringList connectionNames();

    Q_INVOKABLE bool query();
    Q_INVOKABLE bool query(const QString & sql);
    Q_INVOKABLE bool isSelect();
    Q_INVOKABLE bool isValid();
    Q_INVOKABLE bool isNull(int field);
    Q_INVOKABLE bool isNull(const QString & name);
    Q_INVOKABLE int  at();
    Q_INVOKABLE void clear();
    Q_INVOKABLE bool first();
    Q_INVOKABLE bool last();
    Q_INVOKABLE bool next();
    Q_INVOKABLE bool previous();
    Q_INVOKABLE bool seek(int index, bool relative = false);
    Q_INVOKABLE bool prepare(const QString & query);
    Q_INVOKABLE bool exec(const QString & query);
    Q_INVOKABLE bool exec();

    Q_INVOKABLE QString value(int index) ;
    Q_INVOKABLE QString value(const QString & name) ;

    Q_INVOKABLE QString     lastQuery() ;
    Q_INVOKABLE QSqlError   lastError() ;

    Q_INVOKABLE void setConString(const QString & con);    //设置链接字符串
    Q_INVOKABLE void setSqlString(const QString & sql);    //设置SQL语句
    Q_INVOKABLE void setDatabase(const QString &conType,   //添加数据链接
                                 const QString &conName);
    Q_INVOKABLE void removeDatabase(const QString & conName);   //移除数据链接

    Q_INVOKABLE void    clearInformationLs();
    Q_INVOKABLE void    setIsShowInformation(bool bl);
    Q_INVOKABLE bool    getIsShowInformation( );
    Q_INVOKABLE QString getInformationString(const QString &delimiter); //获取调用信息

    Q_INVOKABLE QString   getSqlString();     //获取Sql语句
    Q_INVOKABLE QString   getConString();     //获取链接字符串

    QSqlDatabase *  getDatabaseObject();//获取数据库链接对象
    QSqlQuery    *  getQueryObject();   //获取数据处理对象
    QVariant        getValue();
    QStringList  *  getInformationLs(); //获取调用信息


    //数据处理方法--自定义数据



signals:

public slots:

private:
    QSqlDatabase m_dbs;     //数据库对象
    QSqlQuery    m_query;   //处理语句

    QString      m_sql;     //sql语句
    QString      m_con;     //链接字符串

    QVariant     m_value; //存储

    QStringList  m_informationls;     //调用记录
    bool         m_showInfor;         //判断是否有权显示调用记录


};

#endif // JSDATASET_H
