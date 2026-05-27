//动态规划反向遍历
#include<bits/stdc++.h>
using namespace std;

int dp[12881]; //dp[j]表示容量为j的背包能装下的最大价值

int main(){
    int N, M;//n件物品 M是容量
    if(!(cin >> N >> M)) return 0;

    for(int i = 0; i < N; i++){
        int w, d;
        cin >> w >> d;//w是重量 d是价值
        for(int j = M; j >= w ; j--){
            dp[j] = max(dp[j], dp[j - w] + d);
        }
    }

    cout << dp[M] << endl;
    
    return 0;
}

/*
当我们要决定是否要把一个重量为 w=3 的物品放进容量为 6 的包里时，
我们会查表：“如果我腾出 3 个空间，
剩下的 3 个空间（dp[3]）最高能装多少价值？”
所以顺序是逆向
*/