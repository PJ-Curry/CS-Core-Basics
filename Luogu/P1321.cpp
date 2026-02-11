#include<iostream>//这个题不要想复杂 就是一个或的关系 不需要找到了再用x覆盖
#include<string>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int boy=0;
    int girl=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='b'||s[i+1]=='o'||s[i+2]=='y') boy++;
        if(s[i]=='g'||s[i+1]=='i'||s[i+2]=='r'||s[i+3]=='l') girl++;
    }
    cout<<boy<<endl<<girl;
    return 0;
}