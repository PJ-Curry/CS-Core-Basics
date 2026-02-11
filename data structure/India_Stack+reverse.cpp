#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
/*class Stack
{
private:
    char A[101];
    int top;
public:
    void Push(int x);
    void Pop();
    int Top();
    bool Isempty();
};*/
void Reverse(char C[],int n)//char C[]就是char *C
{
    stack<char> S;
    for(int i=0;i<n;i++)
    {
        S.push(C[i]);
    }
    for(int i=0;i<n;i++)
    {
        C[i]=S.top();//C[i]是栈顶的元素 赋值
        S.pop();//pop
    }
}
int main()
{
    char C[51];
    printf("Enter a string: ");
    gets(C);
    Reverse(C,strlen(C));
    printf("Output=%s",C);
}
//Time complexity:O(n)  Space-complexity:O(n)
//Reverse a Linked List
void Reverse2()
{
    if(head==NULL) return;//检查空链表
    stack<struct Node*>S;//储存链表节点的栈
    Node *temp=head;
    while(temp!=NULL)
    {
        S.push(temp);//当前节点入栈
        temp=temp->next;//移动到下一个节点
    }
    temp=S.top();//栈顶是原链表的尾节点
    head=temp;//新的头结点指向愿尾节点
    S.pop();//弹出栈顶
    while(!S.empty())
    {
        temp->next=S.top();//指向翻转
        S.pop();
        temp=temp->next;
    }
    temp->next=NULL;//防止循环链表
}
//Time complexity O(n)