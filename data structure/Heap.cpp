#include<iostream>
using namespace std;
void HeapInsert(int arr[],int index)//实现大根堆 比大小交换父子节点
{
    while(arr[index]>arr[(index-1)/2])
    {
        swap(arr,index,(index-1)/2);
        index=(index-1)/2;
    }
}

//删除大根堆中的最大值 还使得新树也是大根堆
//删掉最大值 把整个树中的最小值放进去 然后和子节点递归交换 直到最底层
void heapify(int arr[],int index,int heapSize)//heapSize来管左孩子右孩子的越界情况
{
    int left=index * 2 + 1;//左孩子的下标
    while(left<heapSize)//孩子还存在
    {
        int largest = left + 1 < heapSize && arr[left+1] > arr[left] ? left+1:left;
        largest=arr[largest]>arr[index]?largest:index;//比较父子
        //index是父
        if(largest==index)
        {
            break;
        }
        swap(arr,largest,index);
        index=largest;
        left=index*2+1;
    }
}
//HeapInsert和heapify是相反的操作 

void swap(int arr[],int i,int j)
{
    int tmp=arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}

/*在这个heapsize范围内[0,heapsize-1] 将第i个位置数字改掉 如何保证 这组数据还满足堆结构
看arr[i]位置是比原来大了还是小了 变小了就heapify 变大了就HeapInsert
这两个函数就是最重要的
*/

//堆排序
void Heapsort(int arr[],int heapsize)
{
    for(int i=0;i<heapsize;i++)
    {
        HeapInsert(arr,i);
    }

    /*for(int i=heapsize-1;i>=0;i--)
    {
        heapify(arr,i,heapsize);
    }*/

    swap(arr,0,--heapsize);//交换之后得删掉后面的
    while(heapsize>1)//O(n) 建堆过程 用错位相减法 T(n)=n/2*1+n/4*2+n/8*3+...
    {
        heapify(arr,0,heapsize);//O(logn)
        swap(arr,0,--heapsize);//O(1)
    }
}

//一个几乎有序的数组 几乎有序：如果把数组排好顺序的话，每个元素移动的距离不超过k k远小于n
//eg k=6 在0-6 7个数字里 创建小根堆 说明从7开始的数字 不会有能在0位置的 实现小根堆之后移除0 push进去7 然后循环O(n*logk) O(n)
#include<queue>
#include<vector>
void  demoHeapDescending()
{
    priority_queue<int,vector<int>,greater<int>> heap;//priority_queue默认是大根堆 然后greater<int>变成小根堆
    heap.push(8);
    heap.push(4);
    heap.push(4);
    heap.push(9);
    heap.push(10);
    heap.push(3);
    while(!heap.empty())
    {
        cout<<heap.top()<<" ";
        heap.pop();
    }
    cout<<endl;
}
//这个是黑盒 下面要写的是算法实现(针对所有数组)
//有些情况下 我们要手写堆 才会变得高效 黑盒堆结构 在里面调整数据的代价太大了
void sortedArrDistanceLessK(vector<int>&arr,int k)
{
    int n=(int)arr.size();
    if(n<=1||k<=0) return;

    //小根堆
    priority_queue<int,vector<int>,greater<int>> minHeap;
    
    //1) 先把k+1个元素放进堆
    int i=0;//读指针
    int out=0;//写指针 写已经排好序的元素的下标
    int first=min(k+1,n);
    for(;i<first;++i)//把k+1个元素放入堆
    {
        minHeap.push(arr[i]);
    }
    for(;i<n;i++)//边读边写
    {
        arr[out++]=minHeap.top();
        minHeap.pop();
        minHeap.push(arr[i]);//读指针继续往前走
    }

    while(!minHeap.empty())//把剩余的元素 全都弹出
    {
        arr[out++]=minHeap.top();
        minHeap.pop();
    }
}