#include<bits/stdc++.h>
using namespace std;
int main()
{
    int m,n;
    cin>>m>>n;
    int number=0;

    queue<int>que;
    unordered_set<int> seen;//哈希表(用来判重)

    vector<int>arr(n);

    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    for(int x:arr)
    {
        if(seen.count(x)) continue;
        if(que.size()==m)
        {
            int old=que.front();
            que.pop();
            seen.erase(old);//在哈希表中也要清除的
        }
        que.push(x);
        seen.insert(x);
        number++;
    }

    cout<<number<<endl;
    return 0;
}