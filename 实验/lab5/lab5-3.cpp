#include<bits/stdc++.h>
using namespace std;

void ex_gcd(long long a, long long b, long long &x, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
	}
    else
    {
        ex_gcd(b, a % b, x, y);
        long long t = x;
        x = y;
        y = t - a / b * y;
    }
}

long long mod(long long k, long long vr[], long long vq[])
{
    long long num = 1, result = 0;
    for (long long i = 0; i < k; i++)
        num *= vq[i];
    for (long long i = 0; i < k; i++)
    {
        long long x, y;
        ex_gcd(num / vq[i], vq[i], x, y);
        // prlong longf("n:%d a:%d x:%d\n", vq[i], num / vq[i], (x % num + num) % num);
        result += (num / vq[i]) * vr[i] * ((x % num + num) % num);
    }
    return result % num;
}

int main()
{
    long long k, r, q;
    // vector<long long> vr, vq;
    cin >> k;
    long long vr[k], vq[k];
    for (long long i = 0; i < k; i++)
    {
        cin >> r >> q;
        vr[i] = r;
        vq[i] = q;
    }
    cout << mod(k, vr, vq);
    return 0;
}