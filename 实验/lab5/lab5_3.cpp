#include <bits/stdc++.h>
using namespace std;

// 高精度数结构体
struct Number
{
    char num[2000];
    int length;
    int mark;
};

// 打印高精度数
void print(Number n)
{
    if (n.length == 0)
        cout << 0 << endl;
    if (n.mark == -1)
        cout << "-";
    for (int i = n.length - 1; i >= 0; i--)
        cout << (int)n.num[i];
    cout << endl;
}

// 将整型数转换成高精度数
Number transformtonumber(int a)
{
    Number num = {{0}, 0, 1};
    if (a < 0)
    {
        num.mark = -1;
        a *= (-1);
    }
    while (a != 0)
    {
        num.num[num.length++] = a % 10;
        a = a / 10;
    }
    return num;
}

// 比较高精度数绝对值
int cmp1(Number x, Number y)
{
    if (x.length > y.length)
        return 1;
    else if (x.length < y.length)
        return -1;
    else
    {
        for (int i = x.length - 1; i >= 0; i--)
        {
            if (x.num[i] > y.num[i])
                return 1;
            else if (x.num[i] < y.num[i])
                return -1;
        }
    }
    return 0;
}

// 高精度加法
Number add(Number x, Number y)
{
    Number num = {{0}, 0, 1};
    int t = 0, s;
    if (x.mark == y.mark)
    {
        num.mark = x.mark;
        for (int i = 0; i < x.length && i < y.length; i++)
        {
            s = x.num[i] + y.num[i] + t;
            t = s / 10;
            num.num[i] = s % 10;
            num.length++;
        }
        if (x.length > y.length)
        {
            for (int i = y.length; i < x.length; i++)
            {
                s = x.num[i] + t;
                t = s / 10;
                num.num[i] = s % 10;
                num.length++;
            }
        }
        else
        {
            for (int i = x.length; i < y.length; i++)
            {
                s = y.num[i] + t;
                t = s / 10;
                num.num[i] = s % 10;
                num.length++;
            }
        }
        if (t == 1)
            num.num[num.length++] = 1;
    }
    else
    {
        if (cmp1(x, y) == 1)
        {
            num.mark = x.mark;
            for (int i = 0; i < y.length; i++)
            {
                s = x.num[i] - y.num[i] - t;
                if (s >= 0)
                {
                    t = 0;
                    num.num[i] = s;
                }
                else
                {
                    t = 1;
                    num.num[i] = 10 + s;
                }
                num.length++;
            }
            for (int i = y.length; i < x.length; i++)
            {
                s = x.num[i] - t;
                if (s >= 0)
                {
                    t = 0;
                    num.num[i] = s;
                }
                else
                {
                    t = 1;
                    num.num[i] = 10 + s;
                }
                num.length++;
            }
        }
        else if (cmp1(x, y) == -1)
        {
            num.mark = y.mark;
            for (int i = 0; i < x.length; i++)
            {
                s = y.num[i] - x.num[i] - t;
                if (s >= 0)
                {
                    t = 0;
                    num.num[i] = s;
                }
                else
                {
                    t = 1;
                    num.num[i] = 10 + s;
                }
                num.length++;
            }
            for (int i = x.length; i < y.length; i++)
            {
                s = y.num[i] - t;
                if (s >= 0)
                {
                    t = 0;
                    num.num[i] = s;
                }
                else
                {
                    t = 1;
                    num.num[i] = 10 + s;
                }
                num.length++;
            }
        }
        else
            return num;
        while (num.num[num.length - 1] == 0)
                num.length--;
    }
    return num;
}

// 高精度减法
Number sub(Number x, Number y)
{
    Number z = y;
    z.mark *= (-1);
    return add(x, z);
}

// 高精度乘法
Number mul(Number x, Number y)
{
    Number num = {{0}, 0, 1};
    if (x.length == 0 || y.length == 0)
        return num;
    else
    {
        for (int i = 0; i < x.length; i++)
        {
            for (int j = 0; j < y.length; j++)
            {
                num.num[i + j] += x.num[i] * y.num[j];
                num.num[i + j + 1] += num.num[i + j] / 10;
                num.num[i + j] %= 10;
            }
        }
        if (x.mark == y.mark)
            num.mark = 1;
        else
            num.mark = -1;
        num.length = x.length + y.length - 1;
        if (num.num[num.length] != 0)
            num.length++;
        return num;
    }
}

// 高精度除法及取模
Number divide(Number x, Number y, Number &re)
{
    Number num = {{0}, 0, 1};
    if (cmp1(x, y) == -1)
    {
        re = x;
        return num;
    }
    int xs = x.length, ys = y.length, d = xs - ys, u;
    for (int i = y.length - 1; i >= 0; i--)
        y.num[i + d] = y.num[i];
    for (int i = 0; i < d && i < ys; i++)
        y.num[i] = 0;
    y.length = x.length;
    int pos = d;
    while (ys <= y.length)
    {
        while (cmp1(x, y) >= 0)
        {
            num.num[pos]++;
            x = sub(x, y);
        }
        if (pos > 1)
            u = pos;
        else
            u = 1;
        for (int i = u; i < y.length; i++)
            y.num[i - 1] = y.num[i];
        y.length--;
        pos--;
    }
    if (x.mark == y.mark)
        num.mark = 1;
    else
        num.mark = -1;
    num.length = d + 1;
    while (num.num[num.length - 1] == 0)
        num.length--;
    re = x;
    return num;
}

// gcd函数
Number ex_gcd(Number a, Number b, Number &x, Number &y)
{
    Number d = {{0}, 0, 1}, r = {{0}, 0, 1}, di = {{0}, 0, 1};
    if (b.length == 0)
    {
        d = a;
        x = transformtonumber(1);
        y = transformtonumber(0);
    }
    else
    {
        di = divide(a, b, r);
        d = ex_gcd(b, r, x, y);
        Number t = x;
        x = y;
        y = sub(t, mul(divide(a, b, r), y));
    }
    return d;
}

// 中国余数定理
Number mod(int k, Number vr[], Number vp[])
{
    Number num = transformtonumber(1);
    Number result = transformtonumber(0);
    Number re = {{0}, 0, 1}, di = {{0}, 0, 1}, rex = {{0}, 0, 1}, rey = {{0}, 0, 1}, d = {{0}, 0, 1};
    for (int i = 0; i < k; i++)
        num = mul(num, vp[i]);
    for (int i = 0; i < k; i++)
    {
        Number x = {{0}, 0, 1}, y = {{0}, 0, 1};
        di = divide(num, vp[i], re);
        d = ex_gcd(di, vp[i], x, y);
        divide(x, vp[i], rex);
        divide(add(rex, vp[i]), vp[i], rey);
        result = add(result, mul(vr[i], mul(di, rey)));
    }
    d = divide(result, num, re);
    return re;
}

int main()
{
    int k, r, p;
    cin >> k;
    Number vr[k], vp[k];
    for (int i = 0; i < k; i++)
    {
        cin >> r >> p;
        vr[i] = transformtonumber(r);
        vp[i] = transformtonumber(p);
    }
    Number n = mod(k, vr, vp);
    print(n);
    return 0;
}