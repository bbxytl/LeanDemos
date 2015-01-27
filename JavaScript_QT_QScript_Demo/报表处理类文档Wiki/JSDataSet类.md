##JSDataSet
继承自`QObject`,	`class JSDataSet : public QObject` 。主要用来连接数据库、查询数据库以及操作生成自定义数据源。提供给`JavaScript`代码使用。包装了`QSqlDatabase`,`QSqlQuery`,`CustomDataSet`三个类的方法。
####构造函数、析构函数
----------
	explicit JSDataSet(QObject *parent=0);
    explicit JSDataSet(const QString &con,QObject *parent=0);
    explicit JSDataSet(const QString &con,
                       const QString &sql,
                       QObject *parent = 0);
	~JSDataSet();
####public函数
----------
######包装的`QSqlDatabase`方法
	Q_INVOKABLE bool open();
    Q_INVOKABLE void close();
    Q_INVOKABLE bool isOpen();
    Q_INVOKABLE bool isClose();
    Q_INVOKABLE QString databaseName() ;
    Q_INVOKABLE QString driverName();

    Q_INVOKABLE bool contains(const QString & connectionName);
    Q_INVOKABLE QString connectionName();

    QStringList connectionNames();

    Q_INVOKABLE QString   getSqlString();     //获取Sql语句
    Q_INVOKABLE QString   getConString();     //获取链接字符串
    Q_INVOKABLE void setConString(const QString & con);    //设置链接字符串
    Q_INVOKABLE void setSqlString(const QString & sql);    //设置SQL语句

    Q_INVOKABLE void setDatabase(const QString &conType,   //添加数据链接
                                 const QString &conName="default");
    Q_INVOKABLE void removeDatabase(const QString & conName);   //移除数据链接

    QSqlDatabase *  getDatabaseObject();//获取数据库链接对象

######包装的`QSqlQuery`方法
    Q_INVOKABLE bool query();
    Q_INVOKABLE bool query(const QString & sql);
    Q_INVOKABLE bool isSelect();
    Q_INVOKABLE bool isValid();
    Q_INVOKABLE bool isNull(int field);
    Q_INVOKABLE bool isNull(const QString & name);
    Q_INVOKABLE int  at();
    Q_INVOKABLE void clearQuery();
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
    Q_INVOKABLE int valueToInt(int index) ;
    Q_INVOKABLE int valueToInt(const QString & name) ;
    Q_INVOKABLE double valueToDouble(int index) ;
    Q_INVOKABLE double valueToDouble(const QString & name) ;

    Q_INVOKABLE QString     lastQuery() ;
    Q_INVOKABLE QSqlError   lastError() ;

    QSqlQuery    *  getQueryObject();   //获取数据处理对象

######包装的`CustomDataSet`方法
    CustomDataSet * getCustomDataObject();   //获取数据对象

    Q_INVOKABLE void clearCustomData();

    Q_INVOKABLE void addData(const QList<QVariantList> &datas );
    Q_INVOKABLE void addCols(const QStringList &cols);
    Q_INVOKABLE void insertData(const QVariantList &data,const int pos=-1);
    Q_INVOKABLE void insertCol(const QString &columnName,const int pos=-1);
    Q_INVOKABLE int  getColsCount( );    //获取列数
    Q_INVOKABLE int  getRowsCount( );    //获取行数

    Q_INVOKABLE QVariant getData(const int row,const int col);
    Q_INVOKABLE bool modifyData(const int row, const int col,
                                const QVariant &data=QVariant());
    Q_INVOKABLE bool modifyCol(const int col, const QString &data);
    Q_INVOKABLE bool modifyCol(const QString &colNameOld,
                               const QString &colNameNew);
    Q_INVOKABLE QVariant removeData(const int pos=-1);   //remove one data
    Q_INVOKABLE void setID(const QString &dsid);    //设置数据前要先设置这个,数据源ID

    Q_INVOKABLE void clear();       //清除上一次的数据、查询、调用信息

    Q_INVOKABLE void setObjectId(int objectid=1);    //创建类对象时对应的对象id编号
    Q_INVOKABLE int  getObjectId();

####private函数
----------
    void initClass();   //初始化属性字段

####private属性
----------
	int          m_objectId; //类对象对应的Id编号
    QSqlDatabase m_dbs;     //数据库对象
    QSqlQuery    m_query;   //处理语句

    QString      m_sql;     //sql语句
    QString      m_con;     //链接字符串

    CustomDataSet *m_custData;          //存储处理好的数据

#相关类
---
   [JSCode类调用方法](JSCode类调用方法.html)
   [JSDBObject](JSDBObject类.html)
   [JSDataSet](JSDataSet类.html)
   [CustomDataSet](CustomDataSet类.html)