#include <bits/stdc++.h>
using namespace std;

int A[1000001];

long long CountTriplets(int a[], int n)
{
    long long num = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i])
                cnt++;
            else
                num += cnt;
        }
    }
    return num;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> A[i];
    int count = 0;
    cout << CountTriplets(A, n);
    return 0;
}