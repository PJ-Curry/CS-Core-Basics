//寄存柜 还是很好理解的 就是把二维的柜子坐标和存放的东西建立映射
#include<iostream>
#include<vector>
#include<map>
using namespace std;
map<int,map<int,int>>a;//建立二维映射
int main()
{
    int n,q;
    int k,x,y,z;//输入的每组数的四个数据
    cin>>n>>q;//寄包柜个数以及询问次数
    for(int i=1;i<=q;i++)
    {
        cin>>k>>x>>y;
        if(k==1)
        {
            cin>>z;
            a[x][y]=z;
        }
        else
        {
            cout<<a[x][y]<<endl;//会保证查询的柜子里一定有东西 所以大胆cout就行
        }
    }
    return 0;
}