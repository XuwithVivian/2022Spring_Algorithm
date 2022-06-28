#include <bits/stdc++.h>
using namespace std;

int min(int a, int b)
{
    if (a >= b)
        return b;
    else
        return a;
}

int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int main()
{
    int k = 1;
    int n;
    int min_value;

    cin >> n;

    int matrix[n][n] = {0};
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];

    for(int i = 1; i < n; i++) {
        for(int j = 1; j < n; j++) {
            if(matrix[i][j] == 1)
            {
                min_value = min(matrix[i - 1][j], matrix[i][j - 1]);
                min_value = min(min_value, matrix[i - 1][j - 1]);
                matrix[i][j] = min_value + 1;
                k = max(k, matrix[i][j]);
            }
        }
    }

    cout << k;

    return 0;
}