/*
题目：复制含有随机指针节点的链表
一种特殊的单链表节点类描述如下：
class Node {f
    int value;
    Node next;
    Node rand;
    Node(int val) {
        value = val;
    }
}
说明：
- rand 指针是单链表节点结构中新增加的指针，
- rand 可能指向链表中的任意一个节点，也可能指向 null。
- 给定一个由 Node 节点类型组成的无环单链表的头节点 head，
  请实现一个函数完成这个链表的复制，并返回复制的新链表的头节点  完全复制一个新的 一模一样的
要求：
- 时间复杂度 O(N)
- 额外空间复杂度 O(1)
*/
//方法1 哈希表O(N) O(1)
#include<iostream>
#include<unordered_map>
using namespace std;
struct Node
{
    int value;
    Node *next;
    Node *rand;
    Node(int v):value(v),next(NULL),rand(NULL){};
};

Node *copyRandomList_hash(Node *head)//哈希表映射
{
    if(!head) return NULL;

    unordered_map<Node*,Node*>mp;//旧节点->新节点 创建的是哈希表容器

    //step1:为每个老节点创建值相同的新节点 建立映射
    for(Node *cur=head;cur;cur=cur->next)
    {
        mp[cur]=new Node(cur->value);
    }

    //第二趟:补齐所有指针连接 next/rand
    for(Node *cur=head;cur;cur=cur->next)
    {
        mp[cur]->next=cur->next?mp[cur->next]:NULL;
        mp[cur]->rand=cur->rand?mp[cur->rand]:NULL;
    }
    
    return mp[head];
}
//时间复杂度O(n) 空间复杂度O(n)

//方法2：穿插法 时间O(n) 空间O(1)
Node *copyRandomList_interweave(Node *head)
{
    if(!head) return NULL;

    //step1：复制每个节点 完成穿插
    for(Node *cur=head;cur!=NULL; )
    {
        Node *nxt=cur->next;
        Node *copy=new Node(cur->value);
        cur->next=copy;
        copy->next=nxt;
        cur=nxt;
    }

    //step2:连接复制节点的rand指针
    for(Node *cur=head;cur!=NULL;cur=cur->next->next)
    {
        Node *curCopy=cur->next;
        curCopy->rand=(cur->rand?cur->rand->next:NULL);
    }

    //step:3 将两个链表拆分
    Node *newHead=head->next;
    for(Node *cur=head;cur!=NULL; )
    {
        Node *curCopy=cur->next;
        Node *nxt=curCopy->next;
        cur->next=curCopy->next;
        curCopy->next=(nxt?nxt->next:NULL);
        cur=nxt;
    }
    return newHead;
}

int main()
{
    Node *n1=new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    n1->next = n2; n2->next = n3;
    // rand：1->3, 2->1, 3->2
    n1->rand = n3; n2->rand = n1; n3->rand = n2;
    Node *copy1=copyRandomList_interweave(n1);
    //Node *copy2=copyRandomList_hash(n1);

    //简单打印验证
    for(Node *p=copy1;p;p=p->next)
    {
        cout<<"val= "<<p->value<<",rand="<<(p->rand?p->rand->value:-1)<<"\n";
    }
    return 0;
}