#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        stack<unsigned long long> st;  // 每组数据重新开栈

        while (n--) {
            char op[10];   // ✅ 用字符数组代替 string，避免 string 比较带来的 TLE
            cin >> op;

            if (op[0] == 'p') {        // push 或 pop 都以 p 开头
                if (op[1] == 'u') {    // push
                    unsigned long long x;
                    cin >> x;
                    st.push(x);
                } else {               // pop
                    if (st.empty())
                        cout << "Empty\n";
                    else
                        st.pop();
                }
            }
            else if (op[0] == 'q') {   // query
                if (st.empty())
                    cout << "Anguei!\n";
                else
                    cout << st.top() << "\n";
            }
            else {                     // size
                cout << st.size() << "\n";
            }
        }
    }
    return 0;
}