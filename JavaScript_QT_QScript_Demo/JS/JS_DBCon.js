function GetDataSource()
{

    var sqls="select  top 50  \
                Code as 'id',  \
                Name as 'name',\
                Spec as 'test', \
                Code as '编号',  \
                Name as '数据',\
                Spec as '测试' \
            from tblBill";
//JSDataSet类

    pds.setID("cds0");

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
    pds.query(sqls);
    var count=0;
    var rs="The result of Query:";
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


//JSDatabase类调用方法
//    pDS.SetList(sqls);

//    if(pDS.DBS_Open())
//    {
//        pDS.SetList("bool SuS");
//        pDS.DBS_Query(sqls);
//    }else{
//        pDS.SetList("bool Fal");
//    }

//    pDS.DBS_Close();


}

