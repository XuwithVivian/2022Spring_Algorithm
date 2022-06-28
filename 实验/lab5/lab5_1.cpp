#include<bits/stdc++.h>
using namespace std;

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

struct edge
{
    int v;
    int w;
};

// 查找最短路径
void shortestpath(vector<vector<int>> &value, int n, vector<vector<edge>> &edges)
{
    value[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < edges[j].size(); k++)
            {
                if (value[i - 1][edges[j][k].v] != -1)
                {
                    if (value[i][j] == -1)
                        value[i][j] = value[i - 1][edges[j][k].v] + edges[j][k].w;
                    else
                        value[i][j] = min(value[i][j], value[i - 1][edges[j][k].v] + edges[j][k].w);
                }
            }
        }
    }
}

// 查找最短平均权重
double min_averge_value(vector<vector<int>> &value, int n, vector<vector<edge>> &edges)
{
    double weight[n] = {-1};
    for (int i = 0; i < n; i++)
    {
        if (value[n][i] != -1)
        {
            for (int j = 0; j < n; j++)
                if (value[j][i] != -1) {
                    if (weight[i] < ((double)value[n][i] - value[j][i]) / (n - j))
                    {   
                        weight[i] = ((double)value[n][i] - value[j][i]) / (n - j);
                    }
                }
        }
    }
    double result = weight[0];
    for (int i = 0; i < n; i++)
    {
        if (weight[i] != -1 && weight[i] < result) {
            result = weight[i];
        }
    }
    return result;
}

int main()
{
    int n, m, u, v, w;
    cin >> n >> m;
    vector<vector<edge>> edges(n);
    vector<vector<int>> value(n + 1, vector<int>(n, -1));
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        edges[u - 1].push_back({v - 1, w});
    }
    shortestpath(value, n, edges);
    double result = min_averge_value(value, n, edges);
    // 将结果保留3位小数
    cout << setiosflags(ios::fixed) << setprecision(3) << result;
    return 0;
}