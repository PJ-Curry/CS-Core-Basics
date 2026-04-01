#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int dist[105][105];//输出结果的矩阵

int main(){
    int n, m;//点的个数 边的个数
    if(!(cin >> n >> m)) return 0;

    //1.初始化地图
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if (i == j) dist[i][j] == 0;
            else dist[i][j] = INF;
        }
    }

    //2.读入边
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        if(w < dist[u][v]){
            dist[u][v] = dist[v][u] = w;
        }
    }

    //3.Floyd核心算法 注意中间节点k的循环一定在最外层
    for (int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(dist[i][k] != INF && dist[k][j] != INF){
                    if(dist[i][k] + dist[k][j] < dist[i][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    //4.输出结果
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}