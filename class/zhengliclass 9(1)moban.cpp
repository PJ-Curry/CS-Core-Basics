/*
函数模版
问题：整数类型和浮点数类型求绝对值的算法，要不要重载函数 eg：
int abs(int x)
{
    return x<0?-x:x;
}
double abs(double x)
{
    return x<0?-x:x;
}
很显然这样是很麻烦的 解决问题的方式 运用函数模版
创建一个通用功能的函数
支持多种不同的形参
简化重载函数的函数体设计
template<typename T>   typename是类型参数 数据类型也可以定制
T abs(T x)
{
    return x<0?-x:x;
}
int main()
{
    int n=-5;
    double d=-5.5;
    cout<<abs(n)<<endl;  
    cout<<abs(d)<<endl;   我们调用的实际上是double abs(double x)
    return 0;
}
语法形式
template<模版参数表>
函数定义
模版参数表的内容
类型参数：class(或者typename)标识符
常量参数：类型说明符 标识符
模版参数：template<参数表>class标识符
eg：
#include<iostream>
using namespace std;
template<class T>   typename T也可以
void outputArray(const T*array,int count)以指针类型作为抽象类型
{
   for(int i=0;i<count;i++)
   {
       cout<<array[i]<<" ";重载了流运算符"<<"
   }
    cout<<endl;
}
补充 对于运算符到底要不要重载的讨论
当我们使用自定义类/结构体 自定义容器比如Myvector时候需要重载 而且必须重载
用C风格数组 int arr[5] STL容器 可以直接for循环就比如上面的小例子 然后基本数据类型直接cout
因为标准库已经提供了<<支持 所以不用再重载啦
典型场景例子 自定义类
class Person
{
    string name;
    int age;
public:
    Person(string n,int a):name(n),age(a){}
    friend ostream&operator(ostream& os,const Person& p)
    {
        os<<"Name:"<<p.name<<",Age"<<p.age;
        return os;
    }
};
int main()
{
    Person p("Alice",25);
    cout<<p;
    return 0; 
}
自定义容器 如动态数组和链表
template <typename T>
class MyVector
{
    T* data;
    int size;
public:
    // ... 其他代码 ...
    friend ostream& operator<<(ostream& os, const MyVector<T>& vec)
    {
        for (int i = 0; i < vec.size; i++) 
        {
            os << vec.data[i] << " ";
        }
        return os;//返回ostream&是为了支持链式调用
    }
};
int main() 
{
    MyVector<int> vec = {1, 2, 3};
    cout << vec;  // 输出：1 2 3
    return 0;
}
一个函数模版并非自动可以处理所有类型的数据
只有能够进行函数模版中运算的类型，可以作为类型实参
自定义的类，需要重载模版中的运算符，才能作为类型实参 就是上面的例子



！！！！！！！！类模版
使用类模版使用户可以为类声明的一种形式，使得类中的某些数据成员，某些成员函数的参数
某些成员函数的返回值，能取任意类型(包括基本类型和用户自定义类型)
类模版的声明！！！
template<模版参数表>
class 类名（类模版名）
(类成员声明);
如果需要在类模版以外定义其成员函数，可以采用一下形式
template<模版参数表>
类型名 类名<模版参数标识符列表>::函数名(参数表)
模版参数表中的参数可以声明为该模版类的友元类
可以通过typedef或者using对实例化的类模版定义别名
模版的默认实参
类似于函数形参可以有默认实参 函数/类模版也有默认模版实参
template<typename T=double>
class Point
{
public:
    Point(T_x=0,T_y=0):x(_x),y(_y){}
private:
    T x;
    T y;
};
使用模版
Point<int>point();给定模版参数int，定义整数点对象（0,0）
Point<>point();
*/