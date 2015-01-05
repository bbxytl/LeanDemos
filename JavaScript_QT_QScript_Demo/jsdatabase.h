#ifndef JSDATABASE_H
#define JSDATABASE_H
#include "ahead.h"

class JSDatabase:public QObject{

    Q_OBJECT
public:
    explicit JSDatabase(QObject * parent = 0):QObject(parent){
        m_ds=new QList<QVariant>();
    }
    ~JSDatabase(){
        delete m_ds;
    }

    Q_INVOKABLE QString GetMessage(){ return m_Text; }
    Q_INVOKABLE void SetMessage(QString text){ m_Text=text; }

    //自定义数据类型--二维表
    Q_INVOKABLE QList<QVariant>* GetDataSource(){ return m_ds;}
    Q_INVOKABLE void SetDataSource(QList<QVariant> ds){
        foreach (QVariant v, ds) {
            m_ds->append(v);
        }
    }
    Q_INVOKABLE QList<QString> GetList()
    {
        return ls; }
    Q_INVOKABLE void SetList( QString text){ ls<<text; }

    //数据库链接
    Q_INVOKABLE QSqlDatabase* GetDBS(){ return &dbs; }
    Q_INVOKABLE QSqlQuery* GetQuery( ){ return &query; }

    Q_INVOKABLE bool DBS_Open();
    Q_INVOKABLE bool DBS_Close();
    Q_INVOKABLE bool DBS_Query(QString sqr);
    bool DBS_GetColsName();     //获取列名




public:
    Q_INVOKABLE QString m_Text; //经测试，即使m_Text为public，也不能在JS里直接使用对象进行调用
                                //所以使用 Get 和 Set 函数进行处理

    Q_INVOKABLE QList<QVariant> *m_ds;
    Q_INVOKABLE QList<QString> ls;

    Q_INVOKABLE QSqlDatabase dbs;
    Q_INVOKABLE QSqlQuery query;
};

Q_DECLARE_METATYPE(QSqlDatabase)
Q_DECLARE_METATYPE(QSqlDatabase*)
Q_DECLARE_METATYPE(QSqlQuery)


#endif // JSDATABASE_H
