function GetDataSource()
{
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

    var sqls="select *from tblbill";
    pDS.SetList(sqls);

    pDS.GetDBS().open( );
    pDS.GetQuery().prepare(sqls);
    pDS.GetDBS().close();

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
