#include<bits/stdc++.h>
using namespace std;

#define MAX 0x7FFFFFFF

// 边的结构体
typedef struct edge {
	int u;
	int v;
	int w;
	bool operator < (const edge a) const {
		return this->w < a.w;
	}
}edge;

// 返回所在集合
int findset(int p[], int x) {
	if (x != p[x]) {
		p[x] = findset(p, p[x]);
	}
	return p[x];
}

// 取较小值
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    int m, n, u, v, w;
    int result_1 = 0, result_2 = MAX;
    cin >> n >> m;
    vector<int> G[n + 1];
    edge* E = new edge[m];
    int p[n + 1], use[m], max_value[n + 1][n + 1];
    for (int i = 0; i < m; i++)
    {
        cin >> E[i].u >> E[i].v >> E[i].w;
    }
    for (int i = 1; i <= n; i++)
    {
        G[i].clear();
        G[i].push_back(i);
		p[i] = i;
	}
    sort(E, E + m);
    int i = 0, j = 0;
    while (i < m)       // kruskal算法求最小生成树

    {
        int p1 = findset(p, E[i].u);
        int p2 = findset(p, E[i].v);
        if (p1 == p2)
        {
            i++;
            continue;
        }
        else 
        {
            j++;
            use[i] = 1;
            result_1 += E[i].w;
            p[p2] = p1;
            for (int a = 0; a < G[p1].size(); a++)
                for (int b = 0; b < G[p2].size(); b++)
                {
                    max_value[G[p1][a]][G[p2][b]] = E[i].w;
                    max_value[G[p2][b]][G[p1][a]] = E[i].w;
                }
            for (int a = 0; a < G[p2].size(); a++)
                G[p1].push_back(G[p2][a]);
        }
        if (j == n - 1)
            break;
        i++;
    }
    for (int i = 0; i < m; i++)     // 从不在最小生成树中的边加入树中并去掉环中最长的路
    {
        if (use[i] != 1)
            result_2 = min(result_2, result_1 + E[i].w - max_value[E[i].u][E[i].v]);
    }
    cout << result_1 << endl << result_2;
    return 0;
}
