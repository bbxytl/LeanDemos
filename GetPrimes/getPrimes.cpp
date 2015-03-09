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

void getPrime_2()
{    
    const int MAXN = 100;
    const int BitN=(MAXN/2)/32+1;//
    int i, j;    
    int flag[BitN];
    int primes[MAXN / 3 + 1], pi;
    pi = 0;
    primes[pi++]=2;
    for(i=0;i<BitN;++i)flag[i]=0;//为素数置1，不为置0
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

#include <bitset>
void getPrime_3(){
    const int MAXN = 100;
    bitset<(MAXN/2+1)> flag(0);
    int primes[MAXN / 3 + 1], pi=0;
    primes[pi++]=2;
    int i, j;
    for (i = 3; i < MAXN; i+=2){ //大于2的偶数一定不是素数，所以只要判断奇数即可
        if (!(flag.test(i/2)))//如果对应位为false
        {
            primes[pi++] = i;
            //i的倍数一定都不是素数，其中，j加上一个i后为偶数，上一级已经不考虑了，所以还要加上一个i
            for (j = i; j < MAXN; j =j+i+i)
                flag.set(j/2);//设置对应位为true
        }
    }
    for(i=0;i<pi;++i)
        cout<<primes[i]<<" ";
    cout<<endl;
}

int main()
{
    int b[2]={0};
    int i=0;
    cout<<sizeof(i)<<endl;
    for(i=0;i<40;i+=3){
        int dn=i/32,mod=i%32;
        b[dn] |= (1 << (mod));
    }
    for(i=0;i<40;i++){
        ((b[i / 32] >> (i % 32)) & 1) ?
                    putchar('1') :
                    putchar('0');
    }

    cout <<endl<< "getPrime_1" << endl;
    getPrime_1();
    cout <<endl<< "getPrime_2" << endl;
    getPrime_2();
    cout <<endl<< "getPrime_3" << endl;
    getPrime_3();
    return 0;
}

