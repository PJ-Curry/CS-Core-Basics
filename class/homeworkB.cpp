#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int N;
    cin >> N; 
    vector<vector<int>> outputs; //存所有输出结果 延迟输出关键的数据结构
//不知道组数是多少外层vector支持动态扩容 每组输出结果的长度也不知道是多少vector<int>会自动管理 最后统一输出
    for (int group = 0; group < N; group++) 
    {
        int T;
        cin >> T;
        list<int> chatList;
        for (int i = 0; i < T; i++) 
        {
            int id;
            cin >> id;
            auto it = find(chatList.begin(), chatList.end(), id);
            if (it != chatList.end()) chatList.erase(it);
            chatList.push_front(id);
        }// 把这一组结果存进 vector<int> 里 相当于res是一个vector<int>
        vector<int> res;//res是当前组的结果 outputs是总的容器
        for (int id : chatList) res.push_back(id);
        outputs.push_back(res); // 存下来
    }
    for (int i = 0; i < N; i++) 
    { // 外层：第 i 组结果
        for (int j = 0; j < outputs[i].size(); j++) 
        { // 内层：第 i 组中的第 j 个元素
            if (j > 0) cout << " "; // 控制空格格式（首个元素不加空格）
            cout << outputs[i][j];
        }
        cout << endl;
    }    
    /*
    for (const auto& res : outputs)//const auto&不拷贝 只引用 外层循环
    {
        for (int i = 0; i < res.size(); i++)
         {
            cout << res[i]<<" ";
         }
        cout << endl;
    }auto是一个自动推断类型 在这里等价于vector<int> &是引用意味着不复制，直接使用原来的vector<int> 
*/
//vector外层是每一组的测试结果 内层vector<int>是该组测试的聊天列表输出结果 
    return 0;
}