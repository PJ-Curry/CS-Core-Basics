#include<iostream>
using namespace std;
int qsort(int a[],int l,int r,int k)
{
    while(l<=r)
    {
        int i=l,j=r;
        int flag=a[(l+r)/2];
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
        if(k<=j) return qsort(a,l,j,k);
        if(k>=i) return qsort(a,i,r,k);
        else return a[k+1];
    }
}
int main()
{
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);             
    int n,k;
    cin>>n>>k;
    int *a = new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<qsort(a,0,n-1,k-1);
    delete[] a;
    return 0;
}