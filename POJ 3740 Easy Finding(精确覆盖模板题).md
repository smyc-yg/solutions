# POJ 3740 Easy Finding(精确覆盖模板题)

## 题目大意

给定一个`M*N`的01矩阵，能否找到一个行的集合，使得集合中每一列都恰好包含一个1。

## 解题思路

### (一) dfs

从第一行开始深度优先搜索，将与当前已选行无冲突的行加入集合并进行标记(确保集合中不会出现同一列存在多个1的情况)，当所有列均有1时找到答案。

### (二) 二进制枚举

**大致思路：**
二进制枚举，再用**位运算**来判断所选的行是否满足每列只有一个1的限定。

1. 用int型数组的每个二进制位表示每一列的状态。(由于`m <= 16`，32位的int完全够用，此处时间复杂度为`2^16*m`，可以接受。)
比如某一列的第二行有一个`1`，那么数组中表示该列的数字的第二个二进制位就为`1`。
2. 判断第j列是否恰好包含一个`1`：
1> 令`t = col[j]&i`(i表示枚举的行的二进制状态)，这样就把枚举的行里面的1取了出来。
如果`t==0`，说明枚举的这些行对应的某列里面不包含`1`，不满足条件；否则，表示这些行对应的第j列**包含`1`**，需进一步判断。
2> 进行操作`t&(t-1)`，若`t&(t-1)==0`则**恰好包含一个`1`**，否则不满足条件。

### (三) 舞蹈链(Dancing Links)

精确覆盖的经典模板题

## 代码

### (一) dfs

```c++
#include <cstdio>
#include <cstring>

using namespace std;

int a[20][305], m, n;
bool vis[310], f;

//判断所选的行的集合中是否每一列都存在1
bool judge() {
    for(int i = 1; i <= n; i++)
        if(!vis[i]) return false;
    return true;
}

//当前行加入集合的条件：是否有与之前已选的行在某一列有冲突(该列包含多个1)
bool check(int Row) {
    for(int i = 1; i <= n; i++)
        if(vis[i] && a[Row][i]) return false; //如果都有1的话，不满足题意，回溯。
    for(int i = 1; i <= n; i++)
        if(a[Row][i]) vis[i] = true; //如果不冲突的话，则把这一行用上，并把它所有包含1的列都标记上。
    return true;
}

void dfs(int Col) {
    if(f || Col > m + 1) return; //判断退出的标志，即输出的结果，或者行数已经超过了n+1。
    if(judge()) {
        printf("Yes, I found it\n");
        f = true;
        return;
    }
    for(int i = Col; i <= m && !f; i++) {
        if(check(i)) {
            dfs(i + 1);
            for(int j = 1; j <= n; j++) //不要忘记回溯
                if(a[i][j]) vis[j] = false;
        }
    }
}

int main() {
    while(scanf("%d%d", &m, &n) != EOF) {
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &a[i][j]);
        f = false;
        memset(vis, false, sizeof(vis));
        dfs(1);
        if(!f) printf("It is impossible\n");
    }
    return 0;
}

```

### (二) 二进制枚举

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int Col[305]; //Col[j]的第i个二进制位为1 表示位置(i, j)上为1

