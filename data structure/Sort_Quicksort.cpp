/*快速排序 快速排序 时间复杂度O(N*logN) 空间复杂度O(logN)
逻辑
1.[i]<num,[i]和<区下一个交换,<区右扩,i++
2.[i]==num,i++
3.[i]>num,[i]和>区前一个交换,>区左扩,i不变
*/
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
//三路划分 以arr[R]为枢轴
//通过引用参数leftEnd,rightStart 返回等于区的左右边界
void partition(int arr[],int L,int R,int &leftEnd,int &rightStart)//我们还要知道等于区域的左右边界
{
    int pivot=arr[R];
    int less=L-1;//<区右边界
    int more=R;//>区左边界
    int i=L;//当前扫描位置
    while(i<more)//不需要重复处理大于区域
    {
        if(arr[i]<pivot)
        {
            swap(arr[++less],arr[i++]);
        }
        else if(arr[i]>pivot)
        {
            swap(arr[--more],arr[i]);
        }
        else
        {
            i++;
        }
    }
    swap(arr[more],arr[R]);//把选定的枢轴 即在最后位置的数字 放在右边界的最左侧
    leftEnd=less+1;
    rightStart=more;
}
void Quicksort(int arr[],int L,int R)//开始递归
{
    if(L<R)
    {
        int pivotIndex=L+rand()%(R-L+1);
        swap(arr[pivotIndex],arr[R]);
        int p,q;
        partition(arr,L,R,p,q);
        Quicksort(arr,L,p-1);//递归
        Quicksort(arr,q+1,R);//双侧递归
    }
}
int main()
 {
    ios::sync_with_stdio(false);//这两行可以不写 是为了优化性能之类的
    cin.tie(nullptr);
    // —— 随机数初始化 —— 
    srand(static_cast<unsigned>(time(nullptr)));
    int n;
    cin >> n;
    int* data = new int[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> data[i];
    }
    Quicksort(data, 0, n - 1);
    for (int i = 0; i < n; ++i)
    {
        cout << data[i] << (i + 1 < n ? ' ' : '\n');
    }
    delete[] data;
    return 0;
}


void qsort(int a[],int l,int r)
{
    if(l>=r) return;//递归边界
    int i=l,j=r;
    int flag=a[(l+r)/2],tmp;//枢轴
    while(i<=j)
    {
        while(a[i]<flag) i++;
        while (a[j]>flag) j--;
        if(i<=j)
        {
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }
    if(l<j) qsort(a,l,j);
    if(i<r) qsort(a,i,r);
}