#include<bits/stdc++.h>
using namespace std;
int main()
{
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int n;
        cin>>n;

        vector<int> pushSeq(n),popSeq(n);
        for(int i=0;i<n;i++)
        {
            cin>>pushSeq[i];
        }
        for(int i=0;i<n;i++)
        {
            cin>>popSeq[i];
        }
        
        stack<int>st;
        int j=0;//popSeq的指针
        for(int i=0;i<n;i++)
        {
            st.push(pushSeq[i]);
            while(!st.empty() && st.top()==popSeq[j])//边压边弹出 不是全压完再弹出
            {
                st.pop();
                j++;
            }
        }

        if(st.empty())
        {
            cout<<"Yes"<<endl;
        }
        else
        {
            cout<<"No"<<endl;
        }
    }
    return 0;
}
