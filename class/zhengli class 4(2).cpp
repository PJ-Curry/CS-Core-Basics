/*
怎么对对象进行初始化呢？ 答案就是用构造函数
我希望给我们的Clock类初始化为(0,0,0) Clock c(0,0,0) 但是显然编译器不能自己办
在对象被创建时使用特定的值构造对象，将对象初始化为一个特定的初始状态
****重点
1.函数名和类名相同
2.不能定义返回值类型，也不能有return语句
3.可以重载
调用时机：自动调用 只要调用了对象 就一定！会调用构造函数 如果没有定义构造函数 编译器会自己生成一个 不用你管
默认构造函数
{
参数表为空的构造函数
全部参数都有默认值的构造函数
eg.(隐含生成的构造函数)
Clock();
Clock(int newH=0,int newM=0,int newS=0);
两个都是默认构造函数 如果在类中同时出现将会产生编译错误
因为我们在重载函数时候 编译器真的不知道该调用哪个
}
构造函数的实现
Clock(int newH,int newM,int newS) 构造函数 如果写了 编译器就不会管隐含生成的构造函数了
Clock::Clock(int newH,int newM,int newS):hour(newH),minute(newW),second(newS){
}构造函数的视线 初始化列表的形式 GPT也是这个形式
int main()
{
Clock c(0,0,0);这样会自动调用构造函数
}
*/
#include<iostream>
using namespace std;
class Clock
{
public:
Clock()=default;//默认构造函数
Clock(int newH,int newM,int newS);//构造函数
void setTime(int newH=0,int newM=0,int newS=0);//用来设置时间
void showTime();//显示时间的函数
private:
int hour,minute,second;
};
Clock::Clock():hour(0),minute(0),second(0){}//默认构造函数Clock::Clock(int newH,int newM,int newS):hour(newH),minute(newW),second(newS){}
Clock::Clock(int newH,int newM,int newS)//函数的具体实现 当前对象地址this
{/*可以和practice1 做一下对比*/
    hour=newH;//编译器看到的是this->hour 该把他赋值给this指针(编译器知道)
    minute=newM;
    second=newS;
}
void Clock::setTime(int newH,int newM,int newS)
{
    hour=newH;
    minute=newM;
    second=newS;
}
inline void Clock::showTime()
{
    cout<<hour<<":"<<minute<<":"<<second<<endl;
}
int main()
{
    Clock c(6,40,0);//自动调用构造函数
    Clock c2;
    c.showTime();
    return 0;
}
/*
=default 对于已经定义的构造函数，默认情况下编译器就不会再隐含生成默认构造函数
如果还想让编译器隐含生成默认构造函数，可以使用=default 如果不需要就不给你生成 如果需要的话 他还是会自动给你生成 相当于一个保险吧
!委托构造函数
类中往往有很多个构造函数，只是参数表和初始化列表不同，其初始化算法都是相同的，这时候，为了避免代码重复，可以使用委托构造函数
比如上一个题的构造函数和默认构造函数 可以采用委托的方式
原始：
Clock::Clock(int newH,int newM,int newS):hour(newH),minute(newM),second(newS){}构造函数
Clock::Clock():hour(0),minute(0),second(0){}//默认构造函数 41-47行代码
改进:委托构造函数使用类的其他构造函数执行初始化过程
Clock::Clock(int newH,int newM,int newS):hour(newH),minute(newM),second(newS){}
Clock::Clock:Clock(0,0,0){}
!复制构造函数(就是一种特殊的形式)
我们经常会需要用到一个已经存在的对象，去初始化新的对象，这是就需要一种特殊的构造函数——复制构造函数；
隐含生成的复制构造函数可以实现对应数据成员的一一复制
自定义的复制构造函数可以实现特殊的复制功能
形参为本类的对象引用，作用是用一个已经存在的对象去初始化同类型的新对象eg.函数的重载
class 类名
{
public：
    类名(形参)；//构造函数
    类名(const 类名&对象名);//复制构造函数！！！！！！！！！！！so important
};
类名::类(const 类名&对象名)//复制构造函数的实现
{函数体}
有些时候对象不希望被复制构造
C++98做法：将复制构造函数声明为private，明确不提供函数的实现
C++11做法：用"=delete"指示编译器不生成默认复制构造函数
eg：
class Point
{
public:
    Point(int xx=0;int yy=0){x=xx;y=yy;}
    Point(const Point&p)=delete;//指示编译器不生成默认复制构造函数
private:
    int x,y;
};
复制构造函数会被调用的三种情况(important)
1.定义一个对象是，以本类的另一个对象作为初始值，发生复制构造
2.如果函数的形参是类的对象，调用函数时，将使用实参对象形参对象，发生复制构造
3.如果函数的返回值是类的对象，函数执行完成返回主调函数时，将使用return语句中的对象初始化一个临时无名对象
传递给主调函数，此时发生复制构造
这种情况样避免不必要的复制？eg 看对应的cpp zhengli class 4(2)eg.cpp 我自认为是弄懂了的 但是自己写还是不太行

！移动构造
左值和右值
对持久存在的变量的引用成为左值引用 用&表示
对短暂存在可被移动的右值的引用成为右值引用 用&&表示
float n=6;
float &lr_n=n;左值引用
float &&rr_n;错误 右值引用不能绑定到左值
float&&rr_n=n*n;//右值表达式绑定到右值引用（右值用于移动构造）
通过标准库<utility>中的move函数可以将左值对象移动为右值
float n=10;
float &&rr_n=std::move(n);//将n转化为右值
基于右值的引用，移动构造函数通过移动数据的方式构造新对象，与复制构造函数类似，移动构造函数参数为该类对象的右值引用 eg：
*/
#include<utility>
class astring
{
public:
std::string s;
astring(astring&& o)noexcept:s(std::move(o.s))//显示移动所有成员 强行初始化s
{
    //函数体
}
};
/*移动构造函数不分配新的内存，理论上不会报错，为了配合异常捕获机制，需要声明noexcept表明不会抛出异常
被移动的对象不应再被使用，需要销毁或重新赋值
析构函数！！负责出生登记 和善后处理
完成对象被删除前的一些清理工作
在对象的生存期结束的时刻系统自动调用它，然后再释放次对象所属的空间
*/