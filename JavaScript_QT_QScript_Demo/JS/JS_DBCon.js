function GetDataSource()
{

    var sqls="select * from tblbill";
//JSDataSet类的调用方法
    pds.open();
    pds.query(sqls);
    var count=0;
    var rs="The result of Query:";
    rs=rs+"\n"+"序号   数据-------------------"+"\n";
    while(pds.next()){
        rs=rs+(++count)+"    "
                +pds.value(0)+"   "
                +pds.value(1)+"\n";
    }
    rs=rs+"共有 "+count+ " 条数据"+"\n";

    pds.setIsShowInformation(true);
    pds.close();
    return rs;


//JSDatabase类的调用方法
//    pDS.SetList(sqls);

//    if(pDS.DBS_Open())
//    {
//        pDS.SetList("bool SuS");
//        pDS.DBS_Query(sqls);
//    }else{
//        pDS.SetList("bool Fal");
//    }

//    pDS.DBS_Close();


//inserttable();
//    var conn=new ActiveXObject("ADODB.Connection");
//    var rs=new ActiveXObject("ADODB.Recordset");
//    var sqls="select *from FBTreeData";
//    conn.Open("s4");
//    rs.open(sqls,conn);
//    pDS.GetDataSource(rs.GetRows());
////  while(!rs.eof)
////  {
////      rs.MoveNext;
////  }
//    conn.close();
//    rs.close();

//    return "End"
//    dbs.open();

//    var dbs=pDS.GetDBS();
//    pDS.GetDBS().open( );
//    pDS.GetQuery().prepare(sqls);
//    pDS.GetDBS().close();


}



//Other Functions
function createtable()
{
	var conn=new ActiveXObject("ADODB.Connection"); 
	var createsql="create table [curenTable] ([ID] INTEGER PRIMARY KEY,[NUM] TEXT,[NAME] TEXT)";
	conn.Open("s4");
	conn.execute(createsql);
	conn.close();
}

function inserttable()
{
	var conn=new ActiveXObject("ADODB.Connection"); 
	conn.Open("s4");
	conn.execute("insert into curenTable(num,name) values('abc','kobebryant')");
	conn.execute("insert into curenTable(num,name) values('abd','okc')");
	conn.execute("insert into curenTable(num,name) values('abe','lb')");
	conn.close();
}

function droptable()
{
	var conn=new ActiveXObject("ADODB.Connection"); 
	conn.Open("s4");
	conn.execute("delete from curenTable");
	conn.execute("drop table curenTable");
	conn.close();
}
