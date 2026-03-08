#include <iostream>
#include <vector>
#include <queue>
using namespace std; 
//本质上就是拓扑排序
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //准备两个档案库
        vector<int> inDegree(numCourses, 0);//存储每一门课的入度 即解锁该门课的先修课个数
        vector<vector<int>> graph(numCourses);//存放每门课后面的小弟

        //把pre二维数组的数据 翻译成我们能看懂的 入度和邻接表
        for(const auto& info : prerequisites){
            int to = info[0];//a是想要学的
            int from = info[1];//b是先修课

            graph[from].push_back(to);
            inDegree[to]++;
        }

        //把入度为0的课先扔进队列
        queue<int> zeroQueue;
        for(int i = 0; i < numCourses; i++){
            if(inDegree[i] == 0){
                zeroQueue.push(i);
            }
        }

        int learnedCount = 0;//记录我们已经学习了几门课

        //检测图中是否存在环路的核心循环
        while(!zeroQueue.empty()){
            int curCourse = zeroQueue.front();
            zeroQueue.pop();
            learnedCount++;

            for(int nextCourse : graph[curCourse]){
                inDegree[nextCourse] = inDegree[nextCourse] - 1;
                if(inDegree[nextCourse] == 0){
                    zeroQueue.push(nextCourse);
                }
            }
        }
        return learnedCount == numCourses;
    }
};

int main() {
    Solution sol; 
    
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}}; 
    
    // C++ 里的 bool 值，打印出来 true 是 1，false 是 0
    cout << "测试用例 1 (预期能学完，输出 1): " << sol.canFinish(numCourses1, prerequisites1) << endl;

    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}}; 
    
    cout << "测试用例 2 (预期死锁了，输出 0): " << sol.canFinish(numCourses2, prerequisites2) << endl;

    return 0; 
}