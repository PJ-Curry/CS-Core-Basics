//进制转换问题 R为负基数
//可以说 进制转换没有问题了
#include<iostream>
#include<string>
using namespace std;
string fanhui(long long n,long long R)
{
    if(n==0) return 0;
    string digits="0123456789ABCDEFGHIJ";//最多支持到19
    long long base=abs(R);
    string res="";//空字符

    while(n!=0)
    {
        long long r = n % R;//余数
        n /= R;
        if(r<0)
        {
            r += base;//余数变成负数了 就要变成其绝对值 正数
            n += 1;//就要给商加上一个数字
        }
        res = digits[r] + res;
    }
    return res;
}
int main()
{
    long long n,R;
    cin>>n>>R;
    cout<<n<<"="<<fanhui(n,R)<<"(base"<<R<<")";
    return 0;
}