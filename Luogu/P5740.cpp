#include<iostream>
#include<string>
using namespace std;
struct student
{
    string name;
    int math,english,chinese;
    int total(){return math+english+chinese;}
};