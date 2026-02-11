#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int arr[MAXN][MAXN] = {0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin >> n >> m;

    for(int i = 1; i <= m;i++)
    {
        int u,v;
        cin >> u >> v;
        arr[u][v] = 1;
        arr[v][u] = 1;
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout<<endl;
    }

    for(int i = 1; i <= n; i++)
    {
        int degree = 0;
        for(int j = 1; j <= n; j++)
        {
            if(arr[i][j] == 1) degree++;
        }
        cout << degree;//输出度数

        for(int j = 1; j <= n; j++)
        {
            if(arr[i][j] == 1)
            {
                cout<<" "<< j;
            }
        }
        cout << endl;
    }
    return 0;
}