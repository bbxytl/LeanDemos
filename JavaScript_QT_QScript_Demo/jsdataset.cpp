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
    m_informationls.clear();
    m_informationls.append("调用信息：");
    m_showInfor=false;
    m_custData=new CustomDataSet();
}

void JSDataSet::open()
{
    if(!m_dbs.isOpen()){
        m_dbs.open();
        m_informationls.append("Database is opened .");
    }else
        m_informationls.append("Database is already opened .");
}

void JSDataSet::close()
{
    if(m_dbs.isOpen()){
        m_dbs.close();
        m_informationls.append("Database is closed .");
    }else
        m_informationls.append("Database is already closed .");
}

bool JSDataSet::isOpen()
{
    if(m_dbs.isOpen()){
        m_informationls.append("Database is opened .");
        return true;
    }
    m_informationls.append("Database is not opened .");
    return false;
}

bool JSDataSet::isClose()
{
    if(m_dbs.isOpen()){
        m_informationls.append("Database is not closed .");
        return false;
    }
    m_informationls.append("Database is closed .");
    return true;
}

QString JSDataSet::databaseName()
{
    m_informationls.append("Call Database databaseName() .");
    return m_dbs.databaseName();
}

QString JSDataSet::driverName()
{
    m_informationls.append("Call Database driverName() .");
    return m_dbs.driverName();
}

bool JSDataSet::contains(const QString &connectionName)
{
    m_informationls.append("contains( "+connectionName+" ) .");
    return m_dbs.contains(connectionName);
}

QString JSDataSet::connectionName()
{
    m_informationls.append("Call Database connectionName() .");
    return m_dbs.connectionName();
}

QStringList JSDataSet::connectionNames()
{
    m_informationls.append("Call Database connectionNames() .");
    return m_dbs.connectionNames();
}

bool JSDataSet::query()
{
    QSqlQuery qy(m_sql,m_dbs);
    m_query.clear();
    m_query=qy;
    m_informationls.append("Query is going ...");
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
    if(m_query.isSelect()){
        m_informationls.append("Query is 'Select' .");
        return true;
    }
    m_informationls.append("Query is not 'Select' .");
    return false;
}

bool JSDataSet::isValid()
{
    if(m_query.isValid()){
        m_informationls.append("Query is Valid .");
        return true;
    }
    m_informationls.append("Query is unValid .");
    return false;
}

bool JSDataSet::isNull(int field)
{
    if(m_query.isNull(field)){
        m_informationls.append("Index of "+QString(field)+" is Null .");
        return true;
    }
    m_informationls.append("Index of "+QString(field)+" is not Null .");
    return false;
}

bool JSDataSet::isNull(const QString &name)
{
    if(m_query.isNull(name)){
        m_informationls.append("Index of name is Null .");
        return true;
    }
    m_informationls.append("Index of name is not Null .");
    return false;
}

int JSDataSet::at()
{
    m_informationls.append("Call Query at() .");
    return m_query.at();
}

void JSDataSet::clearQuery()
{
    m_informationls.append("Call Query clear() .");
    m_query.clear();
}

bool JSDataSet::first()
{    
    m_informationls.append("Call Query first() .");
    return m_query.first();
}

bool JSDataSet::last()
{
    m_informationls.append("Call Query last() .");
    return m_query.last();
}

bool JSDataSet::next()
{    
    m_informationls.append("Call Query next() .");
    return m_query.next();
}

bool JSDataSet::previous()
{
    m_informationls.append("Call Query previous() .");
    return m_query.previous();
}

bool JSDataSet::seek(int index, bool relative)
{
    m_informationls.append("Call Query seek( "
                           +QString(index)+" ,"
                           +QString(relative)+" ) .");
    return m_query.seek(index,relative);
}

bool JSDataSet::prepare(const QString &query)
{
    m_informationls.append("Call Query prepare( "+query+" ) .");
    return m_query.prepare(query);
}

