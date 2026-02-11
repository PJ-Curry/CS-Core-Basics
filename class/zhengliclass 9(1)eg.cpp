#include<iostream>
#include<cstdlib>
using namespace std;
struct Student
{
    int id;//学号
    float gpa;
};
template<class T>
class Store//类模版 实现对任意类型数据进行存取
{
private:
    T item;//item用于存放任意类型的数据 比如这个题int float Student都可以
    bool haveValue;//haveValue标记item是否已经被存入内容
public:
    friend T;//将参数类型T声明为友元类
    Store();
    T &getElem();//提取数据函数
    void putElem(const T&x);//存入数据函数
};
template<class T>
Store<T>::Store():haveValue(false){}//第109行 Store是一个模版
template<class T>
T &Store<T>::getElem()
{
    //如果试图提取未初始化的数据，则终止程序
    if(!haveValue)
    {
        cout<<"No item present!"<<endl;
        exit(1);//使程序完全退出，回到操作系统
    }
    return item;//返回item中存放的数据
}
template<class T>
void Store<T>::putElem(const T&x)
{
    //将haveValue设置为true，表示item中已经存入数值
    haveValue=true;//存一个数进去就设置成true
    item=x;//将x的值存入item
}
int main()
{
    using IntStore=Store<int>;/*
    class Store
    {
    private:
        int item;bool haveValue;
    public:
    Store();
    int &getElem();
    void putElem(const int&x);这个是第43行代码调用的IntStore的背后解读 第60行也是如此
    }
    */
    IntStore s1,s2;
    s1.putElem(3);
    s2.putElem(-7);
    cout<<s1.getElem()<<" "<<s2.getElem()<<endl;
    
    Student g={1000,23};
    Store<Student>s3;
    s3.putElem(g);
    cout<<"The student id is"<<s3.getElem().id<<endl;
    
    Store<double> d;//自己设计的一个错误 会报错的！27-30行
    cout<<"Retrieving object D...";
    cout<<d.getElem()<<endl;//根本没存过数字 直接就输出 就会报错
    //d未初始化，执行函数D.getElement()时导致程序终止
    return 0;
}