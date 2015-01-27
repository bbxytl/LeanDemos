#使用QT调用JavaScript代码进行报表数据源设置
----
##.pro文件设置
**添加NCReport**

	QT       += script sql printsupport
	NCREPORT_INCLUDEPATH = "D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/include"
	NCREPORT_INCLUDEPATH += "C:/Qt/Qt5.3.1/5.3/mingw482_32/include/QtCore/5.3.1"
	NCREPORT_LIBS = "D:/API/NCReport/2.13.0.MinGW.Qt5.3.2.eval/lib/libNCReportDebug2.a"
	LIBS += $$NCREPORT_LIBS
	INCLUDEPATH += $$NCREPORT_INCLUDEPATH
	DEPENDPATH += $$NCREPORT_INCLUDEPATH
**Copy库文件**

将`libNCReportDebug2.dll`拷贝到`Build`目录下(`Debug`目录的同级)。

##设置变量
	QString         m_fileName;       //存放JS脚本文件路径
    QString         m_ScriptString; //存放读取的JS脚本

    QScriptEngine   m_engine;   //JS解析引擎
    NCReport      * m_report;
    JSDBObject    * m_objects;
    QScriptValue    m_global;
##初始化工作
	m_fileName="模板文件JSCode.js";
    m_report =new NCReport();
    m_objects =new JSDBObject();
    qScriptRegisterQObjectMetaType<JSDataSet*>(&m_engine);//注册 JSDataSet*
    //向JS里添加全局变量
    m_global = m_engine.globalObject();    //获取全局对象
    QScriptValue object= m_engine.newQObject(m_objects);   //创建一个全局对象
    m_global.setProperty("object",object);//在JS代码里可以使用object对象
##运行JSCode里的函数
	QString sFunName="要调用的函数名，默认为：'GetDataSource' ";
	m_engine.evaluate(m_ScriptString);	//已读取JScode.js文件内容到m_ScriptString中
	//调用执行JavaScript里的函数
    QScriptValue func = m_global.property(sFunName);       //根据函数名获取到函数
    QScriptValue result = func.call(QScriptValue(),args);//传入参数执行函数
	//....
	//向report中设置数据源
	m_report->addCustomDataSource(m_objects->getDSObject(customDataId)->getCustomDataObject());
	//....

#相关类
---
   [JSCode类调用方法](JSCode类调用方法.html)
   [JSDBObject](JSDBObject类.html)
   [JSDataSet](JSDataSet类.html)
   [CustomDataSet](CustomDataSet类.html)