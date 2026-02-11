#include<iostream>//选择排序算法 O(n^2)的时间复杂度
#include<algorithm>//swap函数
using namespace std;
void Selectionsort(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int minIndex=i;//minIndex是下标 不是值
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[minIndex]) 
            {
                minIndex=j;
            }
        }
        if(minIndex!=i)
        {
            swap(a[i],a[minIndex]);//要对实在的元素进行交换 而不是下标
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
    Selectionsort(data,n);
    for(int i=0;i<n;i++)
    {
        cout<<data[i]<<" ";
    }
    return 0;
}