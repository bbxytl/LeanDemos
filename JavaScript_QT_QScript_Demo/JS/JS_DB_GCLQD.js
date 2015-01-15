
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
//进度记录：
// 没有进行Flag记录的处理，即不插入没有清单作为子节点的父节点数据以及其对应合计项
// 实验项中数据不齐全，没有连续的两个分部！即if判断中的type===3没有测试！
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
        sqls="select "+
                    " ID          as  '"+asList[t++]+
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
             "',parentid as pkey , key,type, path  from FBTreeData order by path";
    }
    pds.setConString(con);
    pds.setSqlString(sqls);
    pds.setID("cds0");
    pds.setDatabase("QSQLITE","connectName2sdd");
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
    rs=rs+"\n"+"序号   数据dfaesf-------------------"+"\n";
     //设置数据---开始
         var skey =new Array();//存放入栈key
         var stype=new Array();//存放入栈type
         var sdata=new Array();//存放入栈数据
         var sFlag=new Array();//存放入栈数据是否需要合计
         var top=-1;//栈顶

    while(pds.next()){
        var dt=new Array(); //存储一条记录
        //记录数据
        var space="    ";
        rs=rs+(++count)+space;
        for(var j=0;j<pdsColCount;j++){
            rs=rs+pds.value(asList[j])+space;
            var data=pds.value(asList[j]);
            dt.push(data);
        }
          var type=pds.valueToInt("type");	//获取其类型
          var key= pds.value("key");
          rs=rs+"\n"+key+"    "+(type+100)+"\n";
          if(type===1||type===2){
                  skey.push(key);
                  stype.push(type);
                  sdata.push(dt);
                  sFlag.push(0);
                  ++top;
          }else if(type===3){
                  if(pds.value("pkey")!==skey[top]){ //当前数据非栈顶元素的子，需要插入合计并退栈
                      var spopData=sdata.pop();//获取栈顶数据
                      spopData[2]="合计";
                      // if(sFlag[top]===1){
                          pds.insertData(spopData);
                      rs=rs+"\n合计";
                      // }
                      skey.pop();
                      stype.pop();
                      sFlag.pop();
                      --top;
                  }
                }
        pds.insertData(dt); //向数据集添加一条记录
        rs=rs+"\n";
    }
    //数据读取完成，判断栈中是否还有数据
    while(top>-1){
        var spopDataEnd=sdata.pop();//获取栈顶数据
        spopDataEnd[2]="合计";
        // if(sFlag[top]===1){
            pds.insertData(spopDataEnd);
        rs=rs+"\n最后合计  key="+skey[top]+"\n";
        // }
        skey.pop();
        stype.pop();
        sFlag.pop();
        --top;
    }

    rs=rs+"共有 "+count+ " 条数据"+"\n";
    pds.close();
    return rs;
}
/////////////////////////////////添加合计



// function GetDataSource()
// {
    // object.clear();
    // var pds=object.creatDataSetObject();    //创建一个数据源
    // var index=pds.getObjectId();        //获取数据源对应的id
    // //var index=object.getDSObjectID(pds); //另一种获取方式！
    // var rs=setDataSet(pds);     // 给pds设置绑定数据源
    // object.setTemplate("工程量清单项目预算表--ok-14121509-1.xml");
    // object.setUseDataSetID(index);

    // return rs+"\n "+object.getTemplate();
// }


