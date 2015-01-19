#include "jsdataset.h"

JSDataSet::JSDataSet(QObject *parent):QObject(parent)
{
    initClass();
}

JSDataSet::JSDataSet(const QString &con, QObject *parent):QObject(parent)
{
    initClass();
    m_con=con;
}

JSDataSet::JSDataSet(const QString &con, const QString &sql, QObject *parent) :
    QObject(parent)
{
    initClass();
    m_sql=sql;
    m_con=con;
}

JSDataSet::~JSDataSet()
{
    delete m_custData;
}

void JSDataSet::initClass()
{
    m_sql="";
    m_con="";
    m_custData=new CustomDataSet();
}

bool JSDataSet::open()
{
    if(!m_dbs.isOpen()){
        if(!m_dbs.open())return false;
        else return true;
    }else
        return true;
}

void JSDataSet::close()
{
    if(m_dbs.isOpen()){
        m_dbs.close();
    }
}

bool JSDataSet::isOpen()
{
    if(m_dbs.isOpen())  return true;
    return false;
}

bool JSDataSet::isClose()
{
    if(m_dbs.isOpen())   return false;
    return true;
}

QString JSDataSet::databaseName()
{
    return m_dbs.databaseName();
}

QString JSDataSet::driverName()
{
    return m_dbs.driverName();
}

bool JSDataSet::contains(const QString &connectionName)
{
    return m_dbs.contains(connectionName);
}

QString JSDataSet::connectionName()
{
    return m_dbs.connectionName();
}

QStringList JSDataSet::connectionNames()
{
    return m_dbs.connectionNames();
}

bool JSDataSet::query()
{
    QSqlQuery qy(m_sql,m_dbs);
    m_query.clear();
    m_query=qy;
    if(m_query.lastError().isValid())return false;
    else return true;
}

bool JSDataSet::query(const QString &sql)
{
    m_sql=sql;
    return query();
}

bool JSDataSet::isSelect()
{
    if(m_query.isSelect()) return true;
    return false;
}

bool JSDataSet::isValid()
{
    if(m_query.isValid())  return true;
    return false;
}

bool JSDataSet::isNull(int field)
{
    if(m_query.isNull(field)) return true;
    return false;
}

bool JSDataSet::isNull(const QString &name)
{
    if(m_query.isNull(name))  return true;
    return false;
}

int JSDataSet::at()
{
    return m_query.at();
}

void JSDataSet::clearQuery()
{
    m_query.clear();
}

bool JSDataSet::first()
{
    return m_query.first();
}

bool JSDataSet::last()
{
    return m_query.last();
}

bool JSDataSet::next()
{
    return m_query.next();
}

bool JSDataSet::previous()
{
    return m_query.previous();
}

bool JSDataSet::seek(int index, bool relative)
{
    return m_query.seek(index,relative);
}

bool JSDataSet::prepare(const QString &query)
{
    return m_query.prepare(query);
}

bool JSDataSet::exec(const QString &query)
{
    return m_query.exec(query);
}

bool JSDataSet::exec()
{
    return m_query.exec();
}

QString JSDataSet::value(int index)
{
    m_value=m_query.value(index);
    return m_value.toString();
}

QString JSDataSet::value(const QString &name)
{
    m_value=m_query.value(name);
    return m_value.toString();
}

int JSDataSet::valueToInt(int index)
{
    m_value=m_query.value(index);
    return m_value.toInt();
}

int JSDataSet::valueToInt(const QString &name)
{
    m_value=m_query.value(name);
    return m_value.toInt();
}

double JSDataSet::valueToDouble(int index)
{
    m_value=m_query.value(index);
    return m_value.toDouble();
}

double JSDataSet::valueToDouble(const QString &name)
{
    m_value=m_query.value(name);
    return m_value.toDouble();
}

QString JSDataSet::lastQuery()
{
    return m_query.lastQuery();
}

QSqlError JSDataSet::lastError()
{
    return m_query.lastError();
}

void JSDataSet::setConString(const QString &con)
{
    m_con=con;
}

void JSDataSet::setSqlString(const QString &sql)
{
    m_sql=sql;
}

//数据库链接
void JSDataSet::setDatabase(const QString &conType, const QString &conName)
{
    if("default"==conName){
        m_dbs=QSqlDatabase::addDatabase(conType);
        m_dbs.setDatabaseName(m_con);
    }else{
        if(!m_dbs.contains(conName)){
            m_dbs=QSqlDatabase::addDatabase(conType,conName);
            m_dbs.setDatabaseName(m_con);
        }else{
            m_dbs=m_dbs.database(conName);
        }
    }
}

void JSDataSet::removeDatabase(const QString &conName)
{
    m_dbs.removeDatabase(conName);
}


QString JSDataSet::getSqlString()
{
    return m_sql;
}

QString JSDataSet::getConString()
{
    return m_con;
}

QSqlDatabase *JSDataSet::getDatabaseObject()
{
    return &m_dbs;
}

QSqlQuery *JSDataSet::getQueryObject()
{
    return &m_query;
}

QVariant JSDataSet::getValue()
{
    return m_value;
}


CustomDataSet *JSDataSet::getCustomDataObject()
{
    return m_custData;
}

void JSDataSet::clearCustomData()
{
    m_custData->clear();
}

void JSDataSet::addData(const QList<QVariantList> &datas)
{
    m_custData->addData(datas);
}

void JSDataSet::addCols(const QStringList &cols)
{
    m_custData->addCols(cols);
}

int JSDataSet::getColsCount()
{
    return m_custData->columnCount();
}

int JSDataSet::getRowsCount()
{
    return m_custData->rowCount();
}

void JSDataSet::insertData(const QVariantList &data, const int pos)
{
    m_custData->insertData(data,pos);
}

void JSDataSet::insertCol(const QString &columnName, const int pos)
{
    m_custData->insertCol(columnName,pos);
}

QVariant JSDataSet::getData(const int row, const int col)
{
    return m_custData->getData(row,col);
}

bool JSDataSet::modifyData(const int row,const int col,const QVariant &data)
{
    return m_custData->modifyData(row,col,data);
}

bool JSDataSet::modifyCol(const int col,const QString &data )
{
    return m_custData->modifyCol(col,data);
}

bool JSDataSet::modifyCol(const QString &colNameOld, const QString &colNameNew)
{
    return m_custData->modifyCol(colNameOld,colNameNew);
}

QVariant JSDataSet::removeData(const int pos)
{
    return m_custData->removeData(pos);
}

void JSDataSet::setID(const QString &dsid)
{
    m_custData->setID(dsid);
}

void JSDataSet::clear()
{
    clearCustomData();
    clearQuery();
}

void JSDataSet::setObjectId(int objectid)
{
    m_objectId=objectid;
}

int JSDataSet::getObjectId()
{
    return m_objectId;
}


