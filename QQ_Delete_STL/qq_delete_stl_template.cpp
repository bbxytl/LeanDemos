
#include <iostream>
#include <utility>
#include <set>
#include <vector>
typedef long long dlong;

//删除QQ为奇数的项
template <typename T>
void qq_delete_stl_template(T &);
//输出容器中所有元素
template <typename T>
void printElem(T &);

template <typename T>
void qq_delete_stl_template(T &t){
    typename T::iterator it=t.begin(); //typename用来说明T::iterator是一个类型，
                                        //否则iterator会被认为是T中的一个成员变量
    while(it!=t.end()){
        if((*it)&1){ //奇数
            it=t.erase(it); //删除迭代起指向的内容，并返回删除后的下一项内容
        }else{
            ++it;
        }
    }
}

template <typename T>
void printElem(T &t){
    typename T::iterator it=t.begin();
    while(it!=t.end()){
        cout<<*(it)<<endl;
        ++it;
    }
}

void main(){
    set<dlong>      s;  
    vector<dlong>   v;  
    deque<dlong>    d;  
    list<dlong>     l;  
    dlong qqNum=0;
    for(unsigned int i=0;i<100000;++i){ //一亿条QQ号(会死掉，这里使用10万条)
        qqNum=i;
        s.insert(qqNum);
        v.push_back(qqNum);
        d.push_back(qqNum);
        l.push_back(qqNum);
    }
    cout<<"s.size()="<<s.size()<<endl;
    cout<<"v.size()="<<v.size()<<endl;
    cout<<"d.size()="<<d.size()<<endl;
    cout<<"l.size()="<<l.size()<<endl;
    cout<<"----------------------------"<<endl;

//    printElem(s);
    qq_delete_stl_template(s);
    cout<<"s.size()="<<s.size()<<endl;
//    printElem(s);

//    printElem(v);
     qq_delete_stl_template(v);
    cout<<"v.size()="<<v.size()<<endl;
//    printElem(v);

//    printElem(d);
    qq_delete_stl_template(d);
    cout<<"d.size()="<<d.size()<<endl;
//    printElem(d);

//    printElem(l);
    qq_delete_stl_template(l);
    cout<<"l.size()="<<l.size()<<endl;
//    printElem(l);
    cout<<"----------------------------"<<endl;
}


void qq_delete_stl_vector(std::vector<dlong> &v){
    size_t Sz;
    dlong tmp;
    for (size_t i = 0; i < v.size(); ++i)
    {
        Sz = v.size();
        if (v[Sz-1] & 1) // 如果最后一个QQ号为奇数
        {
            v.pop_back();
            continue;
        }
        if (v[i] & 1)
        {
            tmp = v[i];
            v[i] = v[Sz-1];
            v[Sz-1] = tmp;
            v.pop_back();
        }
    }
        v.shrink_to_fit();
}

