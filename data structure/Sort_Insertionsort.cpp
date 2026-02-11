#include<iostream>//插入排序
#include<algorithm>
using namespace std;
void Insertionsort(int a[],int n)
{
    for(int i=1;i<n;i++)//让他在0~i范围上做到有序 不用从1开始因为0~0已经排好序了
    {
        for(int j=i-1;j>=0 && a[j]>a[j+1];j--)//j+1位置就是第i位上的数字
        {
            swap(a[j], a[j + 1]); // 交换相邻的元素
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
    Insertionsort(data,n);
    for(int i=0;i<n;i++)
    {
        cout<<data[i]<<" ";
    }
    return 0;
}