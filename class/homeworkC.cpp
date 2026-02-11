#include<iostream>
#include<string>
using namespace std;
template <class T>
void Print(T*p, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << p[i]<<" ";
    }
}
template<class T>
void GtLever(T *p,int n,T lever)
{
    T *temp=new T[n];//动态分配内存 创建临时数组
    int k=0;//用于记录当前收集了多少个元素
    for(int i=0;i<n;i++)
    {
        if(p[i]>lever)
        {
            temp[k++]=p[i];//将大于lever的元素存入临时数组 属于先赋值再++
        }
    }
    Print(temp,k);//输出大于lever的部分
    delete[] temp;//释放临时数组的内存
}
template<class T>
void run(int total,int check)
{
    T *arr=new T[total];
    for(int i=0;i<total;i++)
    {
        cin>>arr[i];
    }
    T lever;
    cin>>lever;
    GtLever(arr,check,lever);//调用GtLever函数 这里一环套着一环 check内部调用GtLever函数后还会自动调用Print缩小范围
    delete[] arr;
}
int main()
{
    int total,check;
    string type;
    cin>>type>>total>>check;
    if(type=="int")
    {
        run<int>(total,check);
    }
    else if(type=="float")
    {
        run<float>(total,check);
    }
    else if(type=="char")
    {
        run<char>(total,check);
    }
    return 0;
}