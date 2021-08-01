/*
������A*�㷨��⣬�Թ��ۺ���ȷ�����£�

1. h = �ӵ�ǰλ�õ�Ŀ��λ��֮��������پ��� * 10��
2. ���ڰ��ա��ա������ƶ���ÿ��һ���Ļ���g = ceil((������(2 * 2 + 1 * 1)) * 10)��ԼΪ23��
3. ���ķ��� -- f'(n) = g'(n) + h'(n)
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
	int x, y; //��������(x, y)
	int deep; //��ǰ���
	int g; //������ƶ�����ǰ����Ļ���
	int h; //���ۺ���
	int f; //����ʽ����
	bool operator < (const Node & u) const //��������ʽ����f�Ĵ�С��Ϊ���ȶ������������'<'
	{
		return f > u.f;
	}
}k;

inline int gujia(Node u) //���ۺ���h = ��u���յ�֮��������پ��� * 10
{
	return (abs(u.x - ex) + abs(u.y - ey)) * 10;
}

void pre()
{
    memset(vis, 0, sizeof(vis));
	k.x = bx, k.y = by; //�������(k.x, k.y)
	k.g = 0; //����ԭʼ����Ϊ0
	k.deep = 0; //������ֵ��ʼ��Ϊ0
	k.h = gujia(k); //���ۺ���
	k.f = k.g + k.h; //����ʽ����F = G + H
}

void A_Star() //A*�㷨
{
    pre();
    std::priority_queue<Node> q;
    q.push(k);
	while(!q.empty())
    {
		Node u = q.top();
		q.pop();
		vis[u.x][u.y] = 1;
		if(u.x == ex && u.y == ey)//���ʵ��յ�ʱ�����ص�ǰ��Ȳ��˳�����
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
			if(!vis[v.x][v.y]) //vδ�����ʹ�
            {
				v.g = u.g + 23; //ÿ��һ���Ļ���ԼΪ23��˵������
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
