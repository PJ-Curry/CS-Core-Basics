//这个赋值不是只考虑等号后面的就行 因为abc可以多次赋值  要的是最终的结果
//重新做 真是一道好题
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int v[3]={0,0,0};
    for(int i=0;i<s.size();)//continue是跳出本次循环 进入下一轮 break是终止整个循环
    {
        if(s[i]!='a'&&s[i]!='b'&&s[i]!='c')
        {
            i++;
            continue;
        }
        int var=s[i]-'a';//判断目前检索到的abc是哪个
        i+=3;
        if(s[i]>='0'&&s[i]<='9')
        {
            v[var]=s[i]-'0';
        }
        else
        {
            v[var]=v[s[i]-'a'];
            //间接赋值 传递其他字母的值 让数组两个相等
            //题目的意思是赋值 不是输出字母 这相当于给数组赋值 这种语言只有abc
        }
        i+=2;
    }
    cout<<v[0]<<" "<<v[1]<<" "<<v[2];
    return 0;
}
//一切都要从原始的abc开始 然后往下递增 找 找到一个数字就向下递增两个回到原始的abc中的任何一个(因为这个赋值可以是很多次 不止有三次abc)
//创建一个存储结果的数组也是关键 第26行是最关键的