#include<iostream>
using namespace std;
template<class T>
class LinearList
{
public:
    LinearList(int MaxListSize=10);//构造函数
    ~LinearList(){delete []element;}
    bool IsEmpty()const{return length==0;}
    int Length()const{return length;}
    bool Find(int k,T& x)const;//返回列表中的第k个元素
    int Search(const T& x)const;//返回x的位置
    LinearList<T>&Delete(int k,T& x);//删除第k个元素，将其保存在x中
    LinearList<T>&Insert(int k,const T& x)//在第k个元素后插入x
    void Output(ostream& out)const;
private:
    int length;
    int Maxsize;
    T* element;//一维动态数组
};
