#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
int main()
{
    int n,m;
    int arr[101][21];
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>arr[i][j];
        }
    }
    vector<int>sum;
    for(int i=0;i<n;i++)
    {
        int s1=0;
        int max=arr[i][0];
        int min=arr[i][0];
        for(int j=0;j<m;j++)
        {
            int v=arr[i][j];
            s1+=v;
            if(v>max)
            {
                max=v;
            }
            if(v<min)
            {
                min=v;
            }
        }
        int s2=(m>=2?s1-min-max:s1);
        sum.push_back(s2);
    }
    double max2=sum[0];
    for(int i=1;i<n;i++)
    {
        if(sum[i]>max2)
        {
            max2=sum[i];
        }
    }
    double avg=max2/(m-2);
    cout<<fixed<<setprecision(2)<<avg<<endl;
    return 0;
}