/*
这里用A*算法求解，对估价函数确定如下：

1. h = 从当前位置到目标位置之间的曼哈顿距离 * 10。
2. 由于按照“日”字形移动，每走一步的花费g = ceil((根号下(2 * 2 + 1 * 1)) * 10)，约为23。
3. 核心方程 -- f'(n) = g'(n) + h'(n)
*/
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>

int bx, by, ex, ey;
int ans;
bool vis[8][8];
int to_x[8] = {1, 2, 1, 2, -1, -2, -1, -2};
int to_y[8] = {2, 1, -2, -1, 2, 1, -2, -1};

struct Node{
	int x, y; //横纵坐标(x, y)
	int deep; //当前深度
	int g; //从起点移动到当前方格的花费
	int h; //估价函数
	int f; //启发式函数
	bool operator < (const Node & u) const //根据启发式函数f的大小，为优先队列重载运算符'<'
	{
		return f > u.f;
	}
}k;

inline int gujia(Node u) //估价函数h = 点u与终点之间的曼哈顿距离 * 10
{
	return (abs(u.x - ex) + abs(u.y - ey)) * 10;
}

void pre()
{
    memset(vis, 0, sizeof(vis));
	k.x = bx, k.y = by; //起点坐标(k.x, k.y)
	k.g = 0; //起点的原始花费为0
	k.deep = 0; //起点深度值初始化为0
	k.h = gujia(k); //估价函数
	k.f = k.g + k.h; //启发式函数F = G + H
}

void A_Star() //A*算法
{
    pre();
    std::priority_queue<Node> q;
    q.push(k);
	while(!q.empty())
    {
		Node u = q.top();
		q.pop();
		vis[u.x][u.y] = 1;
		if(u.x == ex && u.y == ey)//访问到终点时，返回当前深度并退出搜索
		{
			ans = u.deep;
            break;
		}
		for(int i = 0; i < 8; i++)
        {
			Node v;
			v.x = u.x + to_x[i];
			v.y = u.y + to_y[i];
			if(v.x < 0 || v.x >= 8 || v.y < 0 || v.y >= 8)
                continue;
			if(!vis[v.x][v.y]) //v未被访问过
            {
				v.g = u.g + 23; //每走一步的花费约为23，说明如上
				v.h = gujia(v);
				v.f = v.g + v.h;
				v.deep = u.deep + 1;
				q.push(v);
			}
		}
	}
}
int main()
{
    char a[10], b[10];
    while(scanf("%s%s", a, b) != EOF)
    {
        bx = a[0] - 'a', by = a[1] - '1';
        ex = b[0] - 'a', ey = b[1] - '1';
		A_Star();
		printf("To get from %s to %s takes %d knight moves.\n", a, b, ans);
	}
	return 0;
}
