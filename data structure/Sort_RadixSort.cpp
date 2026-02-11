//基数排序
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

//获取数字num在第d位上的数字
int getDigit(int num,int d)
{
    return (num/static_cast<int>(pow(10,d)))%10;
}

//计算最大数字所需位数
int maxbits(const vector<int>&arr)
{
    int max=*max_element(arr.begin(),arr.end());
    int res=0;
    while(max!=0)
    {
        res++;
        max/=10;
    }
    return res;
}

//基数排序函数
void radixSort(vector<int>&arr)
{
    if(arr.empty()) return;

    int maxDigit=maxbits(arr);//获取最大数字位数
    for(int d=0;d<maxDigit;d++)//从个位数上开始遍历
    {
        vector<int>count(10,0);//用于统计每一位数字(0-9)的出现次数
        vector<int>bucket(arr.size());//临时数组

        //统计每一位数字出现的次数
        for(int i=0;i<arr.size();i++)
        {
            int digit=getDigit(arr[i],d);//获取当前位的数字
            count[digit]++;//增加对应数字的计数
        }

        //更新计数数组 变成前项和形式
        for(int i=0;i<10;i++)
        {
            count[i]+=count[i-1];//累加计数
        }

        //根据每一位的数字将元素放在桶中 倒着遍历 左程云 堆结构课 第三节 最后一小时
        for(int i=arr.size()-1;i>=0;i--)
        {
            int digit=getDigit(arr[i],d);//获取当前位的数字
            bucket[count[digit]-1]=arr[i];//把元素放进临时数组
            count[digit]--;//更新计数器
        }
        arr=bucket;
    }
}

int main()
{  
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(arr);  // 执行基数排序
    for (int num : arr) 
    {
        cout << num << " ";
    }
    return 0;    
}