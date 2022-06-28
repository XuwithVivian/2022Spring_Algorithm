#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// 红黑树结点结构体
typedef struct RBT_node
{
    int color;
    int key;
    int size;
    struct RBT_node *left;
    struct RBT_node *right;
    struct RBT_node *p;
} RBT_node;

// 红黑树结构体
typedef struct RBT
{
    RBT_node *root;
    RBT_node *nil;
} RBT;

// 初始化红黑树
RBT *INIT_RBT(void) 
{
	RBT *T;
	T = (RBT *)malloc(sizeof(RBT));
	T->nil = (RBT_node *)malloc(sizeof(RBT_node));
	T->nil->color = 1;
	T->nil->left = T->nil->right = T->nil->p = NULL;
    T->nil->size = 0;
	T->root = T->nil;
	return T;
}

// 左旋
void LEFT_ROTATE(RBT *T, RBT_node *x)
{
	RBT_node* y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else x->p->right = y;
	y->left = x;
	x->p = y;
    y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

// 右旋
void RIGHT_ROTATE(RBT *T, RBT_node *x) 
{
	RBT_node* y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else x->p->right = y;
	y->right = x;
	x->p = y;
    y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

void RB_INSERT_FIXUP(RBT *T, RBT_node *z) 
{ 
	RBT_node* y;
	while (z->p->color == 0)
		if (z->p == z->p->p->left) 
        {
			y = z->p->p->right;
			if (y->color == 0) 
            {
				z->p->color = 1;
				y->color = 1;
				z->p->p->color = 0;
				z = z->p->p;
			}
			else 
            {
				if (z == z->p->right) 
                {
					z = z->p;
					LEFT_ROTATE(T, z);
				}
				z->p->color = 1;
				z->p->p->color = 0;
				RIGHT_ROTATE(T, z->p->p);
			}
		}
		else 
        {
			y = z->p->p->left;
			if (y->color == 0) 
            {
				z->p->color = 1;
				y->color = 1;
				z->p->p->color = 0;
				z = z->p->p;
			}
			else 
            {
				if (z == z->p->left) 
                {
					z = z->p;
					RIGHT_ROTATE(T, z);
				}
				z->p->color = 1;
				z->p->p->color = 0;
				LEFT_ROTATE(T, z->p->p);
			}
		}
	T->root->color = 1;
}

// 插入节点
void RB_INSERT(RBT *T, RBT_node *z) {
	RBT_node *y = T->nil;
    RBT_node *x= T->root; 
	while (x != T->nil){
        x->size++;
		y = x;
		if (z->key < x->key) 
			x = x->left;
		else x = x->right;
	}
	z->p = y;
	if (y == T->nil) 
		T->root = z;
	else if (z->key < y->key) 
		y->left = z;
	else 
        y->right = z;
	z->left = z->right = T->nil;
	z->color = 0;
    z->size = 1;
	RB_INSERT_FIXUP(T, z);
}

void RB_TRANSPLANT (RBT *T, RBT_node *u, RBT_node *v)
{
    if (u->p == T->nil)
    {
        T->root = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }
    v->p = u->p;
}

void RB_DELETE_FIXUP (RBT *T, RBT_node *x)
{
    RBT_node *w;
    while ((x != T->root) && (x->color == 1))
    {
        if (x == x->p->left)
        {
            w = x->p->right;
            if (w->color == 0)
            {
                w->color = 1;
                x->p->color = 0;
                LEFT_ROTATE(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == 1) && (w->right->color == 1))
            {
                w->color = 0;
                x = x->p;
            }
            else
            {
                if (w->right->color == 1)
                {
                    w->left->color = 1;
                    w->color = 0;
                    RIGHT_ROTATE(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = 1;
                w->right->color = 1;
                LEFT_ROTATE(T, x->p);
                x = T->root;
            }
        }
        else
        {
            w = x->p->left;
            if (w->color == 0)
            {
                w->color = 1;
                x->p->color = 0;
                RIGHT_ROTATE(T, x->p);
                w = x->p->left;
            }
            if ((w->left->color == 1) && (w->right->color == 1))
            {
                w->color = 0;
                x = x->p;
            }
            else
            {
                if (w->left->color == 1)
                {
                    w->right->color = 1;
                    w->color = 0;
                    LEFT_ROTATE(T, w);
                    w = x->p->left;
                }
                w->color = w->p->color;
                x->p->color = 1;
                w->left->color = 1;
                RIGHT_ROTATE(T, x->p);
                x = T->root;
            }
        }
    }
    x->color = 1;
}

// 查找最小结点
RBT_node *TREE_MINIMUM(RBT *T, RBT_node *x)
{
    while (x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}

// 查找最大结点
RBT_node *TREE_MAXIMUM(RBT *T, RBT_node *x)
{
    while (x->right != T->nil)
    {
        x = x->right;
    }
    return x;
}

// 删除结点
void RB_DELETE (RBT *T, RBT_node *z)
{
    RBT_node *y = z;
    int y_original_color = y->color;
    RBT_node *x, *v = z->p;
    if (z->left == T->nil)
    {
        while(v != T->nil)
        {
            v->size--;
            v = v->p;
        }
        x = z->right;
        RB_TRANSPLANT(T, z, z->right);
    }
    else if (z->right == T->nil)
    {
        while(v != T->nil)
        {
            v->size--;
            v = v->p;
        }
        x = z->left;
        RB_TRANSPLANT(T, z, z->left);
    }
    else
    {
        y = TREE_MINIMUM(T, z->right);
        v = y->p;
        y->size = z->size - 1;
        while(v != T->nil)
        {
            v->size--;
            v = v->p;
        }
        y_original_color = y->color;
        x = y->right;
        if (y->p == z)
        {
            x->p = y;
        }
        else
        {
            RB_TRANSPLANT(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        RB_TRANSPLANT(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (y_original_color == 1)
    {
        RB_DELETE_FIXUP(T, x);
    }
    free(z);
}

// 查找第k大元素
int OS_SELECT(RBT_node *x, int k)
{
    int r = x->right->size + 1;
    if (k == r)
        return x->key;
    else if (k < r)
        return OS_SELECT(x->right, k);
    else
        return OS_SELECT(x->left, k - r);
}

RBT_node *TREE_PREDECESSOR(RBT *T, RBT_node *x)
{
    if (x->left != T->nil)
        return TREE_MAXIMUM(T, x->left);
    RBT_node *y = x->p;
    while (y != T->nil && x == y->left)
    {
        x = y;
        y = y->p;
    }
    return y;
}

// 查询大于a的最小元素
int FIND_A(RBT *T, RBT_node *x, int a)
{
    RBT_node *curr = T->root, *ans = T->nil;
 
    while (curr != T->nil) {
        if (curr->key > a) {
            ans = curr;
            curr = curr->left;
        }      
        else if (curr->key == a) {
            ans = curr;
            break;
        }
        else 
            curr = curr->right;
    }
    if (ans != T->nil)
       return ans->key;
    return -1;
}

// 查询小于等于k的元素个数
int FIND_k(RBT *T, RBT_node *x, int k)
{
    if (x ==T->nil)
        return 0;
    if (x->key <= k)
        return FIND_k(T, x->right, k) + x->left->size + 1;
    else
        return FIND_k(T, x->left, k);
}

// 查询[l,r]区间的元素个数
int FIND_LR(RBT *T, int l, int r)
{
    return FIND_k(T, T->root, r) - FIND_k(T, T->root, l - 1);
}

// 根据元素查找结点
RBT_node *TREE_SEARCH(RBT *T, RBT_node *x, int k)
{
    if (x == T->nil || x->key == k)
        return x;
    if (k < x->key)
        return TREE_SEARCH(T, x->left, k);
    else
        return TREE_SEARCH(T, x->right, k);
}

int main()
{
    int m, a, result, l, r;
    char op;
    RBT *T = INIT_RBT();
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        while(getchar() == '\n')
        scanf("%c", &op);
        if (op == 'I')
        {
            scanf("%d", &a);
            RBT_node *z = (RBT_node *)malloc(sizeof(RBT_node));
            z->key = a;
            RB_INSERT(T, z);
        }
        else if (op == 'D')
        {
            scanf("%d", &a);
            RBT_node *z = TREE_SEARCH(T, T->root, a);
            RB_DELETE(T, z);
        }
        else if (op == 'S')
        {
            scanf("%d", &a);
            result = OS_SELECT(T->root, a);
            printf("%d\n", result);
        }
        else if (op == 'L')
        {
            scanf("%d", &a);
            result = FIND_A(T, T->root, a);
            printf("%d\n", result);
        }
        else if (op == 'T')
        {
            scanf("%d %d", &l, &r);
            result = FIND_LR(T, l, r);
            printf("%d\n", result);
        }
    }
    return 0;
}