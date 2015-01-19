#ifndef JSDBOBJECT_H
#define JSDBOBJECT_H

#include <QObject>
#include "ahead.h"
#include "jsdataset.h"

class JSDBObject : public QObject
{
    Q_OBJECT
public:
    explicit JSDBObject(QObject *parent = 0);
    ~JSDBObject();
    Q_INVOKABLE JSDataSet * creatDataSetObject(int parentID=0);
    Q_INVOKABLE int         getCurDSObjectID();
    Q_INVOKABLE JSDataSet * getDSObject(const int objectID);
    Q_INVOKABLE int         getDSObjectID(JSDataSet *jsdataset);
    Q_INVOKABLE QList<int>  getDSChildIDs(int parentID);
    Q_INVOKABLE int         getDSParentID(int objectID);

    Q_INVOKABLE QString getCon();
    Q_INVOKABLE void    setCon(QString con);

    Q_INVOKABLE int     getUseDataSetID();
    Q_INVOKABLE void    setUseDataSetID(int useDataSetID);  //设置要使用的数据连接

    Q_INVOKABLE bool    deleteDSObject(int objectID);
    Q_INVOKABLE void    clear();

    Q_INVOKABLE QString    getTemplate();
    Q_INVOKABLE void       setTemplate(QString templateName);    

    Q_INVOKABLE QString    getJSCode();
    Q_INVOKABLE void       setJSCode(QString fileName);


private:
    int         autoID();   //自动生成ID

signals:

public slots:
private:
    QHash<int,JSDataSet*> * m_hashObjects;
    QHash<int,int>        * m_hashID;
    QString                 m_con;    
    QString                 m_template;       //存放NCReport模板文件的路径
    QString                 m_fileName;       //存放模板对应的JScode文件路径
    int   m_autoId;
    int   m_curObjectId;
    int   m_setUseDataSetID;
};


#endif // JSDBOBJECT_H
