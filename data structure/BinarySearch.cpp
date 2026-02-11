#include<iostream>//递归 可以利用master公式T(N)=a*T(N/b)+O(N^d) 前提是满足子问题等规模
#include<algorithm>
using namespace std;
int process(int arr[],int L,int R);//递归函数声明 不写也行
int getMax(int arr[],int n)
{
    return process(arr,0,n-1);
}
int process(int arr[],int L,int R)
{
    if(L==R)
    {
        return arr[L];
    }
    int mid=L+((R-L)>>1);
    int leftMax=process(arr,L,mid);
    int rightMax=process(arr,mid+1,R);
    return max(leftMax,rightMax);
}


int binarySearch(int *a,int n,int target)
{
    int left=0,right=n-1;
    while(left<=right)
    {
        int mid=left+((right-left)>>1);
        if(a[mid]==target)
        {
            return mid;
        }
        else if(a[mid]>target)
        {
            right=mid-1;
        }
        else
        {
            left=mid+1;
        }
    }
    return -1;//根本没进入循环的话 就是没有 返回-1
}


//找到有序数组中>=num的最左位置
int mostLeftNoLessNumIndex(int arr[],int n,int num)//num是题目里要我们找到的数字
{
    int L=0;
    int R=n-1;
    int ans=-1;
    while(L<=R)
    {
        int mid=L+((R-L)>>1);
        if(arr[mid]>num)
        {
            ans=mid;
            R=mid-1;
        }
        else
        {
            L=mid+1;      
        }
    }
    return ans;//最后要返回我们找到的数字
}
//for test对数器
int test(int arr[],int n,int value)//遍历的方法
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]>=value)
        {
            return i;
        }
    }
    return -1;
}


//局部最小值问题 数组无序 任意两个相邻的位置不相等 定义局部最小
//[0]<[1] return 0
//[N-2]>[N-1] return N-1
//左<[i]>右  三个条件   也可以二分   
#include<iostream>
#include<vector>
using namespace std;
int oneMinIndex(const vector<int>&arr)
{
    int n=arr.size();
    if(n==0)
    {
        return -1;
    }
    if(n==1)
    {
        return 0;
    }
    if(arr[0]<arr[1])
    {
        return 0;
    }
    if(arr[n-1]<arr[n-2])
    {
        return n-1;
    }
    int L=0;
    int R=n-1;
    int ans=-1;
    while(L<R-1)//保证一下数组有三个数//while(L<=R)就是范围会越界 比较严密
    {
        int mid=L+((R-L)>>1);
        if(arr[mid]<arr[mid-1]&&arr[mid]<arr[mid+1])
        {
            ans=mid;
            break;
        }
        if(arr[mid]>arr[mid-1])//直接放弃右边找左边
        {
            R=mid-1;
            continue;
        }
        if(arr[mid]>arr[mid]+1)
        {
            L=mid+1;
            continue;
        }
    }
    return ans;
}
//二分 不是一定要有序