#include<bits/stdc++.h>
using namespace std;
struct score
{
    int k;
    int s;
}p[5000];

bool compare(score a,score b)
{
    if(a.s!=b.s) return a.s>b.s;
    else return a.k<b.k;
}   

int main()
{
    int m,n;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        cin>>p[i].k>>p[i].s;
    }
    sort(p,p+n,compare);
    int renshu=floor(m*1.5);
    if (renshu > n) renshu = n;  // 防越界保护

    int scoreline=p[renshu-1].s;
    while(renshu<n&&p[renshu].s==scoreline)
    {
        renshu++;
    }

    cout<<scoreline<<" "<<renshu<<endl;

    for(int i=0;i<renshu;i++)
    {
        cout<<p[i].k<<" "<<p[i].s<<endl;
    }
    return 0;
}