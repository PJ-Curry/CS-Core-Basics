#include<bits/stdc++.h>
using namespace std;

int N;
double L, R;
double a[15];//存系数

//秦九韶算法
double f(double x){
    double res = 0;
    for(int i = 0; i <= N; i++){
        res = res * x + a[i];
    }
    return res;
}

int main(){
    if(!(cin >> N >> L >> R)) return 0;

    //读入系数
    for (int i = 0; i <= N; i++){
        cin >> a[i];
    }

    //三分查找
    double l = L, r = R;

    for(int i = 0; i < 100; i++){
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;

        if(f(m1) < f(m2)){
            l = m1; //峰值在右侧
        }
        else{
            r = m2;
        }
    }

    cout << fixed << setprecision(5) << l << endl;

    return 0;
}