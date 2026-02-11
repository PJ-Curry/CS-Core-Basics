#include<iostream>
using namespace std;
int main()
{
    int jishu=0;
    int n;
    cin>>n;
    int *arr=new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
                jishu++;
            }
        }
    }
    cout<<jishu;
    return 0;
}