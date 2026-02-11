//队列:使用数组实现一个队列
#include<iostream>
using namespace std;
#define MAX_SIZE 101
class Queue
{
private:
    int A[MAX_SIZE];
    int front,rear;
public:
    //初始化 两个pointer为-1
    Queue()
    {
        front=-1;
        rear=-1;
    }
    

    bool Isempty()
    {
        return(front==-1&&rear==-1);
    }

    bool IsFull()
    {
        return(rear+1)%MAX_SIZE==front?true:false;
    }

    void Enqueue(int x)//向队列中插入数据
    {
        cout<<"Enqueuing"<<x<<"\n";
        if(IsFull())
        {
            cout<<"Error:Queue is Full\n";
            return;
        }
        if(Isempty())
        {
            front=rear=0;
        }
        else
        {
            rear=(rear+1)%MAX_SIZE;
        }
        A[rear]=x;//赋值
    }
    //返回队列中的首个元素
    int Front()
    {
        if(front==-1)
        {
            cout<<"Error:cannot return front empty queue\n";
            return -1;
        }
        return A[front];
    }
    //打印函数 和queue没啥关系
    void Print()
    {
        //首先确定队列中的元素个数
        int count=(rear+MAX_SIZE-front)%MAX_SIZE+1;
        cout<<"Queue:";
        for(int i=0;i<count;i++)
        {
            int index=(front+i)%MAX_SIZE;
            cout<<A[index]<<" ";
        }
        cout<<"\n\n";
    }
};
int main()
{
    Queue Q;
    Q.Enqueue(2);Q.Print();
    Q.Enqueue(4);Q.Print();
    Q.Enqueue(6);Q.Print();
    Q.Enqueue(8);Q.Print();
}