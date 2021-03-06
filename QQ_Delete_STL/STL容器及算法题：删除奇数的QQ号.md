[**GitHubBlog**](https://github.com/bbxytl/bbxytl.github.com/tree/master/blog#home--githubblog) /
=====
#[**STL容器及算法题：删除奇数的QQ号**](https://github.com/bbxytl/Lean_Demos/tree/master/QQ_Delete_STL/STL容器及算法题：删除奇数的QQ号.md#githubblog-)
最近思考到这样一个题目：在STL的set和vector容器里存储了1亿个QQ号，编写函数删除奇数QQ号。
##1. STL容器简介
首先了解一下 set 和 vector 以及其他类似的 STL 容器：
###实现描述：
![](./image-001.png)

###时间和空间复杂度：
![](./image-002.png)

###其他容器适配器
这些容器几乎是由其他容器实现的容器，只是对存取元素方面进行了部分的限制。

容器 | 描述
--|--
stack                     |栈，后进先出的队列。
queue                   |队列，先进先出。
priority_queue     |优先队列，一个队列，其中元素的次序是由作用于所存储值对上的某种谓词决定的，拥有高优先级的元素会先被出队。

##2. 算法解析
第一个思路就是使用**erase**函数一个个去删，（不知道有没有什么更好的方法请在评论里指点一下，谢谢）这里，set和vector的存储方式是不一样的。但是它们都提供了一个删除元素的接口**erase**：   
```cpp
// set
iterator    erase(iterator it);
iterator    erase(iterator first, iterator last);
size_type   erase( const Key& key);
```
- 第一个成员函数：删除 set 中由迭代器 it 指向的元素；
- 第二个成员函数：删除 set 中区间为 [first , last )中的所有元素；
- 第一和第二个成员函数都返回一个迭代器，指向紧接着被删除元素的下一个元素，如果没有这样的元素，则迭代器指向 end()。
- 第三个成员函数：删除 set 中区间为 [lower_bound(key) , upper_bound(key) )中的具有给定排序键key的所有元素，返回删除元素的个数

```cpp
// vector , list ,  deque
iterator    erase(iterator it);
iterator    erase(iterator first, iterator last);
```
- 第一个成员函数：删除 vector/list/deque 中由迭代器 it 指向的元素；
- 第二个成员函数：删除 vector/list/deque 中区间为 [first , last )中的所有元素；
- 第一和第二个成员函数都返回一个迭代器，指向紧接着被删除元素的下一个元素，如果没有这样的元素，则迭代器指向 end()。
- vector时，删除 N 个元素将导致调用 N 次析构函数以及从删除点至序列末端的每个元素都被赋值一次。由于不需要进行存储空间的重新分配，所以只有从指向第一个被删除元素到序列末端这个区域的迭代器以及引用才会失效。
- list时，删除N个元素将调用N次析构函数。由于没有进行任何重新分配发生，只有指向被删除对象的迭代器和引用才会变为无效。
- deque时，删除N个元素将导致N次调用析构函数以及从删除点至序列较近的末端的每个元素都被赋值一次。在序列的两端删除一个元素仅使得原先指向被删除元素的迭代器和引用变得无效，否则，删除一个元素将导致所有的迭代器和引用都变的无效。

了解了这个以后，能发现，算法题中的说存储在set和vector中，其实其内部存储是不一样的，删除的实现原理也是不同的。但都可以用同一个接口**erase()**去实现！及时这时候添加说还存储在list和deque中，也是可以使用的。我们可以写两个函数去实现这个功能，但由于在两个容器中，而调用的接口又都是一样的，所以自然而然想到可以使用模板函数！这是其一。

第二，题目中说是QQ号，众所周知，QQ目前已经多达11位了，以后还会更长，所以将QQ号设为整型肯定是不合适的了，所以这里需要使用**long long** 。同时，遍历容器时，肯定是要使用迭代器来进行遍历的，这样能保证速度。

第三，题目中说一亿个QQ号，目前还不知道这里藏着什么坑，感觉是有的，我写的代码反正是死掉了，一亿条，添加和删除的循环都搞死了。还请大神帮忙分析分析！

所以基于以上分析，写出以下代码：
```cpp
#include <utility>
#include <set>
#include <vector>

typedef long long dlong;

template <typename T>
void qq_delete_stl_template(T &t){
    typename T::iterator it=t.begin(); //typename用来说明T::iterator是一个类型，
                                      //否则iterator会被认为是T中的一个成员变量
    while(it!=t.end()){     //每次删除后都会导致t.end()指向的都是不同的位置
        if((*it)&1){            //奇数
            it=t.erase(it); //删除迭代起指向的内容，并返回删除后的下一项内容
        }else{
            ++it;
        }
    }
}

//调用时应该是：
set<dlong>  s;  //假设s里存有1亿个QQ号
qq_delete_stl_template(s);
vector<dlong>  v;  //假设v里存有1亿个QQ号
qq_delete_stl_template(v);
```
分析的比较浅显，希望大神指教！

[**完整测试源码**](./qq_delete_stl_template.cpp)

##注：
在vector的删除中，当使用erase删除时，每一次都会移动删除元素后面的元素，当数据量有一亿这样多时，效率会大打折扣。因此在使用vector时，应尽量避免使用erase来删除元素。由于在vector的末尾删除元素并不会移动元素，所以效率会很快，即使用pop_back来删除元素。那么上面对应的删除vector里的奇数QQ可以使用下面的函数来实现：
```cpp
#include <vector>

typedef long long dlong;

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
```

##**附录**
- **[GitHub-Blog](http://bbxytl.github.io/)**
- **关注微信订阅号**：     
    ![关注微信订阅号](https://github.com/bbxytl/bbxytl.github.com/blob/master/blog/pages/images/qrcodes/qrcode_100.jpg)



