#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n, m, a, b;
    if(!(cin >> n >> m >> a >> b)){
        return 0;
    }

    long long plan1 = n * a;
    long long plan2 = (n / m) * b + (n % m) * a;
    long long plan3 = ((n + m - 1) / m) * b;

    long long min_cost = min({plan1, plan2, plan3});

    cout << min_cost << endl;

    return 0;
}