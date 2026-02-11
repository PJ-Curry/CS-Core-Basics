#include<bits/stdc++.h>
using namespace std;
struct xx
{
    int yw;
    int sx;
    int yy;
    int zf;
    int bh;
}a[305];//这种写法 自动创建了一个如a[i].yw a[i].sx的数组
int n;
bool compare(xx x,xx y)
{
    if(x.zf!=y.zf)
    {
        return x.zf>y.zf;
    }
    else
        if(x.yw!=y.yw)
            return x.yw>y.yw;
        else
            return x.bh<y.bh;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].yw>>a[i].sx>>a[i].yy;
        a[i].bh=i;
        a[i].zf=a[i].yw+a[i].sx+a[i].yy;
    }
    sort(a+1,a+n+1,compare);
    for(int i=1;i<=5;i++)
    {
        cout<<a[i].bh<<" "<<a[i].zf<<endl;
    }
    return 0;
}