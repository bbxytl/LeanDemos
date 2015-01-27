##CustomDataSet类
继承自`NCReportDataSource`类，用于保存填充到Report中的自定义数据源。数据存储在一个二维表中，存储容器为`QList`,存储类型为`QList<QVariantList>`。
####构造函数、析构函数
----------
	CustomDataSet::CustomDataSet(QObject * parent) : NCReportDataSource( parent );
	CustomDataSet::~ CustomDataSet();
######Eg.
    CustomDataSet * cds = new CustomDataSet();//构造一个对象
    delete cds; //析构掉

####public函数
----------
######函数名称及意义（自定义）：
	1. void        addData			// 添加一个QList<QVariantList>数据
	2. void        addCols			// 给自定义数据绑定列名称`QStringList`
	3. void        insertData		// 在指定行前添加一行数据
	4. void        insertCol		// 在指定列前加入一列
	5. QVariant    getData			// 获取指定行列位置的数据
	6. bool        modifyData		// 修改指定行列位置的数据
	7. bool        modifyCol		// 修改指定列名
	8. QVariantList    removeData		// 移除指定行
	9. QList<QVariantList>*	getCustomData	//获取二维数据
	10. void       clear			//清空二维数据
######函数及参数原型：
	1.void addData(const QList<QVariantList> &datas );

	2.void addCols(const QStringList &cols);

	3.void insertData(const QVariantList &data,const int pos=-1); 
  
    4.void insertCol(const QString &columnName,const int pos=-1);   

    5.QVariant getData(const int row, const int col);

    6.bool modifyData(const int row, const int col, const QVariant &data=QVariant());

    7.bool modifyCol(const int col, const QString &data);
      bool modifyCol(const QString &colNameOld, const QString &colNameNew);

    8.QVariantList removeData(const int pos=-1);   //remove one data

    9.QList<QVariantList> * getCustomData();

    10.void clear();

######函数名称及意义（继承自`NCReportDataSource`）：
    1.  bool open();		// 打开数据源
    2.  bool close();		// 关闭数据源
    3.  bool first();		// 转到第一条数据
    4.  bool last();		// 转到最后一条数据
    5.  bool next();		// 下一条数据
    6.  bool previous();	// 上一条数据
    7.  bool hasNext();	// 是否有下一条数据
    8.  int size() const;	// 返回数据条数
    9.  QVariant value( const QString&, bool*, int ) const; // 返回指定数据
    10.  QVariant value( int, bool*, int ) const;		//返回指定数据
    11.  bool read( NCReportXMLReader* );
    12.  bool write( NCReportXMLWriter* );
    13.  void evaluate( NCReportEvaluator* );
    14.  bool seek( int index ); // 跳转到指定行数据
    15.  bool isValid() const;
    16.  int columnIndexByName(const QString& columnname) const; //返回列名对应的列号
    17.  int columnCount() const;	// 数据源列数
    18.  int rowCount() const;		// 数据源行数
    19.  QString columnName(int column) const;	//数据源指定列的列名

####private属性
----------
	QList<QVariantList> m_lsVar;    // 保存自定义数据源
    QStringList m_colName;          // 保存自定义数据源每一列的列名

#相关类
---
   [JSCode类调用方法](JSCode类调用方法.html)
   [JSDBObject](JSDBObject类.html)
   [JSDataSet](JSDataSet类.html)
   [CustomDataSet](CustomDataSet类.html)