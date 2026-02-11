//Stack-Linked List implementation 
//Insert/delete
//-at the end of list(tail O(n) 因为链表要从头遍历才能到后面  -at beginning(head) O(1)
//创建一个结构体类型的链表
#include<iostream>
using namespace std;
struct Node{
    int data;
    Node *link;
};
Node *top=NULL;//初始化 top就是之前的head
void Push(int x){
    Node *temp=new Node();//动态分配(创建)新节点
    temp->data=x;//存储数据
    temp->link=top;//新节点指向原栈项 让在头部创建的新节点等于top所指向的旧节点
    top=temp;//让top指向新节点
}
void Pop(){
    Node *temp;
    if(top=NULL) return;
    temp=top;
    top=top->link;//link类似于next
    free(temp);
}