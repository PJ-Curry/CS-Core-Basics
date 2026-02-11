//单调栈的实现 找到数组左边离自己最近的更大的数 实现时间复杂度为O(n)
//正常的暴力遍历时间复杂度是O(n^2)
//这种算法 每一个数字都入栈一次 出栈一次 时间复杂度是O(n)
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
vector<int> findLeftGreater(vector<int>&nums)
{
    vector<int>leftGreater(nums.size()-1);
    stack<int>stack;//创建一个新的栈
    for(int i=0;i<nums.size()-1;i++)
    {
        while(!stack.empty()&&nums[i]>=nums[stack.top()])
        {
            stack.pop();
        }
        leftGreater[i]=stack.empty()?-1:stack.top();
        stack.push(i);//压栈
    }
}//不写主函数了