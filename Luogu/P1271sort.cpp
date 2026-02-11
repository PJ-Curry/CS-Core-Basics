//常规方法就是排序 一个桶里 大家往里面投票 这个啥排序都能写
//书上给的做法就是 自己抱着自己的桶 然后按编号看箱子里有几张票 计数排序
#include<iostream>
using namespace std;
int main()
{
    int n;
    int m;
    int a[1010]={0};
    int tmp=0;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>tmp;
        a[tmp]++;
    }
    for(int i=1;i<=n;i++)//这里变换成了箱子 箱子的个数就是小于n
    {
        for(int j=0;j<a[i];j++)
        {
            cout<<i<<" ";
        }
    }//这个逻辑太清晰了 比往上ai写的都好
    return 0;
}
   /*
    for(int i=0;i<m;i++)cin>>a,++b[a]; //记录票出现的次数
	for(int i=0;i<1000;i++)while(b[i]--)cout<<i<<" "; //根据票出现的次数输出
    */