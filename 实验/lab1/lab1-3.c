#include<stdio.h>
#include<math.h>

#define Pi 3.1415926535898

// 定义复数结构体
typedef struct Complex
{
    double real;    // 实部
    double imaginary;   // 虚部
}Complex;

// 利用FFT方法计算DFT(a)
void recursive_fft(int n, Complex a[], Complex y[], int flag)   // flag为0时运用FFT，否则运用逆FFT
{
    if (n == 1)
    {
        y[0].imaginary = a[0].imaginary;
        y[0].real = a[0].real;
        return;
    }

    int num = 0;
    Complex w, w_n;

    // w = 1
    w.imaginary = 0.0;
    w.real = 1.0;

    Complex a_0[n / 2];
    Complex a_1[n / 2];
    Complex y_0[n / 2];
    Complex y_1[n / 2];
    // 以上数组分别储存偶数和奇数位的元素
    for (int i = 0; i < n / 2; i++)
    {
        a_0[i].imaginary = a[2 * i].imaginary;
        a_0[i].real = a[2 * i].real;
        a_1[i].imaginary = a[2 * i + 1].imaginary;
        a_1[i].real = a[2 * i + 1].real;
    }
    // 迭代
    recursive_fft(n / 2, a_0, y_0, flag);
    recursive_fft(n / 2, a_1, y_1, flag);

    for (int k = 0; k < n / 2; k++)
    {
        // y[k] = y_0[k] + w * y_1[k]
        y[k].imaginary = y_0[k].imaginary + w.real * y_1[k].imaginary + w.imaginary * y_1[k].real;
        y[k].real = y_0[k].real + w.real * y_1[k].real - w.imaginary * y_1[k].imaginary;
        // y[k + n / 2] = y_0[k] - w * y_1[k]
        y[k + n / 2].imaginary = y_0[k].imaginary - w.real * y_1[k].imaginary - w.imaginary * y_1[k].real;
        y[k + n / 2].real = y_0[k].real - w.real * y_1[k].real + w.imaginary * y_1[k].imaginary;
        // w = w * w_n
        if (flag == 0)  // FFT
            num += 2;
        else    // 逆FFT
            num -= 2;
        w.imaginary = sin((double)num / n * Pi);
        w.real = cos((double)num / n * Pi);
    }
}

// 用四舍五入的方式将接近答案的浮点数转化成对应的整数输出
int neartodouble(double num)
{
    int i = (int)num;
    if (num - i >= 0.5)
        return i + 1;
    else
        return i;
}

int main()
{
    int n, m = 1;
    scanf("%d", &n);    // 输入n
    while (m < n + 1) // 找到大于等于n + 1的最小的2的幂
    {
        m = m * 2;
    }
    m = m * 2;  // 将次数届加倍
    Complex A[m], B[m], C[m];
    // 输入实部，虚部赋0
    for (int i = 0; i <= n; i++)
    {
        scanf("%lf", &(A[i].real));
        A[i].imaginary = 0.0;
    }
    for (int i = 0; i <= n; i++)
    {
        scanf("%lf", &(B[i].real));
        B[i].imaginary = 0.0;
    }
    // 后续位数实部虚部皆赋0
    for (int i = n + 1; i < m; i++)
    {
        A[i].imaginary = 0.0;
        A[i].real = 0.0;
        B[i].imaginary = 0.0;
        B[i].real = 0.0;
    }
    // 对A,B执行FFT
    Complex y_A[m], y_B[m], y_C[m];
    recursive_fft(m, A, y_A, 0);
    recursive_fft(m, B, y_B, 0);

    // 用点值乘法得到C数组
    for (int i = 0; i < m; i++)
    {
        y_C[i].imaginary = y_A[i].imaginary * y_B[i].real + y_A[i].real * y_B[i].imaginary;
        y_C[i].real = y_A[i].real * y_B[i].real - y_A[i].imaginary * y_B[i].imaginary;
    }
    
    // 对C数组执行逆FFT
    recursive_fft(m, y_C, C, 1);
   
    // 以整型形式输出结果
    for (int i = 0; i <= 2 * n; i++)
    {
        printf("%d ", neartodouble(C[i].real / m));
    } 
        
    return 0;
}