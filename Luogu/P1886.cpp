/*
单调队列：以求窗口最小值为例
只踢掉队尾比新来的大的数字 不踢掉前面更小的值 保证队首元素始终是当前窗口的最小值
要用deque deque可以同时操作队首和队尾 都可以进行pop或者push 
pop队列最前面的数字（因为窗口要滑动）push或pop队尾 push因为滑动 pop因为比较大小
*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    deque<int>qMin,qMax;//分别维护最小值最大值的下标
    for(int i=0;i<k;i++)
    {
        
    }

}