/*全面掌握指针怎么调用函数
第一类：参数成员函数的调用（普通）
class Student
{
public:
    void sayHi()
    {
        cout<<"Hello World!"<<endl;
    }
};
int main()
{
    Student s;
    s.sayHi();//调用成员函数
    return 0;
    和下面这个是等价的 指针方式写的
    Student *p=new Student();//创建对象的指针
    p->sayHi();//调用成员函数
    delete p;//释放内存
}
第二类：带参数的成员函数
class Calculator
{
public:
    int add(int a,int b)
    {
        return a+b;
    }
};
int main()
{
    Calculator c;
    int result=c.add(3,4);//调用成员函数
    cout<<result<<endl;
    return 0;
    下面是与之等价的指针方式
    Calculator *p=new Calculator();//创建对象的指针
    int result=p->add(3,4);//调用成员函数
    cout<<result<<endl;
    delete p;//释放内存
}
// 第三类：带返回值的成员函数
class User
{
public:
    string getName()
    {
        return "John Doe";
    }
};
int main()
{
    User u;
    string name=u.getName();//调用成员函数
    cout<<name<<endl;
    return 0;
    下面是与之等价的指针方式
    User *p=new User();//创建对象的指针
    string name=p->getName();//调用成员函数
    cout<<name<<endl;
    delete p;//释放内存
}
第四类 构造函数+带参数初始化+再调用函数
class Book
{
private:
    string title;
public:
    Book(string t):title(t){}
    void show()
    {
        cout<<"Book title: "<<title<<endl;
    }
};
int main()
{
    Book *b=new Book("C++ Programming");//创建对象的指针并初始化
    b->show();//调用成员函数
    delete b;//释放内存
}
第五类：父类指针指向子类对象（不涉及虚函数）
class Animal
{
public:
    void info()
    {
        cout<<"This is an animal."<<endl;
    }
};
class Dog:public Animal
{
public:
    void Doginfo()  
    {
        cout<<"This is a dog."<<endl;
    }
};
int main()
{
    Animal *a=new Dog();//父类指针指向子类对象
    a->info();//调用父类函数
    // a->Doginfo();//错误：父类指针不能调用子类函数
    delete a;//释放内存
    return 0;
}
第六类：指针访问成员变量（如果public）
class Point
{
public:
    int x,y;
    Point(int a,int b):x(a),y(b){}//构造函数
};
int main()
{
    Point *p=new Point();
    p->set(2,3);
    cout<<p->x<<","<<p->y<<endl;//访问成员变量
    delete p;//释放内存
    return 0;
}

总结：指针调用函数的语法
new 创建 → 指针保存
-> 访问函数 → 参数不怕
有返回值就接住它
析构时别忘 delete 它
*/
