//链表的逻辑 创建 遍历 插入n 在这里temp是temporary临时的意思
#include<iostream>
using namespace std;
int main()
{
    struct Node
    {
        int data;
        Node* link;
    };//接下来声明一下头结点
    Node *A;//创建一个新链表(空链表)    
    A=NULL;//empty list
    //要在列表中插入一个节点 操作如下
    //先创建内存块 通过malloc 参数是内存块所需要的字节数 
    //是动态分配的内存 然后通过指针来引用该内存
    //malloc返回一个void指针  malloc需要进行类型转换 需要转换成Node*
    //将temp作为指向节点的指针
    Node *temp=new Node();//C++
    //Node *temp=(Node*)malloc(sizeof(Node));
    //往节点里添加数据 调整链接 解引用创建的malloc指针
    temp->data=2;//写入数据
    temp->link=NULL;//因为新创建的这个节点既是第一也是最后一个节点 是NULL
    A=temp;//A是头指针 temp是头结点 这句将temp的地址赋值给A使得头指针指向头结点

    temp=new Node();//想在原来的链表尾部继续添加
    temp->data=4;
    temp->link=NULL;//因为是最后一个节点 所以地址要等于0
    //链表的遍历
    Node *temp1=A;//不能用A这个头指针来一直往下遍历 这样的话会丢失链表的首地址
    while(temp1->link!=NULL)
    {
        temp1=temp1->link;//会到达最后一个节点
    }
    temp1->link=temp;//连接上了
    //要是再建立新的节点 和第24行开始逻辑一样


    //链表:在头部插入一个节点
    struct Node
    {
        int data;
        Node* next;//C++不用写sturct C语言要写struct
    };
    struct Node* head;//全局声明                               删掉这一行 对应65行 局部变量
    void Insert(int x)//插入的实现过程                         我们必须传递一个头结点的地址Node* void Insert(Node* head,int x)这里的head也是一个局部变量
    {
        Node* temp=new Node();  
        temp->data=x;
        //实现如何在第一个节点非空的情况下在头部插入一个节点
        //再创建一个新Node 地址还是指向NULL 还是temp指向这个Node
        temp->next=head;//现在temp和之前的head就等效了 指向第一个节点
        head=temp;//现在head连接了新创建的Node 切断了head和第一个节点的联系  return head;
    }
    void Print()//和遍历类似                                  void Print(Node* head)这里的head和第65行的局部变量head就不是一个东西了 这样第56行可以删掉 因为你传入了参数第75行
    {
        Node* temp=head;                                     //不再需要临时的temp指针了
        while(temp!=NULL)
        {                                                    //直接变成cout<<head->data;
            cout<<temp->data<<" ";                                //head=head->next;
            temp=temp->next;
        }
    }
    int main()
    {
        head=NULL;//empty全局指针变量 目前链表为空             改为局部变量Node* head=NULL; 这个无法在其他函数被访问了比如Insert函数 print函数
        cout<<"一共有多少数字";
        int n,i,x;//x是要插入的数字
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cout<<"enter the number";
        }
        cin>>x;
        Insert(x);//前面来具体写一些这两个函数的执行过程        head=Insert(head,x);这是返回头结点的地址来进行插入
        Print();                                            //Print(head)
    }
    //内存释放
    while(head!=NULL)
    {
        Node* temp=head;
        head=head->next;
        delete temp;
    }
    return 0;
}

