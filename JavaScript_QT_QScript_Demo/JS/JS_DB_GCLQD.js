function GetDataSource()
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
