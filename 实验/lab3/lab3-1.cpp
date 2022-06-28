#include <bits/stdc++.h>
using namespace std;

#define max_value 1000000001

typedef struct node
{
    long long value;        // 结点值
    long long front = 0;       // 以该结点在前的逆序对数
    long long behind = 0;       // 以该结点在后的逆序对数
    long long pos;      // 该结点在数组中的原位置
}node;


node A[1000001];

long long merge(node A[], long long p, long long q, long long r)
{
    long long count_1 = 0, count_2 = 0, count_3 = 0;
    long long i, j;
    long long n1 = q - p + 1;
    long long n2 = r - q;
    node L[n1 + 1], R[n2 + 1];
    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];
    L[n1].value = max_value;
    R[n2].value = max_value;
    i = 0;
    j = 0;
    for (long long k = p ; k <= r; k++)
        if (L[i].value <= R[j].value){
            A[k] = L[i];
            // aj > ai > ak，ij在左，k在右
            count_1 = count_1 + (n1 - (A[k].pos - p) - 1 - A[k].front) * (k - p - i);
            A[k].front += k - p - i;
            i++;
        }
        else{
            A[k] = R[j];
            // aj > ak > ai
            count_2 = count_2 + (A[k].behind) * (k - p - j);
            // aj > ak,aj > ai
            count_3 = count_3 + (A[k].front) * (k - p - j);
            A[k].behind += (j + n1 - k + p);
            j++;
        }
    return count_1 + count_3 - count_2;
}

long long MERGESORT(node A[],long long p,long long r){
     if(p < r)
     {
         long long q = (p + r)/2;
         long long count = 0;
         count += MERGESORT(A, p, q);
         count += MERGESORT(A, q + 1, r);
         count += merge(A, p, q, r);
         return count;
     }
     return 0;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i].value;
        A[i].pos = i;
    }
    cout << MERGESORT(A, 0, n - 1);
    return 0;
}