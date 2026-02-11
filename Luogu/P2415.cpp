//洛谷P2415集合求和
#include<iostream>//这个题在编译器上过了 但还是有些瑕疵的
#include<cmath>
using namespace std;
long long s[32];
int main()
{
    long long sum=0,cnt=0;
    while(cin>>s[cnt])
    {
        sum+=s[cnt];
        cnt++;
    }
    long long ans=sum*pow(2,cnt-1);
    cout<<ans;
    return 0;
}