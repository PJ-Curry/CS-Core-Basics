#include<iostream>//异或运算 相同结果为0 不相同为1
using namespace std;
//交换arr的i和j位置上的值
void swap(int arr[],int i,int j)
{
    if(i != j)
    { // 只有当i和j不相等时才进行交换 当i和j相等时候(地址一样) 最终的结果就是0
        arr[i] = arr[i] ^ arr[j]; // 异或操作
        arr[j] = arr[i] ^ arr[j]; // 再次异或得到原来的arr[i]
        arr[i] = arr[i] ^ arr[j]; // 最后一次异或得到原来的arr[j]
    }
}

//面试题 一个整形数组arr[]
//（1）只有一个数 出现了奇数次 其他的数都是偶数次 要求时间复杂度为O(N) 空间复杂度为O(1)
//（2）有两个数 出现了奇数次 其他的数都是偶数次
int findOddTimes(int arr[], int n)//Leetcode 136
{
    int res = 0;
    for (int i = 0; i < n; ++i) 
    {
        res ^= arr[i];//等价于res=res^arr[i];
    }
    return res;//只用了一个变量res来储存 所以空间复杂度是1
} 
//性质 自反性：a^a=0   同零性:0^a=a  
//交换律结合律(不用在乎顺序)用无进位相加来解释 这个运算都是二进制
//(2)题解 过数组两次
void findTwoOdd(int arr[], int n, int& out1, int& out2)
{
    int eor=0;
    for(int i=0;i<n;i++)
    {
        eor^arr[i];
    }
    //eor=a^b
    //eor!=0;
    //eor必然有一个位置上是1 然后接下来我们把那个1找到
    int rightOne=eor&(~eor+1);//与运算是 当两个数同时位1的时候加和才为1
    //~eor是按位取反 二补码表示下-x==~x+1 即~eor+1等价于-eor
    //也可以写成eor&(-eor)
    int onlyOne=0;//即eor' 找到那个位"1"之后接下来做的事儿
    for(int i=0;i<n;i++)
    {
        if((arr[i]&rightOne)==1)//如果arr[i]的rightOne位是1
        {
            onlyOne^=arr[i];//把这个数放到onlyOne中
        }
    }
    cout<<onlyOne<<" "<<(onlyOne^eor)<<endl;//   
} 
//常见位运算 &与 | ^异或 ~取反 <<左移 >>右移