#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
using namespace std;

// 数组开在全局区，防止栈溢出，1010 足够应对 n=1000
const int MAXN = 1010;
int pref[MAXN][MAXN];     // 男人的偏好 ID 名单
int rank_w[MAXN][MAXN];   // 女人的偏好排名矩阵
int match_w[MAXN];        // 女人的当前归宿
int next_p[MAXN];         // 每个男人要求的下一个排名索引
string man_names[MAXN], woman_names[MAXN];

// 鲁棒的解析函数：把 ':' 和 '>' 都当空格处理，直接用 stringstream 读
void parse(string line, string& name, vector<string>& list) {
    for (char &c : line) {
        if (c == ':' || c == '>') c = ' ';
    }
    stringstream ss(line);
    if (!(ss >> name)) return;
    string temp;
    while (ss >> temp) list.push_back(temp);
}

int main() {
    // 关掉同步流，加快 I/O，防止大数据下真的超时
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    string line;
    getline(cin, line); // 吃掉 n 之后的回车

    map<string, int> m_to_id, w_to_id;
    map<string, vector<string>> m_prefs_raw, w_prefs_raw;
    vector<string> m_input_order;

    // 第一步：读入所有人，建立名字和 ID 的双向映射
    // 假设前 n 行是男人，后 n 行是女人
    for (int i = 0; i < n; i++) {
        if (!getline(cin, line) || line.empty()) { i--; continue; }
        string name; vector<string> v;
        parse(line, name, v);
        m_to_id[name] = i;
        man_names[i] = name;
        m_prefs_raw[name] = v;
        m_input_order.push_back(name);
    }
    for (int i = 0; i < n; i++) {
        if (!getline(cin, line) || line.empty()) { i--; continue; }
        string name; vector<string> v;
        parse(line, name, v);
        w_to_id[name] = i;
        woman_names[i] = name;
        w_prefs_raw[name] = v;
    }

    // 第二步：预处理 ID 矩阵，这是跑出 O(n^2) 的关键
    for (int i = 0; i < n; i++) {
        string mn = man_names[i];
        for (int j = 0; j < n; j++) {
            // 男人的偏好存的是女人的 ID
            pref[i][j] = w_to_id[m_prefs_raw[mn][j]];
        }
    }
    for (int i = 0; i < n; i++) {
        string wn = woman_names[i];
        for (int j = 0; j < n; j++) {
            // 女人的排名矩阵：rank_w[女ID][男ID] = 排名数字
            rank_w[i][m_to_id[w_prefs_raw[wn][j]]] = j;
        }
    }

    // 第三步：Gale-Shapley 算法核心
    queue<int> free_men;
    for (int i = 0; i < n; i++) {
        free_men.push(i);
        match_w[i] = -1; // 初始都单身
        next_p[i] = 0;   // 从第一志愿开始
    }

    while (!free_men.empty()) {
        int m = free_men.front();
        free_men.pop();

        int w = pref[m][next_p[m]++]; // 男人 m 找下一个心仪的 w
        if (match_w[w] == -1) {
            match_w[w] = m;
        } else {
            int m_old = match_w[w];
            // 比较排名，值越小代表排名越靠前
            if (rank_w[w][m] < rank_w[w][m_old]) {
                match_w[w] = m;
                free_men.push(m_old); // 前任被踢回队列
            } else {
                free_men.push(m);     // 现任更好，求婚者继续单身
            }
        }
    }

    // 第四步：按男人名字排序输出
    map<string, string> res;
    for (int i = 0; i < n; i++) {
        res[man_names[match_w[i]]] = woman_names[i];
    }
    for (auto const& [m, w] : res) {
        cout << "(" << m << "," << w << ")" << endl;
    }

    return 0;
}