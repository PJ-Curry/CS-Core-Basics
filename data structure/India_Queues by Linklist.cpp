//在队列中要保证队列的操作时间复杂度都为O(1)
//在front里实现Dequeue 在near末尾实现Enqueue(入队)
//因为是链表 如果没有rear就要一直遍历到后面 时间复杂度将会是O(n) 所以需要rear指针
#include<iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
};
struct Node *front=NULL;
struct Node *rear=NULL;
void Enqueue(int x)
{
    Node *temp=new Node();
    temp->data=x;
    temp->next=NULL;
    if(front==NULL&&rear==NULL)
    {
        front=rear=temp;
        return;
    }//一定要动手画图
    rear->next=temp;//temp是一个独立的存储新节点地址的指针 让rear的next指向temp所指向的节点的地址
    rear=temp;//然后把rear向后推 赋值等于temp
}
void Dequeue()
{
    struct Node *temp=front;
    if(front==NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    if(front==rear)
    {
        front=rear=NULL;
    }
    else
    {
        front=front->next;
    }
    free(temp);//释放节点 如果没有temp 不知道上一个节点的地址 temp在存储 
}
int Front() {
	if(front == NULL)
    {
		printf("Queue is empty\n");
		return;
	}
	return front->data;
}

void Print() 
{
	struct Node* temp = front;
	while(temp != NULL) 
    {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	/* Drive code to test the implementation. */
	// Printing elements in Queue after each Enqueue or Dequeue 
	Enqueue(2); Print(); 
	Enqueue(4); Print();
	Enqueue(6); Print();
	Dequeue();  Print();
	Enqueue(8); Print();
}