//另外两种写法 对应上面的注释 第一种写法 值传递
    struct Node
    {
    int data;
    Node* next;
    };
    Node* Insert(Node *head,int x)//接收一个头结点的地址和值，返回修改后的链表
    //Node *Insert是声明函数将返回一个新节点的指针
    {
        struct Node* temp=(Node*)malloc(sizeof(Node));
        temp->data=x;
        temp->next=head;
        head=temp;
        return head;//返回新的head 因为头指针可能会改变
    }
    void Print(const Node *head)//值传递 下一个就是引用传递
    {
        cout<<"List is:";
        while(head!=NULL)  //用head本身不用temp
        {
            cout<<head->data;
            head=head->next;
        }
    }
    int main()
    {
        Node *head=NULL;//局部变量 初始化空链表 把头结点的地址作为两个函数的参数
        cout<<"一共有多少数字";
        int n,i,x;//x是要插入的数字
        cin>>n;
        cin>>x;
        for(int i=0;i<n;i++)
        {
            cout<<"enter the number";
            head=Insert(head,x);//调用方必须接收返回值 保存头结点
            Print(head);
        }
    }
    /*int main() {
    Node* head = NULL;  // 初始空链表
    
    // 第一次插入
    head = Insert(head, 10);
    /*
    调用Insert时:
    - 参数head收到NULL值
    - 函数内创建[10]节点
    - 返回[10]的地址
    - main的head被更新为指向[10]
    */
    /*第二次插入 
    head = Insert(head, 20);
    /*
    调用Insert时:
    - 参数head收到[10]的地址
    - 函数内创建[20]节点，其next指向[10]
    - 返回[20]的地址
    - main的head被更新为指向[20]
    */
//通过引用传递来写
    void Insert(Node** pointertohead,int x)//接受头指针变量本身的地址head 所以叫pointertohead
    //Node*类型直接变成void类型 不需要返回值 这种方式可以直接修改main中的指针
    //通过解引用可以修改外部真正的head指针(main函数中的)
    {
        struct Node* temp=(Node*)malloc(sizeof(Node));
        temp->data=x;
        temp->next=*pointertohead;
        *pointertohead=temp;
    }
    void Print(const Node *head)//值传递 下一个就是引用传递
    {
        cout<<"List is:";
        while(head!=NULL)  //用head本身不用temp
        {
            cout<<head->data;
            head=head->next;
        }
    }
    int main()
    {
        Node *head=NULL;//局部变量 初始化空链表 把头结点的地址作为两个函数的参数
        cout<<"一共有多少数字";
        int n,i,x;//x是要插入的数字
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cout<<"enter the number";
            cin>>x;
            Insert(&head,x);//传递head指针的地址
            Print(head);
        }
    }



//在任意位置插入一个节点
struct Node
{                                
    int data;
    Node* next;
};
Node *head;//全局变量 在static/global处
void Print(){
    Node *temp=head;//一个指向节点的临时指针temp
    while(temp!=NULL){
        printf("%d", temp->data);//打印当前节点指向的数据作用域data
        temp=temp->next;//然后指向下一个指针 继续循环
    }
    printf("\n");
}
void Insert(int data,int n)
{
    Node *temp1=new Node();//创建新节点
    temp1->data=data;
    temp1->next=NULL;
    if(n==1){
        temp1->next=head;//新节点指向原头结点
        head=temp1;//更新头结点为新节点
        return;
    }
    Node *temp2=head;//从头结点开始遍历
    for(int i=0;i<n-2;i++){//运行一个循环 到达第n-1个节点
        temp2=temp2->next;
    }
    //temp1是新创建的节点 temp2是通过循环找到的第n-1个节点
    temp1->next=temp2->next;//新节点指向第n个节点 temp1要插入到temp2之后 所以要temp2指向next
    temp2->next=temp1;//第n-1个节点指向新节点
}
int main()
{
    head=NULL;//empty list
    Insert(2,1);//List:2
    Insert(3,2);//List:2,3
    Insert(4,1);//List:4,2,3
    Insert(5,2);//List:4,5,2,3
    Print();
}


//在任意位置删除一个节点
struct Node{
    int data;
    Node *next;
};
Node *head;//全局变量
void Insert(int data);//在链表末尾插入节点
void Print();
void Delete(int n)//删除在n处的节点
{
    struct Node *temp1=head;
    if(n==1){
        head=temp1->next;//(*temp1).next
        free(temp1);
        return;
    }
    else{
        int i;
        for(i=0;i<n-2;i++){
            temp1=temp1->next;//temp1指向第n-1个节点
            Node *temp2=temp1->next;//temp2指向第n个节点
            temp1->next=temp2->next;//让第n-1个链接 变为连向n+1处链接
            //不能没有temp2 直接想指向n+1 因为只有n处才存有n+1处的地址
        free(temp2);//释放内存 delete temp2;
        }  
    }
}
int main()
{
    head=NULL;//empty List
    Insert(2);
    Insert(4);
    Insert(6);
    Insert(5);//List:2 4 6 5
    int n;
    printf("Enter the position\n");
    scanf("%d",&n);
    Delete(n);
    Print();
}


