/*#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main()
{
    string s;
    cin>>s;

    stack<char> work;
    stack<char> result;

    for(char c:s)
    {
        if(c=='('||c=='[')
        {
            work.push(c); 
        }
        else if(c==')')
        {
            if(!work.empty()&&work.top()=='(')
            {
                result.push(')');
                result.push(work.top());
                work.pop();
            }
            else
            {
                result.push(')');
                result.push('(');
            }
        }
        else if(c==']')
        {
            if(!work.empty()&&work.top()=='[')
            {
                result.push(']');
                result.push(work.top());
                work.pop();
            }
            else
            {
                result.push(']');
                result.push('[');
            }
        }
    }
    

    //现在讨论work栈里没有配对成功的
    while(!work.empty())
    {
        if(work.top()=='(')
        {
            result.push(')');
            result.push('(');
        }
        else
        {
            result.push(']');
            result.push('[');
        }
        work.pop();
    }
    
    string ans;
    while(!result.empty())
    {
        ans.push_back(result.top());
        result.pop();
    }
    cout<<ans;
    return 0;
}*/
//搞两个栈 一个栈存放所有左括号 一个栈存放所有左括号出现的位置 一个数组存放匹配的结果 匹配成功则为空格
/*
使用 s[] 和 w[] 模拟栈：
s[top] 保存括号字符；
w[top] 保存该括号对应的下标。
对每个字符：
如果是 ( 或 [：
压栈，同时在 c[i] 中存放预期匹配的符号 ) 或 ]
如果是 )：
栈顶若是 (：匹配成功，清空对应位置 c[w[top]]，弹栈
否则：说明不匹配，需要补一个 '('，记录到 c[i]
如果是 ]：逻辑类似。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

int top,w[110];//保存括号对应字符串的下标
string a;
char s[110],c[110];
int main()
{
    cin>>a;
    int n=a.length();
    for(int i=0;i<n;i++)
    {
        if(a[i]=='('||a[i]=='[')
        {
            s[++top]=a[i];
            w[top]=i;
            if(a[i]=='(')  c[i]=')';
            else c[i]=']';
        }
        if(a[i]==')')
        {
            if(top&&s[top]=='(')
            {
                c[w[top]]=' ';
                top--;
            }
            else c[i]='(';
        }
        if(a[i]==']')
        {
            if(top&&s[top]=='[')
            {
                c[w[top]]=' ';
                top--;                
            }
            else c[i]='[';
        }
    }
    for(int i=0;i<n;i++)
    {
		if(c[i] == '(' || c[i] == '[')      printf("%c%c",c[i],a[i]);
		else if(c[i] == ')' || c[i] == ']') printf("%c%c",a[i],c[i]);
		else                                printf("%c",a[i]);
	}
//	fclose(stdin);fclose(stdout);
	return 0;
}


//崔迪写的
#include<iostream>
#include<string>
using namespace std;

class st
{
public:
    bool rl;//1为左，0为右
    bool xiao;//1为小，0为中
    bool isP=false;//1是配对，0是未
    char s;
    void moren()
    {
        if(s=='['||s=='(') rl=1;
        else rl=0;

        if(s=='['||s==']') xiao =0;
        else xiao=1;
    }
};

class shuzu
{
public:
    shuzu(int n)
    {
        Stu= new st[n];
        len=n;
    }
    int len;
    st *Stu;
};

void pipei(string S)
{
    int length = S.length();
    shuzu shili(length);

    for(int i=0;i<length;i++)
    {
        shili.Stu[i].s=S[i];
        shili.Stu[i].moren();
        if(!shili.Stu[i].rl)//如果是右括号
        {
            for(int j=i-1;j>=0;j--)
            {
                if(shili.Stu[j].rl&&!shili.Stu[j].isP)
                {//一左一右，左是未配对，大小匹配
                    if(shili.Stu[j].xiao==shili.Stu[i].xiao)
                    {
                        shili.Stu[j].isP=1;
                        shili.Stu[i].isP=1;
                    }
                    break;
                }    
            }
        }
    }
    for(int i=0;i<length;i++)
    {
        if(shili.Stu[i].isP)
        {
            cout<<shili.Stu[i].s;
        }
        else
        {
            if(shili.Stu[i].xiao)
            {
                cout<<"()";
            }                
            else
            {
                cout<<"[]";
            }
        }
    }
}

int main()
{
    string S;
    cin>>S;
    pipei(S);
}