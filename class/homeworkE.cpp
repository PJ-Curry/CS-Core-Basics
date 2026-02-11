#include<iostream>
#include<cmath>
using namespace std;
class Distance
{
public:
    Distance(int xx1=0,int yy1=0,int xx2=0,int yy2=0)
    {
        x1=xx1;
        y1=yy1;
        x2=xx2;
        y2=yy2;
    }
    Distance(const Distance &p);
    int getX1(){return x1;}
    int getY1(){return y1;}
    int getX2(){return x2;}
    int getY2(){return y2;}
    virtual double calculateDistance()const=0;//纯虚函数
    virtual ~Distance(){};
protected://能被派生子类访问用protected 不允许外部代码访问
int x1,y1,x2,y2;//坐标
};
class Manhaton:public Distance
{
public:
Manhaton(int xx1,int yy1,int xx2,int yy2):Distance(xx1,yy1,xx2,yy2){}//目的是用xx1,xx2,yy1,yy2来初始化基类Distance
/*冒号之前叫构造函数，冒号后面叫成员初始化列表，它调用基类Distance的构造函数，用于传入的四个参数进行初始化*/
double calculateDistance()const override//override是关键字 用于标记派生类中的成员函数，表明这个函数是重写（覆盖）了基类中的函数
/*作用：正确匹配虚函数，比如calculateDistance函数发生了变化 编译器会提示错误，防止拼写错误 只是一个检查机制*/
{
    return abs(x1-x2)+abs(y1-y2);
}
};
class Euclidean:public Distance//欧几里得
{
public:
Euclidean(int xx1,int yy1,int xx2,int yy2):Distance(xx1,yy1,xx2,yy2){}
double calculateDistance()const override
{
    return pow(x1-x2,2)+pow(y1-y2,2);//背下来吧
}
};
int main()
{
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    Distance *dist1=new Manhaton(x1,y1,x2,y2);//这就是main函数里用指针 指针动态联编的方式来调用
    Distance *dist2=new Euclidean(x1,y1,x2,y2);//语法 父类类型*指针名=new 子类对象      指针名->成员函数();
    cout<<dist1->calculateDistance()<<" "<<dist2->calculateDistance();
    delete dist1;
    delete dist2;
    return 0;
}
/*
纯虚函数的特点
1.无法直接实例化包含纯虚函数的类(抽象类)，必须由派生类实现所有纯虚函数后，才能创建对象
2.子类必须重写 纯虚函数，否则子类仍然是抽象类，无法实例化
*/