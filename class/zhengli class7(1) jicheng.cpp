/*
继承和派生
保持已有类的特性而构造新类的过程成为继承
在已有类的基础上新增自己的特性而产生新类的过程称为派生
直接参与派生出某类的基类成为直接基类
基类的基类甚至更高层的基类成为间接基类
继承的目的：实现设计与代码的重用
派生的目的：当心的问题出现，原有程序无法解决，还要再改改，直接继承类 然后增加或改造
派生类的定义
单继承时
class 派生类名：继承方式 基类名
{
成员声明;
}
class Derived:public Base
{
public:
    Derived();
    ~Derived();
};
多继承时
class 派生类名:继承方式1 基类名1，继承方式2 基类名2，...
{
    成员声明;
}注意 每一个继承方式 只用于限制对紧随其后之基类的继承 例如
class Derived:public Base1,private Base2
{
public:
    Derived();
    ~Derived();
};
派生类的构成
1.吸收基类成员
2.改造基类成员
如果派生类声明了一个和某基类成员同名的新成员，派生的新成员就隐藏或覆盖了外层同名成员
3.添加新的成员
派生类增加新成员使派生类在功能上有所发展
不同继承方式以及成员的访问控制
——————不同继承方式的影响主要体现在：
派生类成员对基类成员的访问权限
通过派生类对象对基类成员的访问权限
三种继承方式
公有继承 私有继承 保护继承
——公有继承
基类的public和protected成员的访问属性在派生类中保持不变，但是基类的private成员不可以直接访问
派生类中的成员函数可以直接访问基类中的public和protected成员，但是不能直接访问基类的private成员
通过派生类的对象访问从基类集成的成员，只能访问public成员
*/
#include<iostream>
#include<cmath>
using namespace std;
class Point
{
public:
void initPoint(float x=0,float y=0)
{
    {
        this->x=x;this->y=y;//这个是初始化 没用复制构造函数 老师说这个复制构造函数在继承的时候很麻烦
    }
}
void move(float offX,float offY)
{
    x+=offX;y+=offY;//这是点可以移动
}
float getX()const{return x;}
float getY()const{return y;}
private:
    float x,y;
};
class Rectangle:public Point
{
public:
    void initRectangle(float x,float y,float w,float h)//这是直接继承过来的initPoint函数
    {
        initPoint(x,y);//调用基类共有成员函数
        this->w=w;
        this->h=h;
    }
    float getH()const{return h;}
    float getW()const{return w;}
private://新增私有数据成员
    float w,h;//宽和高
};
int main()
{
    Rectangle rect;//定义Rectangle类的对象
    //设置矩形的数据
    rect.initRectangle(2,3,20,10);
    rect.move(3,2);//移动矩形的位置
    cout<<rect.getX()<<endl;
    cout<<rect.getY()<<endl;
    cout<<rect.getW()<<endl;
    cout<<rect.getH()<<endl;
    return 0;
}
/*
保护成员protected
对建立其所在类对象的模块来说，它与private成员的性质相同       相当于横向纵向两方面来看
对于其派生类来说，它与public成员的性质相同
既实现了数据隐藏，又方便继承，实现代码重用
class A
{
protected:
int x;
};
class B:public A
{
public:
    void function();
};
void B::function()
{
    x=5;//正确
}
*/
/*
私有继承
基类的public和protected成员都以private身份出现在派生类中，但是基类的private成员不可以被直接访问
派生类中的成员函数可以直接访问基类中的public和protected成员，但是不能直接访问基类的private成员
通过派生类的对象不能直接访问从基类继承的任何成员
*/
/*
保护继承
基类的public和protected成员都以protected身份出现在派生类中，但是基类的private成员不可以被直接访问
派生类中的成员函数可以直接访问基类中的public和protected成员，但是不能直接访问基类的private成员
通过派生类的对象不能直接访问从基类继承的任何成员
——多继承
就是能继承很多类 但以后会有问题
*/