int main() {
    int m, n; //m行n列
    while(scanf("%d%d", &m, &n) != EOF) {
        int f = 0;
        memset(Col, 0, sizeof(Col));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int x;
                scanf("%d", &x);
                if(x) Col[j] += (1 << i); //二进制存储
                //若对于所有行来说，某一列一个1都没有，则一定不满足条件
                if(i == m - 1 && Col[j] == 0) f = 1;
            }
        }
        if(f) {
            printf("It is impossible\n");
            continue;
        }
        for(int i = 1; i < (1 << m); i++) { //遍历行
            int tmp = 0;
            for(int j = 0; j < n; j ++) {
                //判断是否恰好包含一个1
                int t = Col[j] & i; //t的含义见解析部分
                //排除不包含1和包含多个1的情况
                if(t == 0 || (t & (t-1))) {
                    tmp = 1;
                    break;
                }
            }
            if(!tmp) {
                f = 1;
                break;
            }
        }
        if(f) printf("Yes, I found it\n");
        else printf("It is impossible\n");
    }
    return 0;
}
```

### (三) 舞蹈链(Dancing Links)

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN = 505;
const int M = MAXN * MAXN; //最大节点数

struct DLX {
    int n, m, s; //n行m列，s表示节点数
    //Left[]指向左边的元素、Right[]指向右边的元素、Up[]指向上边的元素、Down[]指向下边的元素
    //Col[]指向列标元素、Row[]表示当前元素所在的行
    int Up[M], Down[M], Left[M], Right[M], Col[M], Row[M];
    int Head[MAXN]; //Head[]表示行首指针，当Head[0] = 0时，链表为空
    int S[MAXN]; //S[i]表示第i列中的节点数
    int ansR, ans[MAXN];//ansR表示答案所包含的行数，ans[]记录答案

    //初始化,构建空的十字链表
    void pre(int _n, int _m) {
        n = _n, m = _m;
        for(int i = 0; i <= m; i++) {
            //其实对于列首元素而言，并不需要Up、Down指向，这里为了方便就一起写了
            Up[i] = i;
            Down[i] = i;
            Left[i] = i - 1;
            Right[i] = i + 1;
            Col[i] = i;
            Row[i] = 0; //列首元素统一放在第0行
            S[i] = 0; //初始时每列节点数清零
        }
        Left[0] = m;
        Right[m] = 0;
        s = m; //从m号元素后就表示普通元素
        for(int i = 0; i <= n; i++) {
            Head[i] = -1;
            ans[i] = 0;
        }
        ansR = 0;
    }

    //在第r行，第c列的位置添加新的节点(注意这里是向下插入、行是前插法)
    void Insert(int r, int c) {
        s++; //节点数+1
        Down[s] = Down[c]; //新节点的下侧指针指向列标元素下边的节点
        Up[s] = c; //新节点的上侧指针指向列标元素
        Up[Down[c]] = s; //原来在列标元素下边的节点的上侧指针指向新节点
        Down[c] = s; //列标元素的下侧指针指向新节点
        //新节点位于第r行，第c列
        Row[s] = r;
        Col[s] = c;
        S[c]++; //第c列的节点数+1
        //如果插入成该行第一个元素
        if(Head[r] < 0) {
            Head[r] = s; //该行第一个元素为新节点
            //它的Right、Left均没有节点
            Right[s] = s;
            Left[s] = s;
        }
        else {
            Left[s] = Head[r]; //新节点的左侧指针指向这一行的第一个节点
            Right[s] = Right[Head[r]]; //新节点的右侧指针指向这一行第一个节点右边的节点
            Left[Right[Head[r]]] = s; //这一行第一个节点右边的节点的左侧指针指向新节点
            Right[Head[r]] = s; //这一行的第一个节点的右侧指针指向新节点
        }
    }

    //将某一列及该列上节点所在的行从链表中暂时删掉
    void Remove(int c) {
        Left[Right[c]] = Left[c]; //第c列右边一列的左侧指针指向第c列的左边一列
        Right[Left[c]] = Right[c]; //第c列左边一列的右侧指针指向第c列的右边一列
        //对于这一列的每个节点
        for(int i = Down[c]; i != c; i = Down[i]) {
            //遍历该节点所在行上的所有节点
            for(int j = Right[i]; j != i; j = Right[j]) {
                //逐一删除节点j
                Up[Down[j]] = Up[j]; //在节点j下边的那个节点的上侧指针指向节点j上边的节点
                Down[Up[j]] = Down[j]; //在节点j上边的那个节点的下侧指针指向节点j下边的节点
                --S[Col[j]]; //节点j所在的那一列的节点数-1
            }
        }
    }

    //将 第c列及该列上节点所在的行 重新加入链表
    void Resume(int c) {
        //对于第c列上的每个节点i
        for(int i = Up[c]; i != c; i = Up[i]) {
            //遍历节点i所在行的每个节点j
            for(int j = Left[i]; j != i; j = Left[j]) {
                Down[Up[j]] = j; //节点j上边节点的下侧指针 指向节点j
                Up[Down[j]] = j; //节点j下边节点的上侧指针 也指向节点j
            }
        }
        Right[Left[c]] = c; //第c列左边一列的列标元素 的右侧指针 指向第c列
        Left[Right[c]] = c; //第c列右边一列的列标元素 的左侧指针 指向第c列
    }

    //核心代码，本质是dfs，Deep表示搜索深度
    bool Dance(int Deep) {
        //当Head.Right == Head时结束
        if(Right[0] == 0) {
            ansR = Deep;
            return true;
        }
        int c = Right[0]; //获取Head.Right指向的列标元素，作为搜索起点
        //下面这个for循环是用来找到当前状态中节点数最少的那一列
        for(int i = Right[0]; i != 0; i = Right[i]) //链表常规操作，不断读取当前元素的右侧指向
            if(S[i] < S[c]) c = i;
        Remove(c); //将选定的这一列从十字双向链表中删掉
        //对于这一列的每个节点
        for(int i = Down[c]; i != c; i = Down[i]) {
            ans[Deep] = Row[i]; //将节点i所在的行记录进答案
            //移除所有 与节点i在同一行的节点j们 所在的那一列
            for(int j = Right[i]; j != i; j = Right[j])
                Remove(Col[j]);
            //找到答案，退出
            if(Dance(Deep + 1)) return true;
            //否则，回溯
            for(int j = Left[i]; j != i; j = Left[j])
                Resume(Col[j]);
        }
        Resume(c); //退出搜索前别忘了回溯c的状态
        return false;
    }
}dlx;

void deal(int n, int m) {
    dlx.pre(n, m); //初始化
    //读入原矩阵，只存储1的信息
    for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
            int x;
			scanf("%d", &x);
			if(x) dlx.Insert(i, j);	//将每个位于(i, j)的1 加到矩阵、链表中
		}
	}
	if(!dlx.Dance(0)) printf("It is impossible\n");
	else printf("Yes, I found it\n");
}

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
        deal(n, m);
    return 0;
}
```

## 参考资料

1. [POJ 3740](https://www.cnblogs.com/wangzhili/p/3950237.html)
2. [POJ 3740](cnblogs.com/Tree-dream/p/5509977.html)
