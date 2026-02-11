#include<bits/stdc++.h>
using namespace std;
string inorder,postorder;

void buildPre(int inL,int inR,int postL,int postR)
{
    if(inL > inR || postL > postR) return;

    //后序的最后一个字符是当前子树的根
    char root = postorder[postR];
    cout << root;//输出根

    //在中序中找到根的位置
    int k = inL;
    while(k <= inR && inorder[k] != root) ++k; //找到了根 中序被分成了两半儿 再递归

    int leftsize = k - inL;
    buildPre(inL, k - 1, postL, postL + leftsize - 1);//左子树
    buildPre(k + 1, inR, postL + leftsize, postR - 1);//右子树
}

int main()
{
    cin >> inorder >>postorder;
    int n = inorder.size();
    buildPre(0, n-1, 0, n-1);//覆盖全部节点
    return 0;
}