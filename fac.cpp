#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;
const int MAX = 10000;                     //整型数组的最大长度 
const long long WIDTHMAX = 1000000000;     //整型数组val[MAX]的元素上限 
const int WIDTH = 9;                       //输出整型数组val[MAX]的元素时的格式宽度，即整型数组val[MAX]的元素的最多位数 
ofstream fout("fac.txt"); 

typedef struct node
{
    long long val[MAX];       //用来存储高精度整数 
    unsigned int size;        //整型数组的实际长度 
}BigInt;

void PrintBigInt(const BigInt & a);    //输出大数类
BigInt MulBigInt(const BigInt & a, const BigInt & b);     //大数类相乘
BigInt FacBigInt(unsigned int n);           //大数类求阶乘


void PrintBigInt(const BigInt & a)
{
	unsigned w;
	int i;
	fout<<a.val[a.size-1];
    for (i=a.size-2; i>=0; i--)
    {
		w = WIDTHMAX / 10;
        while (w > 0)
        {
            if (a.val[i] >= w)
                break;
			fout<<"0";
            w /= 10;
        }
		fout<<a.val[i];
    }
	fout<<endl;
}

/*
函数名称：MulBigInt
函数功能：高精度整数乘法
输入参数：const BigInt & a：用整型数组表示的高精度整数被乘数 
          const BigInt & b：用整型数组表示的高精度整数乘数 
输出参数：BigInt：返回用整型数组表示的高精度整数乘积 
*/
BigInt MulBigInt(const BigInt & a, const BigInt & b)
{
	int i,j;
	BigInt c;
	if (a.size == 1 && a.val[0] == 0)
		return a;
	if (b.size == 1 && b.val[0] == 0)
		return b;

	for (i=0; i<MAX; i++)    //全部赋初值为0 
		c.val[i] = 0;
	for ( i=0, j=0; i<b.size; i++)
	{
		for (j=0; j<a.size; j++)
		{
			c.val[i+j] += a.val[j] * b.val[i]; 
			c.val[i+j+1] += c.val[i+j] / WIDTHMAX; 
			c.val[i+j] %= WIDTHMAX; 
		}
		c.size = i + j;
		if (c.val[c.size] != 0)    //最高位有进位 
			c.size++;
	}
	return c;
}


/*
函数名称：FacBigInt
函数功能：高精度整数阶乘
输入参数：unsigned int n：正整数 
输出参数：BigInt：返回用整型数组表示的高精度整数阶乘 
*/
BigInt FacBigInt(unsigned int n)
{
	long long i;
    BigInt s, c;
    c.size = s.size = 1;
    s.val[0] = 1;
    for (i=2; i<=n; i++)
    {
        c.val[0] = i;
        s = MulBigInt(s, c);
    }
    return s;
}

int main()
{
	BigInt a;
	long long n;
	cout<<"请输入待求阶乘的n的值：";
	cin>>n;
	a=FacBigInt(n);
	cout<<n<<"的阶乘已生成：fac.txt 在运行目录下"<<endl;
	PrintBigInt(a);
	system("pause");
	return 0;    
}
