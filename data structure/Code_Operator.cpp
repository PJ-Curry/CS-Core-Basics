#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

//STL里默认的比较器 less<T>升序(小的在前面) greater<T>降序(大的在前面)
int main()
{
    vector<int>v;
    sort(v.begin(),v.end(),less<int>());
    sort(v.begin(),v.end(),greater<int>());

    //大根堆(默认)
    priority_queue<int,vector<int>,less<int>> pq;
    //小根堆
    priority_queue<int,vector<int>,greater<int>> pq;
}

//自定义结构的比较器
struct Student
{
    string name;
    int age;
    int score;
};
struct Cmp
{
    bool operator()(const Student& a,const Student& b)const
    {
        //Compare(a,b)==true 表示a比b差 a优先级始终低于b
        if(a.score!=b.score) return a.score<b.score;
        return a.age>b.age;//自己实现分类比较
    }
};
priority_queue<Student, vector<Student>,Cmp> pq;//这个里面就自动包括了 比较器Cmp 其中Cmp重载了operator()


//sort的比较器
vector<Student>v={{"Tom",20,85},{"Jack",21,90},{"Lucy",19,90}};
//sort比较器要求:返回true 表示a应该排在b之前
sort(v.begin(),v.end(),[](const Student& a,const Student& b){
    if(a.score!=b.score) return a.score>b.score;
    return a.age<b.age;
});

//运算符重载
struct student
{
    string name;
    int age;
    int score;

    bool operator<(const student& other)const{
        if(score!=other.score) return score<other.score;
        return age>other.age;
    }
};
priority_queue<Student>pq;