bool JSDataSet::exec(const QString &query)
{
    m_informationls.append("Call Query exec( "+query+" ) .");
    return m_query.exec(query);
}

bool JSDataSet::exec()
{
    m_informationls.append("Call Query exec() .");
    return m_query.exec();
}

QString JSDataSet::value(int index)
{
    m_informationls.append("Call Query value( "
                           +QString(index)+" ) .");
    m_value=m_query.value(index);
    return m_value.toString();
}

QString JSDataSet::value(const QString &name)
{
    m_informationls.append("Call Query value( "+name+" ) .");
    m_value=m_query.value(name);
    return m_value.toString();
}

QString JSDataSet::lastQuery()
{    
    m_informationls.append("Call Query lastQuery( ) .");
    return m_query.lastQuery();
}

QSqlError JSDataSet::lastError()
{
    m_informationls.append("Call Query lastError( ) .");
    return m_query.lastError();
}

void JSDataSet::setConString(const QString &con)
{
    m_informationls.append("Call Query setConString( ) .");
    m_con=con;
}

void JSDataSet::setSqlString(const QString &sql)
{
    m_informationls.append("Call Query setSqlString( ) .");
    m_sql=sql;
}

//数据库链接
void JSDataSet::setDatabase(const QString &conType, const QString &conName)
{
    m_informationls.append("Call Query setDatabase() .");
    if(!m_dbs.contains(conName)){
        m_dbs=QSqlDatabase::addDatabase(conType,conName);
        m_dbs.setDatabaseName(m_con);
    }else{
        m_dbs=m_dbs.database(conName);
    }
}

void JSDataSet::removeDatabase(const QString &conName)
{
    m_informationls.append("Call Query removeDatabase() .");
    m_dbs.removeDatabase(conName);
}

void JSDataSet::clearInformationLs()
{
    m_informationls.clear();
    m_informationls.append("调用信息：");
}

void JSDataSet::setIsShowInformation(bool bl)
{
    m_informationls.append("set the ShowCallInformation : "
                           +QString(bl)+" .");
    m_showInfor=bl;
}

bool JSDataSet::getIsShowInformation()
{
    m_informationls.append("Call Query getShowCallInformation( ) .");
    return m_showInfor;
}

QString JSDataSet::getInformationString(const QString &delimiter)
{
    m_informationls.append("Call Query getInformationString( ) .");
    QString infor="";
    if(getIsShowInformation()){
        foreach (QString var, m_informationls) {
            infor=infor+var+delimiter;
        }
    }
    return infor;
}

QString JSDataSet::getSqlString()
{
    m_informationls.append("Call Query getSqlString( ) .");
    return m_sql;
}

QString JSDataSet::getConString()
{
    m_informationls.append("Call Query getConString( ) .");
    return m_con;
}

QSqlDatabase *JSDataSet::getDatabaseObject()
{
    m_informationls.append("Call Query getDatabaseObject( ) .");
    return &m_dbs;
}

QSqlQuery *JSDataSet::getQueryObject()
{
    m_informationls.append("Call Query getQueryObject( ) .");
    return &m_query;
}

QVariant JSDataSet::getValue()
{
    m_informationls.append("Call Query getValue( ) .");
    return m_value;
}

QStringList *JSDataSet::getInformationLs()
{
    m_informationls.append("Call Query getInformationLs( ) .");
    if(getIsShowInformation()){
        return &m_informationls;
    }else
        return new QStringList();
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

void JSDataSet::insertData(const QList<QVariant> &data, const int pos)
{
    m_custData->insertData(data,pos);
}

void JSDataSet::insertCol(const QString &columnName, const int pos)
{
    m_custData->insertCol(columnName,pos);
}

bool JSDataSet::modifyData( int row, int col,const QVariant &data)
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

void JSDataSet::setID(const QString &dsid)
{
    m_custData->setID(dsid);
}

void JSDataSet::clear()
{
    clearCustomData();
    clearQuery();
    clearInformationLs();
}


