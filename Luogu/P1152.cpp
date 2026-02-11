//欢乐的跳
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int>a(n);
    vector<int>jieguo(n-1);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<n-1;i++)
    {
        jieguo[i]=abs(a[i]-a[i+1]);
    }
    sort(jieguo.begin(),jieguo.end());//就是由小到大的 不用bool compare

    for(int i=0;i<n-1;i++)
    {
        if(jieguo[i]!=i+1)
        {
            cout<<"Not Jolly"<<endl;
            return 0;
        }
        
    }
    cout<<"Jolly"<<endl;
    return 0;
}