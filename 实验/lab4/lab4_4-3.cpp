#include<bits/stdc++.h>
using namespace std;

#define N 600

int G[N + 1][N + 1] = {0};
int p[N + 1];

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

bool bfs(int u, int v, int n, int w_max)
{
    int path[n + 1] = {0};
    queue<int> q;
    q.push(u);
    path[u] = 1;
    p[u] = -1;
    p[0] = -1;
    while (!q.empty())
    {
        int i = q.front();
        q.pop();
        for (int j = 1; j <= n; j++)
        {
            if (!path[j] && G[i][j] >= w_max)
            {
                q.push(j);
                p[j] = i;
                path[j] = 1;
            }
        }
    }
    return path[v];
}

int main()
{
    int n, m, u, v, w;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        G[u][v] = w;
    }
    int max_flow = 0;
    cin >> u >> v;
    int w_max = 1000;
    while (w_max >= 1)
    {
        while (bfs(u, v, n, w_max))
        {
            int flow = INT_MAX;
            for (int i = v; i != u; i = p[i])
            {
                int j = p[i];
                flow = min(flow, G[j][i]);
            }
            for (int i = v; i != u; i = p[i])
            {
                int j = p[i];
                G[j][i] -= flow;
                G[i][j] += flow;
            }
            max_flow += flow;
        }
        w_max /= 2;
    }
    cout << max_flow;
    return 0;
}