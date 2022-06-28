#include<bits/stdc++.h>
using namespace std;

stack<int> s;

// KMP算法
void KMP(string T, string P)
{
    int n = T.size();
    int m = P.size();
    vector<int> next(m, -1);
    int k = -1;
    for (int q = 1; q < m; q++)
    {
        while (k != -1 && P[k + 1] != P[q])
        {
            k = next[k];
        }
        if (P[k + 1] == P[q])
        {
            k++;
        }
        next[q] = k;
    }
    int q = -1;
    for (int i = 1; i < n - 1; i++)
    {
        while (q != -1 && P[q + 1] != T[i])
            q = next[q];
        if (P[q + 1] == T[i])
            q++;
        if (q == m - 1)
        {
            q = next[q];
            if (i - m + 1 <= m / 2 && m % (i - m + 1) == 0)
            {
                int pos = m / (i - m + 1);
                s.push(pos);    // 将结果存入栈中，即可实现结果的按序输出
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    string P = "";
    char c;
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        P += c;
    }
    // 1一定是正确答案
    cout << "1" << endl;
    KMP(P + P, P);
    while(!s.empty())
    {
        int r = s.top();
        cout << r << endl;
        s.pop();
    }
    return 0;
}