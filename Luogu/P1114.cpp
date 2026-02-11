//前缀和问题
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
int main()
{
    int n;
    cin>>n;

    vector<int>a(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    //先把女生的0变成-1
    //再加上求前缀和
    vector<int> s(n+1, 0);//0是直接在里面初始化了 不写也行
    for(int i=1;i<=n;i++)
    {
        int val = (a[i]==1 ? 1 : -1);
        s[i] = s[i-1] + val;
    }

    //哈希表
    unordered_map<int,int> first;
    int ans=0;
    
    first[0]=0;

    for(int i=1;i<=n;i++)
    {
        if(first.count(s[i]))//哈希表里面的查找判断函数
        {
            //出现过之前这种前缀和
            ans = max(ans,i-first[s[i]]);
        }
        else
        {
            //第一次出现 就记录一下这个前缀和的位置
            first[s[i]]=i;
        }
    }
    cout<<ans<<endl;
    return 0;
}

//成功AC 还是很有趣的 哈希表要熟练 前缀和这个东西好理解