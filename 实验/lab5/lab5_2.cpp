#include<bits/stdc++.h>
using namespace std;

#define MAX 0x7fffffff

// 边结构体
struct edge
{
    int v;
    int w;
};

int sub, num = 0, result = 0;

// 寻找增广路径
bool dfs(vector<vector<int>> &len, int u, vector<vector<edge>> &edges, vector<int> &match, vector<int> &w, vector<int> &visited, int s, int t)
{
    visited[u] = 1;
    for (int i = 0; i < edges[u].size(); i++)
    {
        if (!visited[edges[u][i].v])
        {
            int value = w[u] + w[edges[u][i].v] - edges[u][i].w;
            if (value == 0)
            {
                visited[edges[u][i].v] = 1;
                if (match[edges[u][i].v] == -1 || dfs(len, match[edges[u][i].v], edges, match, w, visited, s, t))
                {
                    match[u] = edges[u][i].v;
                    match[edges[u][i].v] = u;
                    return true;
                }
            }
            else if (value > 0 && sub > value)
            {
                sub = value;
            }
        }
    }
    return false;
}

// 类匈牙利算法
void Kuhn_Munkras(vector<vector<int>> &len, vector<vector<edge>> &edges, vector<int> &match, vector<int> &w, vector<int> &visited, int s, int t)
{
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < edges[i].size(); j++)
        {
            if (w[i] < edges[i][j].w)
                w[i] = edges[i][j].w;
        }
    }
    for (int i = 0; i < s; i++)
    {
        while(1)
        {
            sub = MAX;
            std::fill(visited.begin(), visited.end(), 0);
            if (dfs(len, i, edges, match, w, visited, s, t))
                break;
            // 改变顶标值
            for (int j = 0; j < s + t; j++)
            {
                if (visited[j] && j < s)
                    w[j] -= sub;
                if (visited[j] && j >= s)
                    w[j] += sub;
            }
        }
    }
    for (int i = 0; i < s; i++)
    {
        if (match[i] != -1)
        {
            result += len[i][match[i]];
            num++;
        }
    }
}

int main()
{
    int s, t, m, u, v, c;
    cin >> s >> t >> m;
    vector<vector<edge>> edges(s + t);
    vector<int> match(s + t, -1);
    vector<int> w(s + t, 0);
    vector<int> visited(s + t);
    vector<vector<int>> len(s + t, vector<int>(s + t, MAX));
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> c;
        edges[u - 1].push_back({v - 1, -c});
        len[u - 1][v - 1] = c;
    }
    Kuhn_Munkras(len, edges, match, w, visited, s, t);
    cout << num << " " << result;
    return 0;
}