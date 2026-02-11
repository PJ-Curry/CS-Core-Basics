#include<bits/stdc++.h>
using namespace std;

vector<int> k_arr,d_arr,m_arr,f_arr;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K,D,M,F;
    cin>>K>>D>>M>>F;
    k_arr.resize(K); for(int i=0; i<K; i++) cin >> k_arr[i];
    d_arr.resize(D); for(int i=0; i<D; i++) cin >> d_arr[i];
    m_arr.resize(M); for(int i=0; i<M; i++) cin >> m_arr[i];
    f_arr.resize(F); for(int i=0; i<F; i++) cin >> f_arr[i];    

    sort(k_arr.rbegin(), k_arr.rend());
    sort(d_arr.rbegin(), d_arr.rend());
    sort(m_arr.rbegin(), m_arr.rend());
    sort(f_arr.rbegin(), f_arr.rend());    

    int Q;
    cin>>Q;

    int p_k=0,p_d=0,p_m=0,p_f=0;

    while(Q--)
    {
        int A,B,C;
        cin>>A>>B>>C;

        double sum=0;

        sum+=k_arr[p_k];
        p_k++;

        for(int i=0;i<A;i++)
        {
            sum+=d_arr[p_d];
            p_d++;
        }

        for(int i=0;i<B;i++)
        {
            sum+=m_arr[p_m];
            p_m++;
        }

        for(int i=0;i<C;i++)
        {
            sum+=f_arr[p_f];
            p_f++;
        }
        cout<<fixed<<setprecision(2)<<(sum/11.0)<<"\n";
    }

    return 0;
}