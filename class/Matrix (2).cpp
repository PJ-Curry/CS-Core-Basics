#include<iostream>
using namespace std;
class Matrix
{
private:
int **data;
int rows,cols;
public:
Matrix(int r,int c):rows(r),cols(c)
{
    data=new int*[rows];
    for(int i=0;i<rows;i++)
    {
        data[i]=new int[cols]();
    }
}
~Matrix()//
{
    for(int i=0;i<rows;i++)
    {
        delete[]data[i];//释放每一行
    }
    delete[]data;//释放行指针数组
}
int&operator()(int r,int c){return data[r][c];}
int operator()(int r,int c)const{return data[r][c];}
Matrix operator+(const Matrix &m)const//m就是另一个矩阵 通过const来建立
{
if(rows!=m.rows||cols!=m.cols)throw runtime_error("mismatch");
Matrix result(rows,cols);
for(int i=0;i<rows;i++)
{
    for(int j=0;j<cols;j++)
    {
        result(i,j)=data[i][j]+m(i,j);
    }
}
return result;
}
Matrix operator*(const Matrix&m)const//重载运算符乘号
{
    if(cols!=m.rows)throw runtime_error("impossible");
    Matrix result(rows,m.cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<m.cols;j++)
        {
            for(int k=0;k<cols;k++)
            {
                result(i,j)+=data[i][k]*m(k,j);//A矩阵是i行k列 B矩阵就是k行j列
            }
        }
    }
    return result;
}//下一个函数 矩阵转置
Matrix transpose()const
{
    Matrix result(cols,rows);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            result(j,i)=data[i][j];
        }
    }
    return result;
}
//友元函数 输出矩阵
friend ostream&operator<<(ostream &out,const Matrix &m)
{
    for(int i=0;i<m.rows;i++)
    {
        for(int j=0;j<m.cols;j++)//m是对象名 不然在这里没法访问
        {
            out<<m(i,j)<<" ";
        }
        out<<endl;
    }
    return out;
}
void input()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cin>>data[i][j];
        }
    }
}
};
int main()
{
    int r,c;
    cin>>r>>c;
    Matrix A(r,c),B(r,c);
    A.input();
    B.input();
    try
    {
        cout<<A+B;
        cout<<A*B;
        cout<<A.transpose();
    }catch(const runtime_error&e)
    {
        cout<<"Error:"<<e.what()<<endl;
    }
    return 0;
}