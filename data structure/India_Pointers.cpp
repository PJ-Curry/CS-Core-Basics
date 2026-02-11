#include<stdio.h>
//第三节 指针类型强制转换
int main()
{
    int a=1025;
    int *p;
    p=&a;
    printf("size of interger is %d bytes\n",sizeof(int));
    printf("Address =%d,value=%d\n",p,*p);
    printf("Address =%d,value=%d\n",p+1,*(p+1));
    char *p0;
    p0=(char*)p;//强制转换指针类型 转换为char类型
    printf("size of char is %d bytes\n",sizeof(char));
    printf("Address=%d,value=%d\n",p0,*p0);
    printf("Address =%d,value=%d\n",p0+1,*(p0+1));
    //1025=00000000 00000000 00000100 00000001
    /*
    size of interger is 4 bytes
    Address =6422076,value=1025
    Address =6422080,value=12475904  具体数值不知道没有初始化 所以是乱码
    size of char is 1 bytes
    Address=6422076,value=1          强制转换成1字节 就是读取最后8位 最后那个字节00000001 所以是1
    Address =6422077,value=4         读取第二个字节就是00000100 二进制计算结果是4
    */
}  
//void pointer-Genric pointer 空指针 
int main()
{
    int a=1025;
    int *p=&a;
    printf("size of integer is %d bytes\n",sizeof(int));
    printf("Address=%d,value=%d\n",p,*p);
    void *p0;
    p0=p;//不需要像char那样进行强制的类型转换
    //printf("Address=%d,value=%d\n",p0,*p0);//不能打印*p0因为没有指定的数据类型进行解引用(报错) 我们只能打印p0
    printf("Address=%d",p0);
}

//第四节 二级指针 Pointer to pointer 在笔记里

//第五节 指针作为函数参数，想通过引用调用 一个反例
void Increment(int a)//called function a是形参
{
    a=a+1;
}
int main()//calling function
{
    int a;
    a=10;
    Increment(a);//调用函数中调用一个函数时 参数成为实参
    printf("a=%d",a);
}
/*底层逻辑 这些函数的操作都是在栈中运行的 从main开始 然后Increment Increment结束之后出栈然后回到main 一个单位称作一个栈帧(stack frame) 
这个程序最后输出的结果还是10 因为在Increment对10加了1之后就出栈了 main函数中的10还在等着 最后还是没变 Increment没有发挥作用
所发生的一切都是实参映射到了形参上 这种调用也称作按值调用 所以没有成功*/
//正例 引用调用 把指针作为函数参数就可以做到
void Increment(int *p)//见笔记
{
    *p=(*p)+1;
}
int main()
{
    int a;
    a=10;
    Increment(&a);//调用函数中调用一个函数时 参数成为实参
    printf("a=%d",a);
}

//第六节 指针和数组
int main()
{
    int A[]={2,4,5,8,1};  // printf("%d",A)等效于printf("%d",&A[0]);都是输出首地址 A[0]=*A等效  A[i]等效*(A+i)
    int i;
    int *p=A;//变量名和创建的指针变量都是等效的
    //A++;不能这么做 只能p++
    for(int i=0;i<5;i++)
    {
        printf("Address=%d\n",&A[i]);//各个数字的地址
        printf("Address=%d\n",A+i);//地址
        printf("value=%d\n",A[i]);//数字
        printf("value=%d\n",*(A+i));//数字
    }
}

//第七节 数组作为函数参数传
int SumOfElements(int A[])
/*编译器会把括号里的参数解释为int *A 一个指向整型变量的指针 而不会复制整个数组(在栈中)一个形参只能传递一个值他只是复制存储变量(这个数组)的首地址 数组不存在传值调用 都是引用调用*/
{
    int i,sum=0;
    int size=sizeof(A)/sizeof(A[0]);//sizeof是算字节数的
    for(i=0;i<size;i++)
    {
        sum+=A[i];
    }
    return sum;
}
int main()
{
    int A[]={1,2,3,4,5};
    int total=SumOfElements(A);
    printf("Sum of elements=%d\n",total);
}
//上述这种方法不行 所以还是要在main函数中计算数组大小 正确示范
int SumOfElements(int *A,int size)
{
    int i,sum=0;
    printf("SOE-Size of A=%d,size of A[0]=%d/n",sizeof(A),sizeof(A[0]));
    for(i=0;i<size;i++)
    {
        sum+=A[i];//A[i]是*(A+i)
    }
    return sum;
}
int main()
{
    int A[]={1,2,3,4,5};
    int size=sizeof(A)/sizeof(A[0]);
    int total=SumOfElements(A,size);
    printf("Sum of elements=%d\n",total);
    printf("Main -Size of A=%d,size of A[0]=%d\n",sizeof(A),sizeof(A[0]));
}

//第八节 字符数组与指针 第一讲
void print(char *C)//不知道数组的大小是20 只知道基地址
{
    int i=0;
    while(C[i]!='\0')//等效于*(C+i)
    {
        printf("%c",C[i]);
        i++;
    }
    /*
    while(*C!='\0')
    {
        printf("%c",*C);
        C++;
    }
    */
    printf("\n");
}
int main()
{
    char C[20]="Hello";//等效于 *C="Hello";这是一个常量 无法被修改 不能再写C[0]='A';放在print函数中就可行 加上const就不行
    //不想直接调用printf库函数 想调用自己写的函数 注意：数组都是引用传递给函数的
    print(C);
}

//第十 十一节 指针和多维数组 创建一个函数接受三维数组作为参数
void Func(int (*A)[2][2])//传递三维数组 别多写 写成***A
{
    
}
int main()
{
    int C[3][2][2]={{{2,5},{7,9}},{{3,4},{6,1}},{{0,8},{11,13}}};
    int A[]={1,2};
    int B[2][3]={{2,4,6},{5,7,8}};//B returns int (*)[3]
    Func(C);//A returns int*
}