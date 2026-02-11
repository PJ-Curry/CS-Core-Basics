/*
题目：给定两个可能有环也可能无环的单链表，头节点 head1 和 head2。
请实现一个函数，如果两个链表相交，请返回相交的第一个节点。
如果不相交，返回 null。

要求：
1. 如果两个链表长度之和为 N，时间复杂度请达到 O(N)；
2. 额外空间复杂度请达到 O(1)。

代码内容比较繁琐 但是逻辑十分清晰
*/   
#include<iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){}
};
//运用快慢指针检测入环节点
ListNode *detectcycle(ListNode *head)
{
    if(!head||!head->next) return NULL;
    ListNode *slow=head;
    ListNode *fast=head;
    //相遇检测
    while(fast&&fast->next)
    {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) break;
    }
    //无环
    if(!fast||!fast->next) return NULL;
    //让slow回到起点 让fast变成一步走一个
    slow=head;
    while(slow!=fast)
    {
        slow=slow->next;
        fast=fast->next;
    }
    return slow;//找到的就是入环节点
}
//进入正题 无环情况：双指针拼接法 空间O(1)
//第一种情况：两个链表都无环 可能相交也可能不相交
ListNode *getIntersectionNodeNoCycle(ListNode *headA,ListNode *headB)
{
    if(!headA||!headB) return NULL;
    ListNode *pA=headA;
    ListNode *pB=headB;
    while(pA!=pB)
    {
        pA=pA?pA->next:headB;
        pB=pB?pB->next:headA;
    }
    return pA;
}
//多加一步：计算从head到loop的节点数
int countToloop(ListNode *head,ListNode *loop)
{
    int cnt=0;
    ListNode *cur=head;
    while(cur!=loop)
    {
        ++cnt;
        cur=cur->next;
    }
    return cnt;
}
//第二第三种情况 有环+无环 两个有环
ListNode *getIntersectionNodeWithCycle(ListNode *headA,ListNode *headB,ListNode *loopA,ListNode *loopB)
{
    int cntA;
    int cntB;//计数
    //情形1：入环节点相同
    if(loopA==loopB)
    {
        int cntA=countToloop(headA,loopA);
        int cntB=countToloop(headB,loopB);
        ListNode *pA=headA;
        ListNode *pB=headB;
        //对齐
        if(cntA>cntB)
        {
            int diff=cntA-cntB;
            while(diff--) pA=pA->next;
        }
        else
        {
            int diff=cntB-cntA;
            while(diff--) pB=pB->next;
        }

        //第三大类 第二种情况 在入环之前找到第一个相同节点 若找不到 那入环节点第一个交点就是
        while(pA!=pB&&pA!=loopA&&pB!=loopB)
        {
            pA=pA->next;
            pB=pB->next;
            if(pA==pB) return pA;
            else return loopA;
        }
    }
    else//情形三 入环点不同 需要区分两个环是不是一个
    {
        ListNode *cur=loopA->next;
        while(cur!=loopA)
        {
            if(cur==loopB)
            {
                return loopA;
            }
            cur=cur->next;
        }
        //两个独立环 不相交
        return NULL;
    }
}
//完整函数：先判断有没有环 再分情况讨论
ListNode *getIntersectionNode(ListNode *headA,ListNode *headB)
{
    if(!headA||!headB) return NULL;
    ListNode *loopA=detectcycle(headA);
    ListNode *loopB=detectcycle(headB);
    if(!loopA&&!loopB)
    return getIntersectionNodeNoCycle(headA,headB);
    else if(( loopA && !loopB ) || ( !loopA && loopB ))
    return NULL;
    else
    return getIntersectionNodeWithCycle(headA,loopA,headB,loopB);
}

int main()
{

}