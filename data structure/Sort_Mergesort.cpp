#include<iostream>//归并排序 T(N)=2T(N/2)+O(N) 时间复杂度 O(N*logN)
using namespace std;
void merge(int arr[],int L,int M,int R);
void process(int arr[],int L,int R)//递归了 满足master公式 T(N)=2T(N/2)
{
    if(L==R)
    {
        return;
    }
    int mid=L+((R-L)>>1);
    process(arr,L,mid);
    process(arr,mid+1,R);
    merge(arr,L,mid,R);
}
void merge(int arr[],int L,int M,int R)//O(N)
{
    int len=R-L+1;
    int *help=new int[len];
    int i=0;
    int p1=L;//指针
    int p2=M+1;//双指针
    while(p1<=M&&p2<=R)
    {
        help[i++]=arr[p1]<=arr[p2]?arr[p1++]:arr[p2++];
    }
    while(p1<=M)//处理剩余部分
    {
        help[i++]=arr[p1++];
    }
    while(p2<=R)
    {
         help[i++]=arr[p2++];
    }
    for(int j=0;j<len;j++)
    {
        arr[L+j]=help[j];//拷贝回去
    }
    delete[] help;
}
int main()
{

}