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
    Q_INVOKABLE int   creatDataSetObject(int parentID=0);
    Q_INVOKABLE int         getCurDSObjectID();
    Q_INVOKABLE JSDataSet * getDSObject(const int objectID);
    Q_INVOKABLE int         getDSObjectID(JSDataSet *jsdataset);
    Q_INVOKABLE QList<int>  getDSChildIDs(int parentID);
    Q_INVOKABLE int         getDSParentID(int objectID);

    Q_INVOKABLE QString getCon();
    Q_INVOKABLE void    setCon(QString con);

    Q_INVOKABLE int     getUseDataSetID();
    Q_INVOKABLE void    setUseDataSetID(int useDataSetID);

    Q_INVOKABLE bool    deleteDSObject(int objectID);
    Q_INVOKABLE void    clear();
private:
    int         autoID();   //自动生成ID

signals:

public slots:
private:
    QHash<int,JSDataSet*> * m_hashObjects;
    QHash<int,int>        * m_hashID;
    QString                 m_con;
    int   m_autoId;
    int   m_curObjectId;
    int   m_setUseDataSetID;
};


#endif // JSDBOBJECT_H
