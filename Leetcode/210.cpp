//也是拓扑排序 和Zuo_topu sort.cpp一样 特判需要在result那有些不一样 只要是有死循环 就不能反悔result
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // 1. 准备两个档案库
        vector<int> inDegree(numCourses, 0); // 存储每一门课的入度
        vector<vector<int>> graph(numCourses);

        // 2. 建图
        for(const auto& info : prerequisites){
            int to = info[0];   // 想要学的
            int from = info[1]; // 先修课

            graph[from].push_back(to);
            inDegree[to]++;
        }

        // 3. 把入度为 0 的软柿子先扔进队列
        queue<int> zeroQueue;
        for(int i = 0; i < numCourses; i++){
            if(inDegree[i] == 0){
                zeroQueue.push(i);
            }
        }

        vector<int> result;

        // 4. 核心循环：剥洋葱并记录顺序
        while(!zeroQueue.empty()){
            int curCourse = zeroQueue.front();
            zeroQueue.pop();
            
            // 出队列的瞬间，存入最终结果集
            result.push_back(curCourse);

            // 顺藤摸瓜通知小弟
            for(int nextCourse : graph[curCourse]){
                inDegree[nextCourse] = inDegree[nextCourse] - 1;
                if(inDegree[nextCourse] == 0){
                    zeroQueue.push(nextCourse);
                }
            }
        }
        
        // 5. 终极防线：秋后算账判环
        // 成功装进结果里的课，是不是等于总课程数？
        if(result.size() == numCourses){
            return result; // 完美毕业，交出课表！
        } else {
            return {};     // 发现死循环，交白卷！
        }
    }
};

// 🌟 本地测试专用 Main 函数
int main() {
    Solution sol;
    int num1 = 4;
    vector<vector<int>> pre1 = {{1,0}, {2,0}, {3,1}, {3,2}};
    vector<int> res1 = sol.findOrder(num1, pre1);
    
    cout << "测试用例 1 排课结果: ";
    if(res1.empty()) {
        cout << "死循环了，交白卷 []";
    } else {
        for(int course : res1) {
            cout << course << " "; // 挨个打印数组里的课
        }
    }
    cout << endl;

    int num2 = 3;
    vector<vector<int>> pre2 = {{1,0}, {1,2}, {0,1}};
    vector<int> res2 = sol.findOrder(num2, pre2);
    
    cout << "测试用例 2 排课结果: ";
    if(res2.empty()) {
        cout << "死循环了，交白卷 []";
    } else {
        for(int course : res2) {
            cout << course << " ";
        }
    }
    cout << endl;

    return 0;
}