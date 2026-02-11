/*
类的组合
组合的概念
类中的成员是另一个类的对象
可以在已有抽象的基础上实现更复杂的抽象
原则：不仅要负责对本类中的基本类型成员数据初始化，也要对对象成员（别的类的对象）初始化
声明形式；
类名::类名（对象成员所需要的形参，本类成员形参）
    :对象1(参数)，对象2(参数)，......
    {
    //函数体其他语句
    }
初始化次序
首先对构造函数初始化列表中列出的成员(包括基本类型成员和对象成员)进行初始化
初始化次序是成员在类体中定义的次序
成员对象构造函数调用顺序：按对象成员的声明顺序，先声明者先构造
初始化列表中未出现的成员对象，调用用默认的构造函数(即无形参的)初始化
处理完初始化列表之后，再执行构造函数的函数体
例子：线段类
*/
#include<iostream>
#include<cmath>
using namespace std;
class Point
{
public:
    Point(int xx=0,int yy=0)
    {
        x=xx;
        y=yy;
    }
    Point(const Point &p);//上面和下面第38行要一致，有const或者没有const都要一致
    int getX(){return x;}
    int getY(){return y;}
private:
    int x,y;//x，y是私有成员 没法用 所以在33-34行 return了 就获取了x和y的值
};
Point::Point(const Point&p)//复制构造函数在类外定义 传入Point对象p的x和y值复制到当前对象的x和y中
{
    x=p.x;//复制构造函数的逻辑：用另一个对象的值初始化当前对象 当前对象是x，y 之前的就是第6行（p的x和y）
    y=p.y;
    cout<<"Calling the copy constructor"<<endl;//表示复制构造函数被调用
}/*复制另一个Point对象p的x和y值，创建新的point对象 当point对象按值传递或作为另一个对象的成员被复制时，会调用此函数*/
class Line
{
public:
    Line(Point xp1,Point xp2);//构造函数
    Line(Line &l);//复制构造函数
    double getLen(){return len;}
private:
    Point p1,p2;//Line类包含两个Point对象
    double len;//线段的长度
};
Line::Line(Point xp1,Point xp2):p1(xp1),p2(xp2)/*该构造函数接受两个Point对象xp1和xp2 表示使用xp1初始化p1，使用xp2初始化p2*/
{
    cout<<"Calling the copy constructor"<<endl;
    double x=static_cast<double>(p1.getX()-p2.getX());
    double y=static_cast<double>(p1.getY()-p2.getY());
    len=sqrt(x*x+y*y);
}
Line::Line(Line &l):p1(l.p1),p2(l.p2)
{
    cout<<"Calling the copy constructor of Line"<<endl;
    len=l.len;
}
int main()
{
    Point myp1(1,1),myp2(4,5);
    Line line(myp1,myp2);
    Line line2(line);
    cout<<"The length of the line is:";
    cout<<line.getLen()<<endl;
    cout<<"The length of the line2 is:";
    cout<<line2.getLen()<<endl;
    return 0;
}
/*运行结果如下
Calling the copy constructor of Point
Calling the copy constructor of Point
Calling the copy constructor of Point
Calling the copy constructor of Point
Calling constructor of Line
Calling the copy constructor of Point
Calling the copy constructor of Point
Calling the copy constructor of Line
The length of the line is:5
The length of the line2 is:
*/