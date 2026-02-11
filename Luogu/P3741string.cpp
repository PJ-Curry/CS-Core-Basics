#include<iostream>
#include<string>
using namespace std;
int main()
{
    int n;
    string s;
    cin>>n;
    cin>>s;
    int count=0;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='V'&&s[i+1]=='K')
        {
            count++;
            s[i]='X';
            s[i+1]='X';
        }
    }
    for(int i=0;i<s.length()-1;i++)
    {
        if(s[i]=='V'&&s[i+1]=='V'){
            s[i+1]='K';
            count++;
            break;
        }
        if(s[i]=='K'&&s[i+1]=='K'){
            s[i]='V';
            count++;
            break;
        }
    }
    cout<<count;
    return 0;
}