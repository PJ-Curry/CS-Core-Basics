#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>
class MySorter//类模版 实现对任意类型数据进行存取
{
private:
    vector<T> data;
public:
    void add(T val);//添加数据
    void sortData();//排序函数
    void printData();//打印函数
};//以下全都是类外函数部分 函数在类外定义都要重新声明模版参数，而且不能直接访问data 9(1) Line108-109每一个函数都要这个模版template<typename T>    返回类型 类名<T>::函数名(){}
template<typename T>
void MySorter<T>::add(T val)//添加数据函数
{
    data.push_back(val);//将val添加到data中
}
template<typename T>
void MySorter<T>::sortData()//排序函数
{
    sort(data.begin(), data.end());
}
template<typename T>
void MySorter<T>::printData()
{
    for(auto const&val:data)
    {
        cout<<val<<" ";
    }
    cout<<endl;
}
int main()
{
    MySorter<int>intsorter;
    MySorter<char>charsorter;
    MySorter<string>stringsorter;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        intsorter.add(temp);
    }
    cin>>n;
    for(int i=0;i<n;i++)
    {
        char temp;
        cin>>temp;
        charsorter.add(temp);
    }
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string temp;
        cin>>temp;
        stringsorter.add(temp);
    }//以上全都是添加 后面还有排序和输出
    intsorter.sortData();
    intsorter.printData();
    charsorter.sortData();
    charsorter.printData();
    stringsorter.sortData();
    stringsorter.printData();
    return 0;
}/*
总结一下函数调用的方法
1.普通函数的调用
void sayHello()
{
    cout<<"Hello World!"<<endl;
}
int main()
{
    sayHello();//调用函数
    return 0;
}
2.类的成员函数的调用
class Student
{
public:
    void sayHello()
    {
        cout<<"Hello World!"<<endl;
    }
};
int main()
{
    Student s;//创建对象s
    s.sayHello();//调用成员函数
    return 0;
}
2.2成员函数有参数
class Dog
{
public:
    void bark(string name)
    {
        cout<<name<<" is barking!"<<endl;
    }
};
int main()
{
    Dog d;//创建对象d
    d.bark("Tommy");//调用成员函数
    return 0;
}
3.模版类对象创建
template<typename T>
class Box
{
public:
    T value;成员变量 类型是模版参数T 当我创建Box<int> 这里是int value;创建Box<string>时 这里是string value
    Box(T v){value=v;}
    void show()
    {
        cout<<value<<endl;
    }
};
int main()
{
    Box<int> b1(10);//创建int类型的Box对象 这里的创建对象就稍微稍微稍微复杂了一些
    Box<string> b2("Hello");//创建string类型的Box对象
    b1.show();//调用show函数
    b2.show();//调用show函数
    return 0;
}
*/