// function setDataSet(pds)
// {
    // //存放要获取的模板中的字段名
    // var asList=new Array("序号",
                         // "清单编码",
                         // "项目名称",
                         // "计量单位",
                         // "工程量",
                         // "人工费",
                         // "辅材费",
                         // "主材费",
                         // "机械费",
                         // "管理费",
                         // "利润费",
                         // "综合单价",
                         // "合价"
                         // )
    // var con="datas.db";
    // var sqls;  //字段别名对应 asList 里的顺序！
    // {
        // var t=0;
        // sqls="select  key, parentid as pkey ,path,type"+
                    // " ,ID          as  '"+asList[t++]+
                    // "',CODE        as  '"+asList[t++]+
                    // "',NAME        as  '"+asList[t++]+
                    // "',UNIT        as  '"+asList[t++]+
                    // "',Matecount   as  '"+asList[t++]+
                    // "',Labor       as  '"+asList[t++]+
                    // "',Material    as  '"+asList[t++]+
                    // "',MainMaterialEquipment as '"+asList[t++]+
                    // "',Machine     as  '"+asList[t++]+
                    // "',Overhead    as  '"+asList[t++]+
                    // "',Profit      as  '"+asList[t++]+
                    // "',(Labor   + Material + MainMaterialEquipment"+
                    // "+ Machine + Overhead + Profit)   "+     //综合单价
                               // "   as  '"+asList[t++]+
                    // "',((Labor   + Material + MainMaterialEquipment"+
                    // "+   Machine + Overhead + Profit) * Matecount) "+
                               // "   as  '"+asList[t++]+        //合价
             // "'  from FBTreeData order by path";
    // }
    // pds.setConString(con);
    // pds.setSqlString(sqls);
    // pds.setID("cds0");
    // pds.setDatabase("QSQLITE","connectName1");
// //  绑定到模板中的字段名
    // for(var i=0;i<asList.length;++i){
        // pds.insertCol(asList[i]);
    // }

    // pds.open();
    // if(!pds.isOpen())return pds.getConString();
    // pds.query();

    // var pdsColCount=pds.getColsCount();    //获取列数
    // var count=0;
    // var rs="The result---1 of Query:";
    // rs=rs+"\n"+"序号   数据-------------------"+"\n";
// //设置数据---开始
	// var skey =new Array();//存放入栈key
	// var stype=new Array();//存放入栈type
	// var sdata=new Array();//存放入栈数据
	// var sFlag=new Array();//存放入栈数据是否需要合计
	// var top=-1;//栈顶
    // while(pds.next()){
        // //一条数据的key-pkey-row-childs 映射集
        // var dt=new Array(); //存储一条记录
			
        // //获取一条数据
				// var space="    ";
				// rs=rs+(++count)+space;
        // for(var j=0;j<pdsColCount;j++){
				// rs=rs+pds.value(asList[j])+space;
            // var data=pds.value(asList[j]);
            // dt.push(data);
        // }
		
		// // var type=pds.valueToInt("type");	//获取其类型
		// // var key= pds.value("key");
		// // switch(type){
			// // case 1:{
				// // skey.push(key);
				// // stype.push(type);
				// // sdata.push(dt);
				// // sFlag.push(0);
				// // ++top;
			// // }break;
			// // case 2:{
				// // skey.push(key);
				// // stype.push(type);
				// // sdata.push(dt);
				// // sFlag.push(0);
				// // ++top;
			// // }break;
			// // case 3:{
				// // if(pds.value("pkey")!=skey[top]){ //当前数据非栈顶元素的子，需要插入合计并退栈
					// // var spopData=sdata.pop();//获取栈顶数据
					// // spopData[2]="合计";
					// // // if(sFlag[top]===1){
						// // pds.insertData(spopData);
					// // // }
					// // skey.pop();
					// // stype.pop();
					// // sFlag.pop();
					// // --top;
				// // }else{
					
				// // }
			// // }break;
			// // case 4:{
			// // }break;
		// // }
        // pds.insertData(dt);
				// rs=rs+"\n";
    // }
// //设置数据---结束
    // rs=rs+"共有 "+count+ " 条数据"+"\n";
    // pds.close();
    // return rs;
// }




//function GetDataSource()
//{
//    object.clear();
//    var pds=object.creatDataSetObject();    //创建一个数据源
//    var index=pds.getObjectId();        //获取数据源对应的id
//    //var index=object.getDSObjectID(pds); //另一种获取方式！
//    var rs=setDataSet(pds);     // 给pds设置绑定数据源
//    object.setTemplate("工程量清单项目预算表--ok-14121509-1.xml");
//    object.setUseDataSetID(index);

//    return rs+"\n "+object.getTemplate();
//}

//var keyRow=new Array();

