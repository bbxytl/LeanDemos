
function GetDataSource()
{
    object.clear();
    var pds=object.creatDataSetObject();    //创建一个数据源
    var index=pds.getObjectId();        //获取数据源对应的id
    //var index=object.getDSObjectID(pds); //另一种获取方式！
    var rs=setDataSet(pds);     // 给pds设置绑定数据源
    object.setTemplate("工程量清单项目预算表--ok-14121509-1.xml");
    object.setUseDataSetID(index);
    return rs+"\n"+object.getTemplate();
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
                         "合价",
                         "分部合计"
                         )
    var con="datas.db";
    var sqls;  //字段别名对应 asList 里的顺序！
    {
        var t=0;
        sqls="select "+
                    " NUM          as  '"+asList[t++]+
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
    var conName="connectName2sdrfdx";
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
//设置数据---开始
    var skey =new Array();//存放入栈key
    var stype=new Array();//存放入栈type
    var sdata=new Array();//存放入栈数据
    var sFlag=new Array();//存放入栈数据是否需要合计
    var sRow =new Array();//存放入栈key在list中所在的行
    var sNoUsedRow=new Array();//存放最后要删除的行
    var top=-1;//栈顶
//处理数据
    while(pds.next()){
        var dt=new Array(); //存储一条记录
        //记录数据
        for(var j=0;j<pdsColCount-1;j++){
            var data=pds.value(asList[j]);
            dt.push(data);
        }
        dt.push(0); //"分部合计"
        var type=pds.valueToInt("type");	//获取其类型
        var key= pds.value("key");
        var pkey= pds.value("pkey");
        switch(type){
        case 1://入栈根
            pushStack(skey,stype,sRow,sdata,sFlag,key,type,pds.getRowsCount(),dt);
            ++top;
            break;
        case 2:
            if(pds.value("pkey")!==skey[top]){ //当前数据非栈顶元素的子，需要插入合计并退栈
                addHJ(pds,skey,stype,sdata,sFlag,sRow,sNoUsedRow,top);
                --top;
            }//入栈分部
            pushStack(skey,stype,sRow,sdata,sFlag,key,type,pds.getRowsCount(),dt);
            ++top;
            break;
        case 3:
            if(pds.value("pkey")!==skey[top]){ //当前数据非栈顶元素的子，需要插入合计并退栈
                addHJ(pds,skey,stype,sdata,sFlag,sRow,sNoUsedRow,top);
                --top;
            }else{
                if(sFlag[top]!==1)sFlag[top]=1;
                dt[0]=" ";
            }
            break;
        case 4:
            dt[0]=" ";
            break;
        }
        pds.insertData(dt); //向数据集添加一条记录
    }
    //数据读取完成，判断栈中是否还有数据
    while(top>-1){//添加合计
        addHJ(pds,skey,stype,sdata,sFlag,sRow,sNoUsedRow,top);
        --top;
    }
    removeNoUseRow(pds,sNoUsedRow);//清除无用行
    pds.close();
    return conName;
}
function addHJ(pds,skey,stype,sdata,sFlag,sRow,sNoUsedRow,top){
    var spopData=sdata[top];//获取栈顶数据
     if(sFlag[top]===1){
         var row=sRow[top];
         var sz=pds.getColsCount();
         spopData[0]=" ";
         spopData[2]="合计";
         spopData[sz-1]=spopData[sz-2];
         pds.insertData(spopData);//插入合计
         //清除分部行数据
         for(var col=1;col<sz-1;++col){
             pds.modifyData(row,col);
         }
     }else{     //删除不需要合计的分部数据
         sNoUsedRow.push(sRow[top]);
     }
    popStack(skey,stype,sRow,sdata,sFlag);
}

function pushStack(skey,stype,sRow,sdata,sFlag,key,type,row,dt){
    skey.push(key);
    stype.push(type);
    sdata.push(dt);
    sFlag.push(0);
    sRow.push(row);
}
function popStack(skey,stype,sRow,sdata,sFlag){
    skey.pop();
    stype.pop();
    sRow.pop();
    sdata.pop();
    sFlag.pop();
}

function removeNoUseRow(pds,noUse){
    while(noUse.length){
        var pos=noUse.pop();
        pds.removeData(pos);
    }
}

