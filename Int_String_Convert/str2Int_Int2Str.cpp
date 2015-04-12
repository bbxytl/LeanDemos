
#include "cpp_head.h"

char * int2StrA(int);
char * int2StrB(int);
char * int2StrC(int);

enum   Status{kInvalid=0,kValid};
int    g_status=kValid;    //合法输入
int    str2IntA(const char*);
int    str2IntB(const char*);


void main(){
    int number=-172342480;
    char * str=int2StrB(number);
    printCharPtr(str);
    number=0;
    delete str;
    str="-2334580";
    number=str2IntA(str);
    if(g_status==kInvalid)
        cout<<"非法输入！"<<endl;
    else cout<<number<<endl;
}

char * int2StrA(int nb){
    char * str= new char[12];//整型最长11位
    str[11]='\0';
    unsigned int nindex=0;
    if(nb<0){       //负数时的情况
        str[0]='-';
        nb*=-1;     //转换为正数
        ++nindex;   //第0位记录了符号'-',所以下移一位开始记录数字
                    //如果是正数和0的情况，直接从第0位开始记录数字
    }else if(0==nb){    //0时的情况
        str[0]='0';
        str[1]='\0';
        return str;
    }
    int tmpNum,len;
    while(nb!=0){
        len=1;
        tmpNum=nb;
        while(tmpNum>=10){
            len*=10;        //记录最高位的位度
            tmpNum/=10;     //循环累除10求最高位数字
        }
        str[nindex++]=tmpNum+'0';
        nb=nb-tmpNum*len;           //nb 减去最高位
        if(nb==0){  //判断最后一位是否为 0 的情况
            str[nindex++]='0';
            break;
        }
    }
    str[nindex]='\0'; //添加结束符号
    return str;
}

char * int2StrB(int nb){
    char * str= new char[12];//整型最长带上符号共11位
    str[11]='\0';
    unsigned int nindex=0;
    if(nb<0){
        str[0]='-';
        nb*=-1;     //转换为正数
        nindex=1;
    }else if(0==nb){
        str[0]='0';
        str[1]='\0';
        return str;
    }
    unsigned int len=0; //记录nb的位数
    int tmpNb=nb;
    while(0!=tmpNb){
        ++len;
        tmpNb/=10;
    }
    if(nindex==0)--len; //在str中定位最后一位数字应该在的位置
    str[len+1]='\0';    //设置结束符号
    while(0!=nb){
        str[len--]=nb%10+'0';
        nb/=10;
    }
    return str;
}

char * int2StrC(int nb){
    char * str= new char[12];//整型最长带上符号共11位
    str[11]='\0';
    unsigned int nindex=0;
    if(nb<0){
        str[0]='-';
        nb*=-1;     //转换为正数
        nindex=1;
    }else if(0==nb){
        str[0]='0';
        str[1]='\0';
        return str;
    }
    unsigned int nstar=nindex; //记录要逆序的初始位置
    while(0!=nb){
        str[nindex++]=nb%10+'0';
        nb/=10;
    }
    str[nindex]='\0';
    //字符串逆序
    --nindex;
    while(nstar<nindex){
        char tmp=str[nstar];
        str[nstar]=str[nindex];
        str[nindex]=tmp;
        ++nstar;
        --nindex;
    }
    return str;
}

#include <sstream>

typedef long long dlong;
int    str2IntA(const char* str){
    g_status=kInvalid;
    if(str==nullptr || *str=='\0')return 0; //指针不为空，字符串不为空
    if(*str!='+' && *str!='-' && (*str<'0' && *str>'9'))return 0;
    if(*str=='+' || *str=='-'){     //只有 "+" 和 "-" 或 '+'/'-'后跟的不是数字
        if(*(str+1)=='\0' || (*(str+1)<'0' && *(str+1)>'9'))return 0;
    }
    stringstream stream(str);
    dlong num=INT_MAX+10; //大于整型最大数，判断溢出
    stream>>num;
    if(num>INT_MAX || num<INT_MIN)return 0;
    g_status=kValid;
    return (int)num;
}

int    str2IntB(const char* str){
    g_status=kInvalid;
    if(str==nullptr || *str=='\0')return 0; //指针不为空，字符串不为空
    char const* pstr=str;
    int flag=1;                 //判断正负数，默认为正数
    dlong num=0;            //防溢出
    if(*pstr=='-')flag=-1;      //负数
    else if(*pstr=='+') flag=1; //正数
    else if(*pstr<'0' && *pstr>'9')return 0;//非法输入
    else num=(*pstr-'0')*flag;  //上来就是数字，为正数
    ++pstr;
    if(*pstr!='\0'){        //防止字符串为"+"，或 "-"的情况
        while(*pstr!='\0'){ //循环求数字
            if(*pstr>='0' && *pstr<='9'){
                num=num*10+(*pstr-'0')*flag;
                if((flag==1 && num>INT_MAX) ||
                   (flag==-1 && num<INT_MIN))   //防溢出
                    return 0;//溢出
                ++pstr;
            }else return 0; //非法输入
        }
        if(*pstr=='\0') g_status=kValid;    //直达字符串末尾，说明输入合法
    }
    return (int)num;    //将 dlong 型强制转换为 int
}


