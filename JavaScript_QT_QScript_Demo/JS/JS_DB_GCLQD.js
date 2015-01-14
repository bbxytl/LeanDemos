function GetDataSource()
{
    object.clear();
    var pds=object.creatDataSetObject();    //创建一个数据源
    var index=pds.getObjectId();        //获取数据源对应的id
    //var index=object.getDSObjectID(pds); //另一种获取方式！
    var rs=setDataSet(pds);     // 给pds设置绑定数据源
    object.setTemplate("工程量清单项目预算表--ok-14121509-1.xml");
    object.setUseDataSetID(index);

    return rs+"\n "+object.getTemplate();
}

function setDataSet(pds)
{
    //存放要获取的模板中的字段名
    var asList=new Array("序号",
                         "清单编码",
                         "项目名称",
                         "计量单位",
                         "工程量",
                         "人工费",
                         "辅材费",
                         "主材费",
                         "机械费",
                         "管理费",
                         "利润费",
                         "综合单价",
                         "合价"
                         )
    var con="datas.db";
    var sqls;  //字段别名对应 asList 里的顺序！
    {
        var t=0;
        sqls="select   ID          as  '"+asList[t++]+
                    "',CODE        as  '"+asList[t++]+
                    "',NAME        as  '"+asList[t++]+
                    "',UNIT        as  '"+asList[t++]+
                    "',Matecount   as  '"+asList[t++]+
                    "',Labor       as  '"+asList[t++]+
                    "',Material    as  '"+asList[t++]+
                    "',MainMaterialEquipment as '"+asList[t++]+
                    "',Machine     as  '"+asList[t++]+
                    "',Overhead    as  '"+asList[t++]+
                    "',Profit      as  '"+asList[t++]+
                    "',(Labor   + Material + MainMaterialEquipment"+
                    "+ Machine + Overhead + Profit)   "+     //综合单价
                               "   as  '"+asList[t++]+
                    "',((Labor   + Material + MainMaterialEquipment"+
                    "+   Machine + Overhead + Profit) * Matecount) "+
                               "   as  '"+asList[t++]+        //合价
             "'  from FBTreeData";
    }
    pds.setConString(con);
    pds.setSqlString(sqls);
    pds.setID("cds0");
    pds.setDatabase("QSQLITE","connectName1");
//  绑定到模板中的字段名
    for(var i=0;i<asList.length;++i){
        pds.insertCol(asList[i]);
    }

    pds.open();
    if(!pds.isOpen())return pds.getConString();
    pds.query();

    var pdsColCount=pds.getColsCount();    //获取列数
    var count=0;
    var rs="The result---1 of Query:";
    rs=rs+"\n"+"序号   数据-------------------"+"\n";
    while(pds.next()){
        var dt=new Array(); //存储一条记录
        //记录数据
        var space="    ";
        rs=rs+(++count)+space;
        for(var j=0;j<pdsColCount;j++){
            rs=rs+pds.value(j)+space;
            var data=pds.value(asList[j]);

            dt.push(data);
        }
        pds.insertData(dt); //向数据集添加一条记录
        rs=rs+"\n";
    }
    rs=rs+"共有 "+count+ " 条数据"+"\n";
    pds.close();
    return rs;
}

///////////////////////////////////////////////////////////////////////////
//  废弃部分


function GetDataSource1()
{
    var sqls="select  top 10 Code as 'id', Name as 'name',Spec as 'test', \
                Code as '编号',Name as '数据',Spec as '测试' from tblBill";
    object.creatDataSetObject();
    var pds1=object.getDSObject(1);
    object.creatDataSetObject();
    var pds2=object.getDSObject(2);
    var rs1=getDataSet1(pds1,sqls);
    var rs2=getDataSet2(pds2,sqls);
    var rs=rs1+"\n\n"+rs2;

    object.setUseDataSetID(2);

    return rs;
}

function getDataSet1(pds,sqls)
{
    var sqls="select  top 20 Code as 'id', Name as 'name',Spec as 'test', \
                Code as '编号',Name as '数据',Spec as '测试' from tblBill";
    var con=object.getCon();

    pds.setConString(con);
    pds.setID("cds0");
    pds.setDatabase("QODBC","dbname1");

//  英文
    pds.insertCol("id");
    pds.insertCol("name");
    pds.insertCol("test");
//  中文
    pds.insertCol("编号");
    pds.insertCol("daf");
    pds.insertCol("测试");

    pds.modifyCol(4,"修改列名-1");
    pds.modifyCol("修改列名-1","数据");

    pds.open();
    if(!pds.isOpen())return pds.getConString();
    pds.query(sqls);
    var count=0;
    var rs="The result---1 of Query:";
    rs=rs+"\n"+"序号   数据-------------------"+"\n";
    while(pds.next()){

        var dt=new Array();
        //记录数据
        rs=rs+(++count)+"    "
                +pds.value(0)+"   "
                +pds.value(1)+"\n";
        for(var i=0;i<pds.getColsCount();i++){
            dt.push(pds.value(i));
        }
        pds.insertData(dt);

    }
    pds.modifyData("modifyDataTest",pds.getRowsCount()-1,pds.getColsCount()-1);
    rs=rs+"共有 "+count+ " 条数据"+"\n";

    pds.setIsShowInformation(false);    //不显示函数调用信息
    pds.close();
    return rs;
}


function getDataSet2(pds,sqls)
{
    var sqls="select  top 10 Code as 'id', Name as 'name',Spec as 'test', \
                Code as '编号',Name as '数据',Spec as '测试' from tblBill";
    var con=object.getCon();
    pds.setConString(con);
    pds.setID("cds0");
    pds.setDatabase("QODBC","dbname2");

//  英文
    pds.insertCol("id");
    pds.insertCol("name");
    pds.insertCol("test");
//  中文
    pds.insertCol("编号");
    pds.insertCol("daf");
    pds.insertCol("测试");

    pds.modifyCol(4,"修改列名-1");
    pds.modifyCol("修改列名-1","数据");

    pds.open();
    if(!pds.isOpen())return pds.getConString();
    pds.query(sqls);
    var count=0;
    var rs="The result---2 of Query:";
    rs=rs+"\n"+"序号   数据-------------------"+"\n";
    while(pds.next()){

        var dt=new Array();
        //记录数据
        rs=rs+(++count)+"    "
                +pds.value(0)+"   "
                +pds.value(1)+"\n";
        for(var i=0;i<pds.getColsCount();i++){
            dt.push(pds.value(i));
        }
        pds.insertData(dt);

    }
    pds.modifyData("modifyDataTest",pds.getRowsCount()-1,pds.getColsCount()-1);
    rs=rs+"共有 "+count+ " 条数据"+"\n";


    pds.setIsShowInformation(false);    //不显示函数调用信息
    pds.close();
    return rs;
}
