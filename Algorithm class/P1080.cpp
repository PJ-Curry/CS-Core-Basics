//贪心问题 通过数学推导 可以知道 要对左右手的成绩进行贪心策略 让拿钱最多的人拿钱最少
#include<bits/stdc++.h>
using namespace std;
// 大臣结构体
struct Minister {
    int a, b;
    long long prod;
};

// 贪心排序：按 a*b 从小到大排 这样的策略一定是正确的
bool cmp(const Minister& x, const Minister& y) {
    return x.prod < y.prod;
}

// 高精度乘法：BigInt * int
vector<int> multiply(const vector<int>& A, int b) {
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || t; i++) {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

// 高精度除法：BigInt / int (向下取整)
vector<int> divide(vector<int>& A, int b) {
    vector<int> C;
    int r = 0;
    for (int i = A.size() - 1; i >= 0; i--) {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

// 高精度比较：A > B 返回 true
bool isGreater(vector<int>& A, vector<int>& B) {
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] > B[i];
    }
    return false;
}

int main(){
    int n;
    cin >> n;

    // 读入国王的手数
    int ka, kb;
    cin >> ka >> kb;

    vector<Minister> mins(n);
    for (int i = 0; i < n; i++) {
        cin >> mins[i].a >> mins[i].b;
        mins[i].prod = (long long)mins[i].a * mins[i].b;//开三个数组 左手右手乘积数组
    }

    //1.贪心排序
    sort(mins.begin(), mins.end(), cmp);//begin end都指向的是mins数组第一个元素的指针
    
    //2.计算 已经确定了谁会拿最多的钱了
    vector<int> current_prod;//存储前面所有人左手的乘积
    int temp = ka;
    while(temp){
        current_prod.push_back(temp % 10);
        temp /= 10;//把国王每位都存进去 得拆 要循环
    }

    vector<int> max_reward = {0};

    for(int i = 0; i < n; i++){
        vector<int> reward = divide(current_prod, mins[i].b);
        
        //更新最大奖金
        if (isGreater(reward, max_reward)){
            max_reward = reward;//贪心策略让我们确定了 这里的最大奖金的人就是对的人 但我们目前还不知道这个人是谁 要都算出来
        }

        //更新左手成绩，为下一个大臣准备
        current_prod = multiply(current_prod, mins[i].a);
    }

    //输出大整数
    for(int i = max_reward.size() - 1; i >= 0; i--){
        cout << max_reward[i];
    }
    cout << endl;

    return 0;
}