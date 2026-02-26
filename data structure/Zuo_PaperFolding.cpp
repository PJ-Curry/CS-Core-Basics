//纸张对折问题 微软原题 讨论一张纸条对折后折痕的凹凸性 本质上是二叉树的中序遍历
#include<bits/stdc++.h>
using namespace std;

class PaperFolding{
public:
    //递归过程，模拟遍历虚拟的二叉树
    //i：当前层数
    //N：总层数
    //isDown:true代表凹，false代表凸
    void printProcess(int i, int N, bool isDown)
    {
        if(i > N)
        {
            return;
        }
        //既然是中序遍历 一定是按照左 中 右这个顺序递归
        //对于左树来说 一定是凹的 递归
        printProcess(i + 1, N, true);
        //中 打印当前节点的折痕方向
        cout << (isDown ? "凹" : "凸");
        printProcess(i + 1, N, false);
    }

    //主入口函数
    void printAllFolds(int N)
    {
        //第一次这点产生根节点 一定是凹
        printProcess(1, N, true);
        cout << endl;//打印之后换行
    }
};

int main()
{
    PaperFolding pf;
    int N = 3;
    cout << "折叠 " << N << " 次的折痕从上到下为：" << endl;
    pf.printAllFolds(N);
    return 0;
}