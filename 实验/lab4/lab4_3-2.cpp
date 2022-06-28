#include<bits/stdc++.h>
using namespace std;

#define MAX 0x0FFFFFFF

#define N_MAX 601

int value[N_MAX][N_MAX];
int value_update[N_MAX][N_MAX];
int length[N_MAX][N_MAX];
int d[N_MAX];
int h[N_MAX];

// 结点包括顶点的最远短距离d和在数组中的下标q
struct Node
{
    int d;
    int q;
};

// 松弛操作
void relax(int j, int k)
{
    if (d[k] > d[j] + value[j][k])
        d[k] = d[j] + value[j][k];
}

// bellman_ford算法
int bellman_ford(int N, vector<set<int>> &edge)
{
    d[N - 1] = 0;
    int i, j;
    for (i = 1; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (auto k = edge[j].begin(); k != edge[j].end(); k++)
            {
                relax(j, *k);
            }
        }
    }
    for (j = 0; j < N; j++)
    {
        for (auto k = edge[j].begin(); k != edge[j].end(); k++)
        {
            if(d[*k] > d[j] + value[j][*k])
            {
                return 0;
            }
        }
    }
    return 1; 
}

// dijkstra算法
void dijkstra(vector<set<int>> &edge, int s, int N)
{
    auto cmp = [](Node a, Node b)
    {
        if (a.d != b.d)
            return a.d < b.d;
        else
            return a.q < b.q;
    };
    Node node[N];
    set<Node, decltype(cmp)> Q(cmp);    // 根据d值进行排序
    for (int i = 0; i < N; i++)
    {
        if (i != s)
        {
            node[i].d = MAX;
            node[i].q = i;
            Q.insert(node[i]);
        }
        else
        {
            node[i].d = 0;
            node[i].q = i;
            Q.insert(node[i]);
        }
    }
    while (!Q.empty())
    {
        Node u = *Q.begin();
        Q.erase(Q.begin());
        for (auto j = edge[u.q].begin(); j != edge[u.q].end(); j++)
        {
            if (node[*j].d > node[u.q].d + value[u.q][*j])
            {
                Q.erase(node[*j]);
                node[*j].d = node[u.q].d + value[u.q][*j];
                Q.insert(node[*j]);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        d[i] = node[i].d;
    }
}

int main()
{
    int n, m, u, v, w, q, flag = 0;
    cin >> n >> m;
    vector<set<int>> edge(n + 1);
    // 矩阵初始化
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                length[i][j] = 0;
                value[i][j] = 0;
            }
            else
            {
                length[i][j] = MAX;
                value[i][j] = MAX;
            }
        }
        d[i] = MAX;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        value[u - 1][v - 1] = w;
        edge[u - 1].insert(v - 1);
    }
    for (int i = 0; i < n; i++)
    {
        edge[n].insert(i);
        value[n][i] = 0;
        value[i][n] = MAX;
    }
    value[n][n] = 0;
    if (bellman_ford(n + 1, edge) == 0)
    {
        cout << "negative-weight cycle";
    }
    else 
    {
        for (int i = 0; i <= n; i++) {
            for (auto j = edge[i].begin(); j != edge[i].end(); j++)
            {
                value[i][*j] = value[i][*j] + d[i] - d[*j];
            }
            h[i] = d[i];
        }
        for (int i = 0; i < n; i++)
        {
            dijkstra(edge, i, n + 1);
            for (int j = 0; j <= n; j++) {
                if (d[j] != MAX)
                    length[i][j] = d[j] + h[j] - h[i];
            }
        }
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> u >> v;
            cout << length[u - 1][v - 1] << endl;
        }
    }
    return 0;
}