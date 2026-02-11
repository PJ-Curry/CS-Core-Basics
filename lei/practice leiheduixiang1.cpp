#include<iostream>
using namespace std;
class Rectangle
{
private:
int length;//长
int width;//宽
public:
int value;
Rectangle(int l,int w)
{
    length=l;
    width=w;
}
Rectangle(const Rectangle &rect)//我们创建的这个东西叫构造函数 不能有返回值 void都不能写
/*名字必须和类名相同 用于初始化对象*/
{
     value=rect.length*rect.width;
}
Rectangle(const Rectangle &rect,int)//要用int补位
/*在C++里函数（包括构造函数）都可以重载，但是不能有相同的参数列表 否则编译器将会无法区分*/
{
     value=2*(rect.length+rect.width);
}
/*暴露成员变量的操作 但是并不建议暴露 所以标绿
int getLength(){return length;}
int getWidth(){return width;}
*/
};
int main()
{
    int len,wid;
    cin>>len>>wid;
    Rectangle m(len,wid);
    Rectangle area(m);//能够直接识别出来这个是面积不是因为名字起的好 而是参数和上面的构造函数有对应关系
    Rectangle perimeter(m,0);//这个(m,0)就是很好的对应了类中的参数 所以可以识别成功
    cout<<area.value<<endl;
    cout<<perimeter.value<<endl;
    return 0;
}