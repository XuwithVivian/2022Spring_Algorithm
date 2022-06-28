#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<stddef.h>
#include<string>

using namespace std;
// 哈希表结点
typedef struct hash_node{
    int pos;    // 记录堆结点下标
}hash_node;
// 堆结点
typedef struct heap_node{
    int key;
    string name;
}heap_node;

hash_node hash_table[42772886];     // 哈希表
heap_node heap[700000];     // 堆数组
string name[700000];       // 储存最高成绩的名字
int max_name = 0;       // 储存最高成绩的人数

// 对每个字符串得到唯一的数组下标
int SDBMHash(string a)
{
    int sum = 0, digit = 1;
    for (int i = 0; i < a.size(); i++)
    {
        if (i == 0)
            sum = sum + (a[i] - 'A') * digit;
        else
            sum = sum + a[i] * digit;
        digit *= 26;
    }
    return sum;
}

// 将字符串转换成整型数用于基数排序
int transtoint(string a)
{
    int sum = 0, digit = 26 * 26 * 26 * 26;
    for (int i = 0; i < a.size(); i++)
    {
        sum = sum + (a[i] - 'A' + 1) * digit;
        digit /= 26;
    }
    return sum;
}

int heap_size = 0;      // 堆大小

// 获取父结点下标
int parent(int i)
{
    if ((i - 1) % 2 == 0)
        return (i - 1) / 2;
    else 
        return (i - 2) / 2;
}

// 获取左孩子下标
int left(int i)
{
    return 2 * i + 1;
}

// 获取右孩子下标
int right(int i)
{
    return 2 * i + 2;
}

// 交换堆结点
void swap(heap_node a[], int i, int j)
{
    int swap_key;
    string swap_name;
    hash_table[SDBMHash(a[i].name)].pos = j;
    hash_table[SDBMHash(a[j].name)].pos = i;
    swap_key = a[i].key;
    a[i].key = a[j].key;
    a[j].key = swap_key;
    swap_name = a[i].name;
    a[i].name = a[j].name;
    a[j].name = swap_name;
}

// 交换堆结点，哈希位置不交换
void swap_1(heap_node a[], int i, int j)
{
    int swap_key;
    string swap_name;
    swap_key = a[i].key;
    a[i].key = a[j].key;
    a[j].key = swap_key;
    swap_name = a[i].name;
    a[i].name = a[j].name;
    a[j].name = a[i].name;
}

// 维护堆性质
void max_heapify(heap_node a[], int i)
{
    int l = left(i);
    int r = right(i);
    int largest;
    if (l < heap_size && (a[l].key > a[i].key))
        largest = l;
    else
        largest = i;
    if (r < heap_size && (a[r].key > a[largest].key))
        largest = r;
    if (largest != i)
    {
        swap(a, i, largest);
        max_heapify(a, largest);
    }
}

// 增大堆结点的值
int heap_increase_key(heap_node a[], int i, int key)
{
    if (key < a[i].key)
        printf("new key is smaller than current key");
    a[i].key = key;
    while (i > 0 && a[parent(i)].key < a[i].key)
    {
        swap(a, i, parent(i));
        i = parent(i);
    }
    return i;
}

// 插入堆结点
int max_heap_insert(heap_node a[], int key, string name)
{
    heap_size++;
    a[heap_size - 1].name = name;
    a[heap_size - 1].key = -1;
    hash_table[SDBMHash(name)].pos = heap_size - 1;
    int i = heap_increase_key(a, heap_size - 1, key);
    return i;
}

// 删除最大堆结点
int heap_extract_max(heap_node a[])
{
    if (heap_size < 1)
        printf("heap underflow");
    int max = a[0].key;
    swap_1(a, 0, heap_size - 1);

    heap_size--;
    max_heapify(a, 0);
    return max;
}

// 删除堆结点
void delete_heap_node(heap_node a[], int i)
{
    heap_increase_key(a, i, 200);
    int max = heap_extract_max(a);
}

// 将最高成绩名字存入字符串数组
void store_name(heap_node a[], int pos)
{
    if (left(pos) < heap_size)
    {
        if (a[left(pos)].key == a[pos].key)
        {
            name[max_name++] = a[left(pos)].name;
            store_name(a, left(pos));
        }
    }
    if (right(pos) < heap_size)
    {
        if (a[right(pos)].key == a[pos].key)
        {
            name[max_name++] = a[right(pos)].name;
            store_name(a, right(pos));
        }
    }
}

// 计数排序，用于对每一十进制位排序
void counting_sort(string array[], int n, int digit)
{
    int temp[10] = {0}, i, num;     // 提供临时存储空间
    string store[n];        // store数组存放排序的输出,num用于存储所需排序位上的数
    for (i = 0; i < n; i++)
    {
        num = (transtoint(array[i]) / digit) % 10;
        temp[num]++;
    }
    for (i = 1; i < 10; i++)
        temp[i] = temp[i] + temp[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        num = (transtoint(array[i]) / digit) % 10;
        store[temp[num] - 1] = array[i];
        temp[num]--;
    }
    for (i = 0; i < n; i++)     // 将储存在Store数组中的元素移入array数组
        array[i] = store[i];
}

// 基数排序函数
void radixsort(string array[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (transtoint(array[i]) > max)
            max = transtoint(array[i]);
    }   // 寻找数组中最大元素
    for (int digit = 1; max / digit != 0; digit = digit * 10)   // digit表示排序的位
    {
        counting_sort(array, n, digit);     // 调用计数排序对每一位进行排序
        if (digit == 1000000000)    // 若到达digit所能到达最大位则终止，防止digit溢出
            break;
    }
}

// 打印最高成绩名字
void print(heap_node a[])
{
    max_name = 0;
    name[max_name++] = a[0].name;
    store_name(a, 0);
    radixsort(name, max_name);      // 基数排序
    for (int i = 0; i < max_name; i++)
        cout << name[i] << endl;
}

int main()
{
    int m, a, pos;
    int result;
    char op;
    string name;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        if (op == 'I')
        {
            cin >> name >> a;
            pos = max_heap_insert(heap, a, name);
        }
        else if (op == 'D')
        {
            cin >> name;
            pos = hash_table[SDBMHash(name)].pos;
            delete_heap_node(heap, pos);
            hash_table[SDBMHash(name)].pos = -1;
        }
        else if (op == 'S')
        {
            cin >> name;
            if (heap[hash_table[SDBMHash(name)].pos].key > 0 && heap[hash_table[SDBMHash(name)].pos].name == name)
                cout << heap[hash_table[SDBMHash(name)].pos].key << endl;
            else
                cout << 0 << endl;
        }
        else if (op == 'F')
        {
            print(heap);
        }
    }
    return 0;
}