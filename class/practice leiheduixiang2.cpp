#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
class BankAccount
{
private:
string accountNumber;//账号
string accountHolder;//账户持有人姓名
double balance;
public:
BankAccount(string accNumber,string accHolder)
:accountNumber(accNumber),accountHolder(accHolder),balance(0.0){}//完成初始化
void deposit(double amount)//题目里没说要用构造函数 这就是一个普通的成员函数 成员函数在后续调用的时候就是m.什么什么就可以了
{
    balance+=amount;
}
void withdraw(double amount)
{
    if(amount>balance)
    {
        cout<<"Insufficient funds"<<endl;
        return;//这样就可以直接返回了 不用再执行下面的代码了
    }
    balance-=amount;
}
void displayBalance()const//加const是一种良好的做法 表示这个成员函数不会修改类的成员变量
/*如果成员函数只是用于读取类的数据，不涉及修改类的数据就应该加上const来提高代码的可读性和可维护性*/
{
    cout<<fixed<<setprecision(2)<<balance<<endl;
}
};
int main()
{
     string accnumber;
     string name;
     double money;
     cin>>accnumber>>name;
     BankAccount m(accnumber,name);
     string operation;//用于储存操作类型
    while(true)//这个循环是巧妙地
    {
        cin>>operation;
        if(operation=="D"||operation=="W")//如果operation是char类型就用单引号 如果是string类型就用双引号 这是第一次报错的原因
        {
            cin>>money;
            if(operation=="D")
            {
                m.deposit(money);
            }
            else if(operation=="W")
            {
                m.withdraw(money);
            }
        }
        else if(operation=="END")
        {
            break;
        }
    }
    m.displayBalance();
    return 0;
}