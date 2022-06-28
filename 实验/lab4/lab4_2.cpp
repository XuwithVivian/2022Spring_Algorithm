#include <bits/stdc++.h>
using namespace std;

#define N 160001
#define M 320001

vector<set<int>> scc_G(1000);
vector<set<int>> scc_reach(1000);
int color[N];
int d[N];
int order[N];       // 记录按照指定顺序的顶点
int f[N];
int scc_in[N] = {-1};   // 记录每个点所在的强连通分量
int timer;
int scc_num;    // 记录强连通分量数
int time_num;

// 深度优先搜索
void dfs_visit(int n, int u, int T, vector<set<int>> &scc_set, vector<set<int>> &edge_1, vector<set<int>> &edge_2)
{
    timer++;
    color[u] = -1;
    d[u] = timer;
    if (T == 0)
    {
        for (auto i = edge_1[u].begin(); i != edge_1[u].end(); i++)
        {
            if (color[*i] == 0)
            {
                dfs_visit(n, *i, T, scc_set, edge_1, edge_2);
            }
        }
    }
    else
    {
        scc_in[u] = scc_num;
        scc_set[scc_num].insert(u);
        for (auto i = edge_2[u].begin(); i != edge_2[u].end(); i++)
        {
            if (color[*i] == 0)
            {
                dfs_visit(n, *i, T, scc_set, edge_1, edge_2);
            }
            else
            {
                if (scc_in[*i] != scc_num) {
                    scc_G[scc_in[*i]].insert(scc_num);
                }
            }
        }
    }
    color[u] = 1;
    if (T == 0)
    {
        timer++;
        f[u] = timer;
    }
    else
    {
        order[time_num++] = u;
    }
}

// 深度优先搜索，若T为0，则对G执行；若T为1，则对G的转置图执行
void dfs(int n, int T, vector<set<int>> &scc_set, vector<set<int>> &edge_1, vector<set<int>> &edge_2)
{
    for (int i = 0; i < n; i++)
    {
        color[i] = 0;
    }
    int j;
    timer = 0;
    scc_num = 0;
    time_num = 0;
    for (int i = 0; i < n; i++)
    {
        j = order[i];
        if (color[j] != 1)
        {
            dfs_visit(n, j, T, scc_set, edge_1, edge_2);
            if (T == 1)
                scc_num++;
        }
    }
}

// 求强连通分量
void scc(int n, vector<set<int>> &scc_set, vector<set<int>> &edge_1, vector<set<int>> &edge_2)
{
    for (int i = 0; i < n; i++)
    {
        order[i] = i;
    }
    dfs(n, 0, scc_set, edge_1, edge_2);
    dfs(n, 1, scc_set, edge_1, edge_2);
}

int main()
{
    int n, m, u, v, q;
    cin >> n >> m;
    vector<set<int>> edge_1(n + 1);
    vector<set<int>> edge_2(n + 1);
    vector<set<int>> scc_set(n + 1);
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        edge_1[u - 1].insert(v - 1);
        edge_2[v - 1].insert(u - 1);
    }
    scc(n, scc_set, edge_1, edge_2);
    vector<vector<int>> t(scc_num, vector<int>(scc_num));
    for (int i = 0;i < scc_num; i++)
    {
        for (int j = 0;j < scc_num; j++)
        {
            if (i == j || scc_G[i].find(j) != scc_G[i].end())
                t[i][j] = 1;
            else
                t[i][j] = 0;
        }
    }
    // TRANSITIVE-CLOSURE算法
    vector<vector<int>> T = t; 
    for (int k = 0;k < scc_num; k++)
    {
        for (int i = 0;i < scc_num; i++)
        {
            for (int j = 0;j < scc_num; j++)
            {
                if (T[i][j] == 1 || (T[i][k] == 1 && T[k][j] == 1))
                    t[i][j] = 1;
                else
                    t[i][j] = 0;
            }
        }
        T = t;
    }
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> u >> v;
        int scc_u = scc_in[u - 1];
        int scc_v = scc_in[v - 1];
        cout << T[scc_u][scc_v] << endl;
    }
    return 0;
}