#include<bits/stdc++.h>
using namespace std;

#define MAX 0x0FFFFFFF

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    int n, m, u, v, w, q, flag = 0;
    cin >> n >> m;
    vector<vector<int>> value(n, vector<int>(n, MAX));
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        value[u - 1][v - 1] = w;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                value[i][j] = min(value[i][j], value[i][k] + value[k][j]);
    for (int i = 0; i < n; i++)
    {
        if (value[i][i] < 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        cout << "negative-weight cycle";
    }
    else {
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> u >> v;
            cout << value[u - 1][v - 1] << endl;
        }
    }
    return 0;
}