#include <bits/stdc++.h>
using namespace std;

long long dp[50010] = {0};      // 下标对应金额，表示对应金额的找零组合数
int a[20010] = {0};

int changecoin(int a[], int V, int n)
{
    dp[0] = 1;
    for(int i = 1; i <= n ; i++){
        for(int j = a[i - 1]; j <= V ; j++){
            dp[j] = (dp[j] + dp[j - a[i - 1]]) % 1000000007;
        }
    }
    return dp[V] % 1000000007;
}

int main()
{
    int n;
    int V, num = 0;
    cin >> n >> V;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << changecoin(a, V, n);
    return 0;
}