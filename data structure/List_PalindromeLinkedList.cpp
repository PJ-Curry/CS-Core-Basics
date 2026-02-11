//判断一个单向链表是不是回文结构 Time：O(n) Space:O(1)
//用快慢指针+反转链表
#include<iostream>
#include<stack>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(NULL){}//构造函数 int x用来初始化节点的数据域val
};

//反转链表
ListNode *reverseList(ListNode *head)//返回值 反转后新链表的头指针
{
    ListNode *prev=NULL;
    while(head!=NULL)
    {
        ListNode *nextNode = head->next;
        head->next=prev;
        prev=head;
        head=nextNode;
    }
    return prev;
}

bool isPalindrome(ListNode *head)
{
    if(!head||!head->next) return true;

    //1.快慢指针找到中点
    ListNode *slow=head;
    ListNode *fast=head;
    while(fast->next&&fast->next->next)
    {
        slow=slow->next;
        fast=fast->next->next;
    }

    //2.翻转后半部分
    ListNode *secondHalf=reverseList(slow->next);

    //3.比较
    ListNode *p1=head;
    ListNode *p2=secondHalf;
    bool result=true;
    while(p2)
    {
        if(p1->val!=p2->val)
        {
            result=false;
            break;
        }
        p1=p1->next;
        p2=p2->next;
    }

    //4.恢复链表结构
    slow->next=reverseList(secondHalf);
    return result;
}

//额外空间复杂度为O(n)的栈算法
bool isPalindrome_stack(ListNode *head)
{
    if(!head || !head->next) return true;

    stack<int>st;
    ListNode *cur=head;

    //把所有值压栈
    while(cur!=NULL)
    {
        st.push(cur->val);
        cur=cur->next;
    }

    //再遍历一次链表 每次弹出比较
    cur=head;
    while(cur!=NULL)
    {
        if(cur->val!=st.top()) return false;
        st.pop();
        cur=cur->next;
    }
    return true;
}