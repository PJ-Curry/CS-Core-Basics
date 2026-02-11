#include<iostream>
using namespace std;
int main()
{
    int n,k1,k2,ans=-1;
    cin>>n>>k1>>k2;
    for(int i=1,a,x,y;i<=n;i++)
    {
        cin>>a>>x>>y;
        if(x&&y) continue;//x&&y意识是x和y都是真(非零)
        if(x==1) a-=k1;
        if(y==1) a-=k2;
        if(a<0) continue;
        ans=max(ans,a);//精髓是把它放在循环中直接比 就可以和所有的ans作比较了
    }
    cout<<ans;
    return 0;
}