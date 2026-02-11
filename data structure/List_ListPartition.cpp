/*
题目描述：在一个链表中 指定一个数 在链表中 这个数字之前的数字都小于他 中间的等于 后面的大于
*/
#include<iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(NULL){}
};

//三路partition
ListNode *listPartition(ListNode *head,int pivot)
{
    if(!head || !head->next) return;

    ListNode *sh=NULL,*st=NULL;
    ListNode *eh=NULL,*et=NULL;
    ListNode *bh=NULL,*bt=NULL;

    while(head!=NULL)
    {
        ListNode *nxt=head->next;//保存后继
        head->next=NULL;//断开旧链

        if(head->val<pivot)
        {
            if(!sh) sh=st=head;//！head含义是 如果head是空指针
            else st->next=head; st=head;//往下更新
        }

        if(head->val==pivot)//双等号 别犯错
        {
            if(!eh) eh=et=head;
            else et->next=head; et=head;
        }

        if(head->val>pivot)
        {
            if(!bh) bh=bt=head;
            else bt->next=head; bt=head;
        }
        head=nxt;
    }

    //分拣结束 开始连接各个部分
    if(st)
    {
        st->next=eh;
        et=et?et:st;//如果存在就et 如果不存在跳过eh直接连st
    }
    if(et)
    {
        et->next=bh;
    }
    //选新的头
    return sh?sh:(eh?eh:bh);
}

int main() 
{
    // 1. 手动创建链表：3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1
    //有点丑陋 应该建立一个Insert函数的
    ListNode* h = new ListNode(3);
    h->next = new ListNode(5);
    h->next->next = new ListNode(8);
    h->next->next->next = new ListNode(5);
    h->next->next->next->next = new ListNode(10);
    h->next->next->next->next->next = new ListNode(2);
    h->next->next->next->next->next->next = new ListNode(1);

    // 2. 设置 pivot
    int pivot = 5;

    // 3. 调用分区函数
    h = listPartition(h, pivot);

    // 4. 打印链表
    ListNode* p = h;
    while (p != nullptr) 
    {
        cout << p->val;
        if (p->next != nullptr) cout << " -> ";
        p = p->next;
    }
    cout << endl;

    return 0;
}