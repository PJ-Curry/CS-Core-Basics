//后缀表达式计算
#include<iostream>
#include<string>
#include<stack>  
using namespace std;

int main()
{
    string s;
    getline(cin,s);//这个支持空格
    stack<long long> a;
    for(int i=0;i<s.length();i++)
    {
        if(isdigit(s[i]))//这里是重点 我们遇到的是单个数字 有时候处理的是两位数
        {
            int j=i;
            while(j<s.length() && isdigit(s[j])) j++;
            int num=stoi(s.substr(i,j-i));//转换成整数
            a.push(num);
            i=j;//移动下标
        }
        else if(s[i]=='.')
        {
            continue;
        }
        else if(s[i]=='@')
        {
            break;
        }
        else
        {
            long long b=a.top(); a.pop();//pop最上面的数字
            long long x=a.top(); a.pop();//pop第二个数字
            long long res=0;
            if(s[i]=='+') res=x+b;
            else if(s[i]=='-') res=x-b;
            else if(s[i]=='*') res=x*b;
            else if(s[i]=='/') res=x/b;
            a.push(res);
        }
    }
    cout<<a.top()<<endl;
    return 0;
}

//AC！

//用哈希表映射 更优雅 不过没啥意义也
/*
unordered_map<char, function<long long(long long,long long)>> op = {
    {'+', [](long long a, long long b){ return a+b; }},
    {'-', [](long long a, long long b){ return a-b; }},
    {'*', [](long long a, long long b){ return a*b; }},
    {'/', [](long long a, long long b){ return a/b; }}
};

else if(op.count(s[i]))
{
    long long b=st.top();st.pop();
    long long a=st.top();st.pop();
    st.push(op[s[i]](a,b));
    i++;
}
*/