//翻转一个链表(迭代方式实现)
struct Node
{
    int data;
    Node *next;
};
struct Node *head;
void Reverse()
{
    struct Node *current,*prev,*next;//得用两个指针 prev是previous
    current=head;
    prev=NULL;
    while(current!=NULL)
    {
        next=current->next;
        current->next=prev;//这个next是current的指针域
        prev=current;//往后移
        current=next;//往后移  这个next是指针
    }
    head=prev;//current和next已经指向了NULL
}

//完整的程序
struct Node
{
    int data;
    Node *next;
};
struct Node *head;
struct Node *Reverse(struct Node *head)
{
    struct Node *current,*prev,*next;//得用两个指针 prev是previous
    current=head;
    prev=NULL;
    while(current!=NULL)
    {
        next=current->next;
        current->next=prev;//这个next是current的指针域
        prev=current;//往后移
        current=next;//往后移  这个next是指针
    }
    head=prev;//current和next已经指向了NULL
    return head;
}
Node *Insert(Node *head,int data)//参数必须是指针 指针那块学过的 参数传递
{
    Node*temp=new Node();
    temp->data=data;
    temp->next=NULL;
    if(head==NULL)head=temp;//如果head不是空链表
    else
    {
        Node *temp1=head;
        while(temp1->next!=NULL)temp1=temp1->next;
        temp1->next=temp;
    }
    return head;
}
//temp是新创建的节点 temp1是上一个节点
void Print(Node *head)
{
    while(head!=NULL)
    {
        printf("%d",head->data);
        head=head->next;
    }
}
int main()
{
    struct Node *head=NULL;
    head=Insert(head,2);
    head=Insert(head,4);
    head=Insert(head,6);
    head=Insert(head,8);
    Print(head);
    head=Reverse(head);
    Print(head);
}

//用递归方式倒序链表(不是打印) 就是地址也得跟着变
struct Node
{
    int data;
    Node *next;
};
struct Node *head;
void Reverse(struct Node *p)
{
    if(p->next==NULL)
    {
        head=p;
        return;
    }//exit
    Reverse(p->next);//持续递归
    struct Node *q=p->next;
    q->next=p;
    p->next=NULL;
}

//用递归方式打印链表
struct Node
{
    int data;
    struct Node *next;
};
void Print(struct Node *p)//局部变量*p 递归 自己调用自己
{
    if(p=NULL)return;//到达了列表末尾
    printf("%d",p->data);//正序
    Print(p->next);//递归
}
//逆序做法  比迭代的方法方便的多
void ReversePrint(struct Node *p)
{
    if(p=NULL)return;
    ReversePrint(p->next);
 }//倒序打印 

//双向链表
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;//一个节点三个域
};
struct Node *head;
struct Node *GetNewNode(int x)
{
    Node *newNode=new Node();
    newNode->data=x;
    newNode->prev=NULL;
    newNode->next=NULL;//全都初始化为空值
    return newNode;
}
void InsertAtHead(int x)//当这个函数执行完毕时 这个newNode指针会被自动清除 但是节点本身不会清除
{
    struct Node *newNode=GetNewNode(x);//newNode和上面的不一样 因为newNode是局部变量
    if(head==NULL)
    {
        head=newNode;
        return;
    }
    head->prev=newNode;
    newNode->next=head; 
    head=newNode;
}
void ReversePrint()
{
    struct Node *temp=head;
    if(temp==NULL)return;//empty list,exit
    //Going to the last node
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    //Traversing backward using prev pointer 得先到后面 然后再回来
    printf("Reverse:");
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->prev;
    }
    printf("\n");
}
int main()
{
    head=NULL;
    InsertAtHead(2);Print();ReversePrint();
}