//function setDataSet(pds)
//{
//    //存放要获取的模板中的字段名
//    var asList=new Array("序号",
//                         "清单编码",
//                         "项目名称",
//                         "计量单位",
//                         "工程量",
//                         "人工费",
//                         "辅材费",
//                         "主材费",
//                         "机械费",
//                         "管理费",
//                         "利润费",
//                         "综合单价",
//                         "合价"
//                         )
//    var con="datas.db";
//    var sqls;  //字段别名对应 asList 里的顺序！
//    {
//        var t=0;
//        sqls="select  key, parentid as pkey "+
//                    " ,ID          as  '"+asList[t++]+
//                    "',CODE        as  '"+asList[t++]+
//                    "',NAME        as  '"+asList[t++]+
//                    "',UNIT        as  '"+asList[t++]+
//                    "',Matecount   as  '"+asList[t++]+
//                    "',Labor       as  '"+asList[t++]+
//                    "',Material    as  '"+asList[t++]+
//                    "',MainMaterialEquipment as '"+asList[t++]+
//                    "',Machine     as  '"+asList[t++]+
//                    "',Overhead    as  '"+asList[t++]+
//                    "',Profit      as  '"+asList[t++]+
//                    "',(Labor   + Material + MainMaterialEquipment"+
//                    "+ Machine + Overhead + Profit)   "+     //综合单价
//                               "   as  '"+asList[t++]+
//                    "',((Labor   + Material + MainMaterialEquipment"+
//                    "+   Machine + Overhead + Profit) * Matecount) "+
//                               "   as  '"+asList[t++]+        //合价
//             "'  from FBTreeData";
//    }
//    pds.setConString(con);
//    pds.setSqlString(sqls);
//    pds.setID("cds0");
//    pds.setDatabase("QSQLITE","connectName1");
////  绑定到模板中的字段名
//    for(var i=0;i<asList.length;++i){
//        pds.insertCol(asList[i]);
//    }

//    pds.open();
//    if(!pds.isOpen())return pds.getConString();
//    pds.query();

//    var pdsColCount=pds.getColsCount();    //获取列数
//    var count=0;
//    var rs="The result---1 of Query:";
//    rs=rs+"\n"+"序号   数据-------------------"+"\n";

//    var rootkr={key:0,row:-1,pkey:0,childs:0};
//    keyRow.push(rootkr);//添加根行

//    while(pds.next()){
//        //一条数据的key-pkey-row-childs 映射集
//        var dt=new Array(); //存储一条记录
//        var ky= pds.value("key");
//        var pky=pds.value("pkey");
//        var kr={key:ky,row:0,pkey:pky,childs:0};
//        var index=findKey(pkey);
//        var prow=keyRow[index].row;
//        var pchilds=keyRow[index].childs;
//        kr.row=prow+(pchilds+1);
//        keyRow[index].childs+=1;

//        keyRow.push(kr);

//        //获取一条数据
//        var space="    ";
//        rs=rs+(++count)+space;
//        for(var j=0;j<pdsColCount;j++){
//            rs=rs+pds.value(asList[j])+space;
//            var data=pds.value(asList[j]);
//            dt.push(data);
//        }
//        //向数据集添加一条记录
//        var bl=0;
//        if(kr.row<=pds.getRowsCount()){  //如果在记录的中间插入，则置1
//            bl=1;
//        }
//        pds.insertData(dt,kr.row);
//        update(pds,bl);//更新key行映射
//        rs=rs+"\n";
//    }
//    rs=rs+"共有 "+count+ " 条数据"+"\n";
//    pds.close();
//    return rs;
//}

function update(pds,bl){
    if(bl===1){ //仅在中间插入时才更新编号映射

    }
}
//返回对应key值存储在keyRow中的位置
function findKey(key){
    for(var i=0;i<keyRow.length;i++){
        var kr=keyRow[i];
        if(kr.key===key){
            return i;
        }
    }
}


//////////////////////////////
function getRow(pds,kr){
    var row=0;
    var i=findKey(kr.pkey);
    row = keyRow[i].row;
    var cd=keyRow[i].childs;
    row=row+cd+1;
    return row;
}

function getChilds(pds,kr){
    var childs=0;
    var i=findKey(kr.pkey);
    childs=keyRow[i].childs;
    return childs;
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
