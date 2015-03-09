[**GitHub博客**](https://github.com/bbxytl/bbxytl.github.com/blog) / [学习Demo](https://github.com/bbxytl/Lean_Demos) /
====

##[**使用位操作符求素数**](https://github.com/bbxytl/Lean_Demos/tree/master/GetPrimes)

先放代码：
```cpp
#include <iostream>
using namespace std;

void getPrime_1()
{
    const int MAXN = 100;
    bool flag[MAXN];
    int primes[MAXN / 3 + 1], pi=0;
    primes[pi++]=2; //2 是一个素数，先记录下来
    int i, j;
    for(i=0;i<MAXN;++i)flag[i]=false;//全部置假，没访问一个，相应位置真
    for (i = 3; i < MAXN; i+=2){//大于2的偶数一定不是素数，所以只要判断奇数即可
        if (!flag[i])//如果是素数
        {
            primes[pi++] = i;
            for (j = i; j < MAXN; j += i)//i的倍数一定都不是素数
                flag[j] = true;
        }
    }
    for(i=0;i<pi;++i)
        cout<<primes[i]<<" ";
    cout<<endl;
}
```
这里使用了素数表，每一个**bool**型占用**1**个字节，共**8**位二进制位。而且这里除了多用了很多的无用**bool**变量在**flag**数组里，可以看到，我们使用的**flag**数组只用到**2**号位之后的所有奇数位。因此，这里可以进行压缩改进一下：
1. 将**flag**数组减少一半
2. 使用**位操作符**使空间占用减少为原来的八分之一

这里使用到对指定位置**置1**的操作：对于一个整数**X**可以通过将**1**左移**n**位后，与**X**进行**或**操作，使**X**的第**n**位**置1**。
```
int X=0;
int n=10;
X |= 1<< n; // 将 X 的第 n 位置 1
```

所以根据上面两条，优化后的代码如下：
```
void getPrime_2()
{    
    const int MAXN = 200;
    const int BitN=(MAXN/2)/32+1;//   
    int flag[BitN];
    int primes[MAXN / 3 + 1], pi=0;
    primes[pi++]=2;  //2 是一个素数，先记录下来
    int i, j; 
    for(i=0;i<BitN;++i)flag[i]=0;//全置0，每访问过一个，相应位置1
    for (i = 3; i < MAXN; i+=2){ //大于2的偶数一定不是素数，所以只要判断奇数即可
        if (!((flag[(i/2) / 32] >> ((i/2) % 32)) & 1))
        {
            primes[pi++] = i;
            //i的倍数一定都不是素数，其中，j加上一个i后为偶数，上一级已经不考虑了，所以还要加上一个i
            for (j = i; j < MAXN; j =j+i+i)
                flag[(j/2) / 32] |= (1 << ((j/2) % 32));
        }
    }
    for(i=0;i<pi;++i)
        cout<<primes[i]<<" ";
    cout<<endl;
}
```
首先，根据最大数，判断需要32的整型多少个：
```
BitN=(MAXN/2)/32+1;
```
` MAXN/2 `去除了所有偶数位，` (MAXN/2)/32+1 `代表需要多少32位的整型。
其次，所有求位的操作，都要除以2以去除偶数位的影响。
同时：
```
for (j = i; j < MAXN; j =j+i+i)
                flag[(j/2) / 32] |= (1 << ((j/2) % 32));
```
其中的 `j=j+i+i;` 是因为 **j** 和 **i** 本身都是一个奇数，相加后为偶数，不考虑，所以还要加上一个 **i** 。
通过这种方式，缩小了占用空间。
[**代码文件**](https://github.com/bbxytl/Lean_Demos/blob/master/GetPrimes/getPrimes.cpp)

####注：
当 `MAXN=200 ` 时，实际的素数只有**45**个，但**primes**的大小却是**66**，那么这里怎么能更进一步的优化呢？


