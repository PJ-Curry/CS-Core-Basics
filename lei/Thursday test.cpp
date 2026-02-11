#include<iostream>
#include<cstring>
using namespace std;
class Team
{
protected:
char *name;//名称
int win;//胜场次
int draw;//平场次
int lose;//负场次
public:
    Team(const char* n,int w,int d,int l):win(w),draw(d),lose(l)
    {
        name=new char[strlen(n)+1];
        strcpy(name,n);
    }
};
int main()
{

}
