#include<iostream>//一个point类来让自己更好的理解一下复制构造函数
using namespace std;
class Point
{
public:
    Point(int xx=0,int yy=0){x=xx;y=yy;}//构造函数(内联)这是一个带默认参数的构造函数，用于初始化Point对象的x和y成员变量
    Point(const Point&p);//复制构造函数 通过一个已经存在的Point对象来初始化一个新的Point对象。
    //它接受一个Point对象的引用作为参数，并将该对象的x和y复制到新对象中
    void setX(int xx){x=xx;}//成员函数 用于设置x和y的值
    void setY(int yy){y=yy;}
    int getX()const{return x;}//常函数 被声明为const 说明他们不会修改对象的状态
    int getY()const{return y;}//用于获取x和y的值
private:
    int x,y;
};//复制构造函数的实现 第四章看不出来有啥用 后面比如动态内存分配会用到
Point::Point(const Point&p)//复制构造函数在类外定义 传入Point对象p的x和y值复制到当前对象的x和y中
{
    x=p.x;//复制构造函数的逻辑：用另一个对象的值初始化当前对象 当前对象是x，y 之前的就是第6行（p的x和y）
    y=p.y;
    cout<<"Calling the copy constructor"<<endl;//表示复制构造函数被调用
}//很有挑衅意味
void fun1(Point p)
{
    cout<<p.getX()<<endl;
}
Point fun2()
{
    Point a(1,2);
    return a;
}
int main()
{
    Point a(4,5);
    Point b(a);//把a的值复制给b 然后他就会返回到16-21行
    cout<<b.getX()<<endl;
    fun1(b);//对象b作为fun1的实参传递 此时会调用复制构造函数来创建b的副本
    b=fun2();//函数的返回值是类对象
    cout<<b.getX()<<endl;
    return 0;
}

/*
最后的输出结果会是
Calling the copy constructor
4
Calling the copy constructor
4
Calling the copy constructor
1
这个例题很好的举例了上课所提到的三种会调用复制构造函数的情况 调用时机
1.33-34行 属于显式的用另一个对象初始化新对象
2.22行 将对象作为参数传递给函数(按值传递)因为cout是get函数 那个函数是一个常函数
3.26-30行 从函数返回对象(按值返回) 和1没啥区别 就是多了一个函数 返回了一下 显得比较高级
为什么需要他
deepseek告诉我们
1.实现深拷贝
2.控制对象的复制行为
*/