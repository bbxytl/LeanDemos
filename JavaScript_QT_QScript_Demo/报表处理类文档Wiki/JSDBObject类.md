##JSDBObject
继承自`QObject`,	`class JSDBObject : public QObject` 。主要用来管理`JSDataSet`类的创建和删除，以及建立各`JSDataSet`对象的父子关系，提供给`JavaScript`代码使用。管理和`JavaScript`的交互。
####构造函数、析构函数
----------
	explicit JSDBObject(QObject *parent = 0);
    ~JSDBObject();
####public函数
----------
	Q_INVOKABLE JSDataSet * creatDataSetObject(int parentID=0); // 创建一个JSDataSet对象并制定其父级对象，设置其自己的ObjectId
    Q_INVOKABLE int         getCurDSObjectID(); // 获取当前使用JSDataSet对象的ObjectId
    Q_INVOKABLE JSDataSet * getDSObject(const int objectID); // 根据ObjectId获取对象
    Q_INVOKABLE int         getDSObjectID(JSDataSet *jsdataset); // 根据对象获取其ObjectId
    Q_INVOKABLE QList<int>  getDSChildIDs(int parentID); // 根据ObjectId获取其孩子对象的ObjectId
    Q_INVOKABLE int         getDSParentID(int objectID); //根据ObjectId获取其父对象的ObjectId

    Q_INVOKABLE QString getCon(); 				// 获取数据库链接字符串
    Q_INVOKABLE void    setCon(QString con);    // 设置数据库链接字符串

    Q_INVOKABLE int     getUseDataSetID();		// 获取将在报表中使用的数据源JSDataSet对象的ObjectId
    Q_INVOKABLE void    setUseDataSetID(int useDataSetID);  //设置要使用的数据源JSDataSet对象的ObjectId

    Q_INVOKABLE bool    deleteDSObject(int objectID); // 删除指定的JSDataSet对象
    Q_INVOKABLE void    clear(); //清空所有的JSDataSet数据源对象

    Q_INVOKABLE QString    getTemplate(); // 获取报表模板文件路径
    Q_INVOKABLE void       setTemplate(QString templateName); // 设置报表模板文件路径   

    Q_INVOKABLE QString    getJSCode(); //获取报表模板对应的JavaScript代码文件
    Q_INVOKABLE void       setJSCode(QString fileName); //设置报表模板对应的JavaScript代码文件

####private属性
----------
	QHash<int,JSDataSet*> * m_hashObjects;	// Hash映射：ObjectId，JSDataSet*
    QHash<int,int>        * m_hashID;		// Hash映射：ObjectId，parentObjectId
    QString                 m_con;    		// 数据库链接字符串
    QString                 m_template;     // 存放NCReport模板文件的路径
    QString                 m_fileName;     // 存放模板对应的JScode文件路径
    int   m_autoId;				// ObjectId自增长
    int   m_curObjectId;		// 当前JSDataSet对象的ObjectId
    int   m_setUseDataSetID;	// 设置要使用的数据源对象的ObjectId
#相关类
---
   [JSCode类调用方法](JSCode类调用方法.html)
   [JSDBObject](JSDBObject类.html)
   [JSDataSet](JSDataSet类.html)
   [CustomDataSet](CustomDataSet类.html)