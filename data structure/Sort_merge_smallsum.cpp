#include<iostream>//求小和也是归并排序！区别就是右侧组等于左侧组的时候 先把右侧组放到help里
using namespace std;
int merge(int arr[],int l,int m,int r);
int process(int arr[],int l,int r)//既要排好序 也要求小和
{
    if(l==r)
    {
        return 0;
    }
    int mid=l+((r-l)>>1);
    return process(arr,l,mid)+process(arr,mid+1,r)+merge(arr,l,mid,r);
} 
int merge(int arr[],int l,int m,int r)
{
    int len=r-l+1;
    int *help=new int[len];
    int i=0;
    int p1=l;
    int p2=m+1;
    int res=0;
    while(p1<=m&&p2<=r)
    {
        res+=arr[p1]<arr[p2]?(r-p2+1)*arr[p1]:0;
        help[i++]=arr[p1]<arr[p2]?arr[p1++]:arr[p2++];
    }
    while(p1<=m)
    {
        help[i++]=arr[p1++];
    }
    while(p2<=r)
    {
        help[i++]=arr[p2++];
    }
    for(int j=0;j<len;j++)
    {
        arr[l+j]=help[j];
    }
    delete[]help;
    return res;
}