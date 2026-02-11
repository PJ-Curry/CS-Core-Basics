#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int x,y,z;
}p[50000];

bool compare(Node a,Node b)
{
    return a.z<b.z;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>p[i].x>>p[i].y>>p[i].z;
    }
    sort(p,p+n,compare);
    double sum=0;
    for(int i=1;i<n;i++)
    {
        double xx=p[i].x-p[i-1].x;
        double yy=p[i].y-p[i-1].y;
        double zz=p[i].z-p[i-1].z;
        sum+=sqrt(xx*xx+yy*yy+zz*zz);
    }
    cout<<fixed<<setprecision(3)<<sum<<endl;
    return 0;
}