#include<bits/stdc++.h>
using namespace std;

vector<int> S;

void dfs_visit(int u, int n, vector<unordered_set<int>> &s, int color[])
{
    color[u] = -1;
    for (auto i = s[u].begin(); i != s[u].end(); i++)
    {
        if (color[*i] == 0)
        {
            S.push_back(*i);
            dfs_visit(*i, n, s, color);
        }
    }
    color[u] = 1;
}

int main()
{
    int n = 600, m = 600, edge, w;
    int num = m / n;
    int color[n] = {0};
    ofstream outfile;
    vector<unordered_set<int>> s(n);
    outfile.open("file4.txt");
    outfile << n << " " << m << endl;
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < num; j++)
        {
            edge = rand() % n + 1;
            while (edge == i || s[i - 1].find(edge) != s[i - 1].end())
                edge = rand() % n + 1;
            s[i - 1].insert(edge);
            w = rand() % 1001;
            outfile << i << " " << edge << " " << w << endl;
        }
    }
    S.clear();
    int u = rand() % n + 1;
    cout << u << endl;
    dfs_visit(u, n, s, color);
    int t = rand() % S.size();
    int v = S[t];
    cout << v << endl;
    outfile << u << " " << v << endl;
    outfile.close();
    return 0;
}