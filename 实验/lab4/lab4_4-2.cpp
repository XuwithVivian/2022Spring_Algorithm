#include<bits/stdc++.h>
using namespace std;

#define N 600

int G[N + 1][N + 1] = {0};
int p[N + 1] = {-1};    // 记录父结点
int flow;

// 结点包括顶点的最大剩余容量d和在数组中的下标q
struct Node
{
    int d;
    int q;
};

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

// 搜索最大剩余容量路径
bool bfs(int u, int v, int n)
{
    // 在dijkstra算法的基础上做修改
    auto cmp = [](Node a, Node b)
    {
        if (a.d != b.d)
            return a.d > b.d;
        else
            return a.q > b.q;
    };
    Node node[n];
    int path[n] = {0};
    path[u] = 1;
    set<Node, decltype(cmp)> Q(cmp);    // 根据d值进行排序
    for (int i = 0; i < n; i++)
    {
        if (i != u)
        {
            node[i].d = 0;
            node[i].q = i;
            Q.insert(node[i]);
        }
        else
        {
            node[i].d = 1000;
            node[i].q = i;
            Q.insert(node[i]);
        }
        p[i] = -1;
    }
    while (!Q.empty())
    {
        Node n_begin = *Q.begin();
        Q.erase(Q.begin());
        path[n_begin.q] = 1;
        for (int j = 0; j < n; j++)
        {
            if (!path[j] && G[n_begin.q][j] > 0 && node[j].d < min(node[n_begin.q].d, G[n_begin.q][j]))
            {
                p[j] = n_begin.q;
                Q.erase(node[j]);
                node[j].d = min(node[n_begin.q].d, G[n_begin.q][j]);
                Q.insert(node[j]);
            }
        }
    }
    flow = node[v].d;       // 剩余容量
    if (p[v] == -1)
        return false;
    else
        return true;
}

int main()
{
    int n, m, u, v, w;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        G[u - 1][v - 1] = w;
    }
    int max_flow = 0;
    cin >> u >> v;
    while (bfs(u - 1, v - 1, n))
    {
        for (int i = v - 1; i != u - 1; i = p[i])
        {
            int j = p[i];
            G[j][i] -= flow;
            G[i][j] += flow;
        }
        max_flow += flow;
    }
    cout << max_flow;
    return 0;
}