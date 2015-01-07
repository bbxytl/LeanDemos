

//测试时使用的类----已废弃

#include "jsdatabase.h"


bool JSDatabase::DBS_Open(){
    if(!dbs.isOpen()){
        dbs.open();
        ls<<" 已-打开-数据库链接";
    }
    return true;
}
bool JSDatabase::DBS_Close(){
    if(dbs.isOpen()){
        dbs.close();
        ls<<" 已-关闭-数据库链接";
    }
    return true;
}
bool JSDatabase::DBS_Query(QString sqr){

    {
        QSqlQuery qy(sqr,dbs);
        query=qy;
    }

        ls<<" 已-执行-查询信息";
        int n=query.size();
        ls<<QString(n);
        while (query.next()){
            ls << query.value(0).toString() +"   " + query.value(1).toString();

        }
        n = query.size();
        n++;

    return true;
}
