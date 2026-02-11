//约瑟夫环问题
#include<iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int x):data(x),next(NULL){}
};
int main()
{
    int n,m;
    cin>>n>>m;

    Node *head=new Node(1);
    Node *tail=head;
    for(int i=2;i<=n;i++)
    {
        tail->next=new Node(i);
        tail=tail->next;
    }
    tail->next=head;//成环

    Node *cur=head;
    Node *pre=tail;

    int len=n;
    while(len>0)
    {
        for(int i=1;i<m;i++)
        {
            pre=cur;
            cur=cur->next;
        }
        cout<<cur->data<<" ";
        pre->next=cur->next;
        Node *del=cur;
        cur=cur->next;
        delete del;
        len--;
    }
    return 0;
}