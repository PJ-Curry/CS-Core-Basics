#include<iostream>
using namespace std;
//中缀变后缀的伪代码
//InfixToPostfix(exp)
{
    create a stack s
    res <- empty string
    for(i<-0 to length(exp)-1)
    {
        if(exp[i] is operand)
        res->res+exp[i]
    }
    else if exp[i] is operator
    while(!s.empty()&&HashigherPrec(s.top(),exp[i]))
    {
        res<-res+s.top()
        s.pop()
    }
    s.push(exp[i])
    while(!s.empty())
    {
        res<-res+s.top()
        s.pop()
    }
    return res;
}