/*
重点在于问题转换部分，理解行列的定义，其余就是纯 Dancing Links X
*/
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN = 3010; //最大节点数
int a[10][10];

struct DLX {
    int n, m, s; //n行m列，s表示节点数
    //Left[]指向左边的元素、Right[]指向右边的元素、Up[]指向上边的元素、Down[]指向下边的元素
    //Col[]指向列标元素、Row[]表示当前元素所在的行
    int Up[MAXN], Down[MAXN], Left[MAXN], Right[MAXN], Col[MAXN], Row[MAXN];
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
        //memset(Head, -1, sizeof(Head));
        //memset(ans, 0, sizeof(ans));
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
                ++S[Col[j]];
            }
        }
        Right[Left[c]] = c; //第c列左边一列的列标元素 的右侧指针 指向第c列
        Left[Right[c]] = c; //第c列右边一列的列标元素 的左侧指针 指向第c列
    }

    //核心代码，本质是dfs，Deep表示搜索深度
    bool Dance(int Deep) {
        //当Head.Right == Head本身时 结束
        if(Right[0] == 0) {
            int x, y, v; //(x, y)处值为v
			for(int i = 0; i < Deep; i++) {
                //把行信息转换成对应的点的信息
                x = (ans[i] - 1) / 9 / 9;
                y = (ans[i] - 1) / 9 % 9;
                v = ans[i] % 9;
                if(v == 0) v = 9; //防止9的倍数%9==0
                    a[x][y] = v;
			}
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

int main() {
    int n = 729, m = 324;
    dlx.pre(n, m); //初始化
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            scanf("%d", &a[i][j]);
            for(int k = 1; k <= 9; k++) {
                if(a[i][j] != k && a[i][j]) continue; //已经填好的数直接跳过
                int id = i * 9 * 9 + j * 9 + k;
                int c1, c2, c3, c4;
                c1 = i * 9 + j + 1;
                c2 = i * 9 + 81 + k;
                c3 = j * 9 + 81 * 2 + k;
                c4 = 81 * 3 + (i / 3 * 3 + j / 3) * 9 + k;
                dlx.Insert(id, c1);
                dlx.Insert(id, c2);
                dlx.Insert(id, c3);
                dlx.Insert(id, c4); //连接行列
            }
        }
    }
    dlx.Dance(0);
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++)
            printf("%d ", a[i][j]);
		printf("\n");
	}
    return 0;
}
