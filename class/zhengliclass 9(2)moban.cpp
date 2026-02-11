/*
线性群体 数组类模版vector
群体的概念
分为线性群体和非线性群体 直接访问和顺序访问
#ifndef ARRAY_H
#define ARRAY_H
#inlucde<cassert>
template<class T>//数组类模版定义
class Array
{
private:
    T* list;//用于存放动态分配的数组内存首地址
    int size;//数组大小（元素个数）
public:
    Array(int sz=50);//构造函数
    Array(const Array<T>& a);//复制构造函数
    ~Array();//析构函数
    Array<T>&operator=(const Array<T>& rhs);//赋值运算符重载=
    T& operator[](int i);//下标运算符重载[]
    const T& operator[](int i) const;//下标运算符重载[] const版本
    operator T*();//类型转换运算符重载
    operator const T*() const;//类型转换运算符重载const版本
    int getSize() const;//返回数组大小
    void resize(int sz);//修改数组大小
};
template<class T>Array<T>::Array(int sz):size(sz)//构造函数
{
    assert(sz>0);//如果sz<=0则终止程序
    list=new T[size];//动态分配数组内存
}
*/