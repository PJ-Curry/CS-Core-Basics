#include<iostream>//轮流挨个交换 O(n^2)的时间复杂度
#include<algorithm>//swap函数
using namespace std;
void Bubllesort(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
}
int main()
{
    int data[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>data[i];
    }
    Bubllesort(data,n);
    for(int i=0;i<n;i++)
    {
        cout<<data[i]<<" ";
    }
    return 0;
}