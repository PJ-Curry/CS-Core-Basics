#include<iostream>
using namespace std;
class Rational
{
private:
int numerator;//分子
int denominator;//分母
friend Rational operator*(const Rational &other);//这个都是后加上去的
friend Rational operator/(const Rational &lhs, const Rational &rhs);
int gcd(int a,int b)
{
    while(b!=0)
    {
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}
void simplify()//分数化简操作
{
    int gcd_val=gcd(numerator,denominator);
    numerator/=gcd_val;
    denominator/=gcd_val;
    if(denominator<0)
    {
        numerator=-numerator;//把负号要移动到分子上 这样输出也好看
        denominator=-denominator;
    }
}
public:
Rational(int num=0,int den=1)
{
    numerator=num;
    denominator=den;
    simplify();
}//设置默认参数 0和1
Rational operator+(const Rational &other)const//这个不叫构造函数 这个叫运算符重载函数和练习题1不同
{
    int new_numerator=numerator*other.denominator+denominator*other.numerator;
    int new_denominator=denominator*other.denominator;
    Rational result(new_numerator,new_denominator);
    result.simplify();
    return result;
}
Rational operator-(const Rational &other)const
{
    int new_numerator=numerator*other.denominator-denominator*other.numerator;
    int new_denominator=denominator*other.denominator;
    Rational result(new_numerator,new_denominator);
    result.simplify();
    return result;
}
friend Rational operator*(const Rational &lhs,const Rational &rhs)//友元函数不能直接访问私有成员 我们需要在类中声明
{
    int new_numerator=lhs.numerator*rhs.numerator;
    int new_denominator=lhs.denominator*rhs.denominator;
    Rational result(new_numerator,new_denominator);
    result.simplify();
    return result;
}
friend Rational operator/(const Rational &lhs,const Rational &rhs)
{
        int new_numerator = lhs.numerator * rhs.denominator;
        int new_denominator = lhs.denominator * rhs.numerator;
        Rational result(new_numerator, new_denominator);
        result.simplify();
        return result;
}
Rational operator++(int)//这是自己对自己的操作
{
      Rational temp=*this;//this指向调用该函数的对象 指向执行++操作的Rational对象
      /*  temp是*this的拷贝，储存调用对象的原始值，保证在++之前的值被正常返回，this所指向的对象可以继续被修改 */
      numerator+=denominator;
      simplify();
      return temp;//返回原来的值
}
Rational &operator=(const Rational &other)//需要接受另一个对象来作为参数 所以括号里面是要有东西的
{
    if(this!=&other)
    {
        numerator=other.numerator;//赋值分子
        denominator=other.denominator;//赋值分母
        simplify();
    }
    return *this;//返回当前对象引用 ！！！多看看这个函数
}
friend ostream&operator<<(ostream &out,const Rational &r)
/*这个操作和刚才赋值=的运算的区别很重要 区别在于=主要用于对象的赋值操作 输出
运算符主要用于输出对象的内容，不会改变对象本身的状态，就是单纯的输出*/
{
    if(r.denominator==1)
    {
        out<<r.numerator;
    }
    else
    {
        out<<r.numerator<<"/"<<r.denominator;
    }
    return out;//注意细节
}
int getNumerator()const{return numerator;}//常函数 合理
int getDenominator()const{return denominator;}
};
int main()
{
    int num1,den1,num2,den2;
    cin>>num1>>den1;
    cin>>num2>>den2;
    Rational r1(num1,den1);
    Rational r2(num2,den2);
    Rational result=r1+r2;
    cout<<result<<endl;
    result=r1-r2;
    cout<<result<<endl;
    result=r1*r2;
    cout<<result<<endl;
    result=r1/r2;
    cout<<result<<endl;
    Rational r1_copy=r1;
    Rational r2_copy=r2;
    r1_copy++;
    r2_copy++;
    cout<<r1_copy<<" "<<r2_copy<<endl;
    Rational r3(r1.getDenominator(),r1.getNumerator());
    Rational r4(r2.getDenominator(),r2.getNumerator());
    cout<<r3<<" "<<r4<<endl;
    return 0;
}