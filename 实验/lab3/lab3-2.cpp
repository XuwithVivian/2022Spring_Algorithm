#include <bits/stdc++.h>
using namespace std;

int min(int a, int b)
{
    if (a >= b)
        return b;
    else
        return a;
}

int leastlen(int a[], int n, int K)
{
    int len = n + 1;
    deque<int> dec;
    long long sum[n + 1] = {0};
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + a[i - 1];
    }
    for (int i = 0; i <= n; i++)
    {
        while (!dec.empty() && sum[i] - sum[dec.front()] >= K)
        {
            len = min(len, i - dec.front());
            dec.pop_front();
        }
        while (!dec.empty() && sum[i] <= sum[dec.back()])
        {
            dec.pop_back();
        }
        dec.push_back(i);
    }
    if (len == n + 1)
        return 0;
    else
        return len;
}

int main()
{
    int n, K;
    cin >> n >> K;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << leastlen(a, n, K);
    return 0;
}