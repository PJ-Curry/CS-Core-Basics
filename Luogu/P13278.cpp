#include<iostream>
using namespace std;
int main()
{
    const int N=1e6+5;
    int n,m,q;//n是轮数 m血量 q道具数量
    int a[N],sum,k,s,d;//数组是输入的数据 k是攻击B的回合数 s是A对B的总伤害 d是A的死亡时间
    cin>>n>>m>>q;
    for(int i=0;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        if(a[i]>0) s+=a[i],k++;
        if(a[i]<0) sum+=-a[i];
        if(sum>=m){
            d=i;
            break;
        }
    }
    if(!d) d=n+1;//未死亡
    while(q--){
        int x;cin>>x;
        int aa=x*k+s;
        if(aa>=m) cout<<"Yes\n";
        else if(d==n+1) cout<<"Tie\n";
        else cout<<"No\n";
    }
    return 0;
}