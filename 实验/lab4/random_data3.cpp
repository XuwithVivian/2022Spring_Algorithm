#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n = 32, m = 640, edge, w;
    int num = m / n;
    ofstream outfile;
    vector<unordered_set<int>> s(n);
    outfile.open("file3.txt");
    outfile << n << " " << m << endl;
    srand((unsigned)time(NULL));
    for (int i = 1; i <= n; i++)
    {
        // srand((unsigned)time(NULL));
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
    outfile.close();
    return 0;
}