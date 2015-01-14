#include "jsdbobject.h"

JSDBObject::JSDBObject(QObject *parent) :
    QObject(parent)
{
    m_autoId=0;
    m_curObjectId =0;
    m_hashID        = new QHash<int,int>();
    m_hashObjects   = new QHash<int,JSDataSet*>();
    m_template=" ";
}

JSDBObject::~JSDBObject()
{
    delete m_hashID;
    QList<int> ls=m_hashObjects->keys();
    foreach (int key, ls) {
        delete m_hashObjects->value(key);
    }
    delete m_hashObjects;
    qDebug()<<("表清空！");
}

JSDataSet * JSDBObject::creatDataSetObject(int parentID)
{
    qDebug()<<"创建前 m_autoId= "<<m_autoId;
    qDebug()<<"创建前 表中有对象个数： "<<m_hashObjects->size();
    ++m_autoId;
    m_hashID->insert(m_autoId,parentID);
    JSDataSet * jsds=new JSDataSet();
    m_hashObjects->insert(m_autoId,jsds);
    jsds->setObjectId(m_autoId);
    qDebug()<<("创建了一个JSDataSet对象，编号为：")<<m_autoId
              <<"此时表中有对象个数： "<<m_hashObjects->size();
    qDebug()<<"创建前 m_autoId= "<<m_autoId;
    return jsds;
}

int JSDBObject::getCurDSObjectID()
{
    return m_curObjectId;
}

JSDataSet *JSDBObject::getDSObject(const int objectID)
{
    return m_hashObjects->value(objectID);
}

int JSDBObject::getDSObjectID(JSDataSet *jsdataset)
{
    return m_hashObjects->key(jsdataset);
}

QList<int> JSDBObject::getDSChildIDs(int parentID)
{
    QList<int> ls=m_hashID->values();
    QList<int> childIDs;
    foreach (int id, ls) {
        if(id==parentID){
            childIDs.append(m_hashID->key(id));
        }
    }
    return childIDs;
}

int JSDBObject::getDSParentID(int objectID)
{
    return m_hashID->value(objectID);
}

QString JSDBObject::getCon()
{
    return m_con;
}

void JSDBObject::setCon(QString con)
{
    m_con=con;
}

int JSDBObject::getUseDataSetID()
{
    return m_setUseDataSetID;
}

void JSDBObject::setUseDataSetID(int useDataSetID)
{
    m_setUseDataSetID=useDataSetID;
}

bool JSDBObject::deleteDSObject(int objectID)
{
    try{
        delete m_hashObjects->value(objectID);
        m_hashObjects->remove(objectID);
    }catch(...){
        qDebug()<<"删除数据集对象失败！数据集编号： "<<objectID
                  <<" 数据集父数据集编号： "<<m_hashID->value(objectID);
        return false;
    }
    m_hashID->remove(objectID);
    return true;
}

void JSDBObject::clear()
{
    m_autoId=0;
    m_curObjectId=0;
    m_hashID->clear();
    QList<int> ls=m_hashObjects->keys();
    foreach (int key, ls) {
        delete m_hashObjects->value(key);
    }
    m_hashObjects->clear();
}

QString JSDBObject::getTemplate()
{
    return m_template;
}

void JSDBObject::setTemplate(QString templateName)
{
    m_template=templateName;
}

int JSDBObject::autoID()
{
    return (++m_autoId);
}
