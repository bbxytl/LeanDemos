
//函数GetDataSource返回的结果为数据处理过程的记录
//用以Debug调试之用，为字符串

function GetDataSource()
{
    object.clear();
    var pds=object.creatDataSetObject();    //创建一个数据源
    var index=pds.getObjectId();        //获取数据源对应的id
    //var index=object.getDSObjectID(pds); //另一种获取方式！
    var rs=setDataSet(pds);     // 给pds设置绑定数据源
    object.setTemplate("07分部分项工程和单价措施项目清单与计价表.xml");
    object.setUseDataSetID(index);
    return rs+"\n"+object.getTemplate();
}

function setDataSet(pds)
{
    //存放要获取的模板中的字段名
    var asList=new Array("序号",
                         "项目编码",
                         "项目名称",
                         "项目特征",
                         "计量单位",
                         "工程数量",
                         "单价",
                         "合价",
                         "暂估价",
                         "分部小计合价",
                         "分部小计暂估价"
                         );
    var con="datas.db";
    var conName="connectNamesds";
    var sqls;  //字段别名对应 asList 里的顺序！
    {
        var t=0;
        sqls="select "+
                    " NUM          as  '"+asList[t++]+
                    "',CODE        as  '"+asList[t++]+
                    "',NAME        as  '"+asList[t++]+
                    "',NAME        as  '"+asList[t++]+ //项目特征，暂时代替
                    "',UNIT        as  '"+asList[t++]+
                    "',Matecount   as  '"+asList[t++]+
                    "',totalPrice  as  '"+asList[t++]+//综合单价
                    "',sum         as  '"+asList[t++]+//合价
                    "',zgj         as  '"+asList[t++]+//暂估价

             "',parentid as pkey , key, type, path  from FBTreeData order by path";
    }
    pds.setConString(con);
    pds.setSqlString(sqls);
    pds.setID("cds0");
    pds.setDatabase("QSQLITE",conName);
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
    var sRow =new Array();//存放入栈key在list中所在的行
    var top=-1;//栈顶
//处理数据
    while(pds.next()){
        var dt=new Array(); //存储一条记录
        //记录数据
        var space="    ";
        ++count;
        var rs0;
        rs0=(pds.value("key"))+space;
        for(var j=0;j<pdsColCount-2;j++){//留出“分部小计”
            rs0=rs0+pds.value(asList[j])+space;
            var data=pds.value(asList[j]);
            dt.push(data);
        }
        dt.push(0); //"分部小计合价"初始化0
        dt.push(0); //"分部小计暂估价"初始化0

        var type=pds.valueToInt("type");	//获取其类型
        var key= pds.value("key");
        var pkey= pds.value("pkey");
        switch(type){
        case 1://入栈根
            rs+=pushStack(skey,stype,sRow,sdata,sFlag,key,type,pds.getRowsCount(),dt);
            ++top;
            break;
        case 2:
            while(pds.value("pkey")!==skey[top]){ //当前数据非栈顶元素的子，需要插入小计并退栈
                rs+=addHJ(pds,skey,stype,sdata,sFlag,sRow,top);
                rs+=popStack(skey,stype,sRow,sdata,sFlag);
                --top;
            }//入栈分部
            rs+=pushStack(skey,stype,sRow,sdata,sFlag,key,type,pds.getRowsCount(),dt);
            ++top;
            break;
        case 3:
            if(pds.next()){
                if(pds.valueToInt("type")!==4){//非清单，不显示
                    pds.previous();//返回上一个记录
                    continue;   //不插入这条数据，直接下一条
                }
            }
            pds.previous();
            while(pds.value("pkey")!==skey[top]){ //当前数据非栈顶元素的子，需要插入小计并退栈
                rs+=addHJ(pds,skey,stype,sdata,sFlag,sRow,top);
                rs+=popStack(skey,stype,sRow,sdata,sFlag);
                --top;
            }
            if(pds.value("pkey")===skey[top]){
                sFlag[top]+=1;
                dt[0]=" ";
            }
            break;
        case 4:
            dt[0]=" ";
            break;
        }
        rs=rs+"\n"+pds.getRowsCount()+"|"+rs0+"\n";
        if(!(type===4)){ //定额不显示
            pds.insertData(dt); //向数据集添加一条记录
        }

    }
    //数据读取完成，判断栈中是否还有数据
    while(top>-1){//添加合计
        rs+=addHJ(pds,skey,stype,sdata,sFlag,sRow,top);
        rs+=popStack(skey,stype,sRow,sdata,sFlag);
        --top;
    }
    rs=rs+"共有 "+count+ " 条数据"+"\n";
    pds.close();
    pds.clearQuery();
    return rs;
}
//插入一条小计
function addHJ(pds,skey,stype,sdata,sFlag,sRow,top){
    var spopData=sdata[top];//获取栈顶数据
    var rs=" ";
     if(sFlag[top]>0){
         var row=sRow[top];
         var sz=spopData.length;
         rs=rs+pds.getRowsCount()+" 【插入一个小计： "+spopData[0];
         spopData[0]=" ";
         spopData[1]=" ";
         spopData[2]="【"+spopData[2]+"】小计";
         spopData[3]=" ";
         spopData[4]=" ";
         spopData[5]=" ";
         spopData[6]=" ";
         spopData[9]=spopData[7];
         spopData[10]=spopData[8];
         pds.insertData(spopData);//插入合计
         //清除分部行数据
         for(var col=1;col<sz;++col){
//             if(col!=7)
             pds.modifyData(row,col);
         }
     }else{     //删除不需要合计的分部数据
         pds.removeData(sRow[top]);
         rs="\n   【PusH 一行用于删除 | "+sRow[top];
     }
     return rs;
}

function pushStack(skey,stype,sRow,sdata,sFlag,key,type,row,dt){
    skey.push(key);
    stype.push(type);
    sdata.push(dt);
    sFlag.push(0);
    sRow.push(row);
    var rs="\n   【PusH |"+dt[0]+" | key="+key+" | row="+row
            +" | Flag="+0+" | type="+type+"\n";
    return rs;
}
function popStack(skey,stype,sRow,sdata,sFlag){
    var key	=	skey.pop();
    var type=	stype.pop();
    var row	=	sRow.pop();
    var dt	=	sdata.pop();
    var flag=	sFlag.pop();
    var rs="\n   【PoP |"+dt[0]+" | key="+key+" | row="+row
            +" | Flag="+flag+" | type="+type+"\n";
    return rs;
}
