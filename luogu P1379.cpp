/*
A*算法，核心方程如下：
当前不合格的位置数 + 搜索深度 > 最大限制深度k
*/
#include<algorithm>
#include<cstring>
#include<cstdio>

using namespace std;

int ans[4][4] = { {0,0,0,0}, {0,1,2,3}, {0,8,0,4}, {0,7,6,5} }; //目标状态
int a[5][5], k, judge;
int tx[] = {0, 1, -1, 0};
int ty[] = {1, 0, 0, -1};

//判断是否到达目标状态
int check() {
    for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
            if(ans[i][j] != a[i][j]) return 0;
    return 1;
}

//估价
int test(int step) {
    int cnt = 0;
    for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
            if(ans[i][j] != a[i][j]) { //若未达目标状态
                if(++cnt + step > k) return 0; //当前不合格的位置数 + 搜索深度 > 最大限制深度k
            }
    return 1;
}

//深搜
void A_star(int step, int x, int y, int pre) {
    //结束条件一：达到当前限制的最大深度
    if(step == k) {
        if(check()) judge = 1;
        return;
    }
    ////结束条件二：已找到答案
    if(judge) return;
    for(int i = 0; i < 4; ++i) {
        int nx = x + tx[i], ny = y + ty[i];
        if(nx < 1 || nx > 3 || ny < 1 || ny > 3 || pre + i == 3) continue; //越界 或 上述的最优性剪枝
        swap(a[x][y], a[nx][ny]);
        if(test(step) && !judge) A_star(step + 1, nx, ny, i); //A*估价合法 且 未找到答案 才向下搜索
        swap(a[x][y], a[nx][ny]);
    }
}

int main() {
    int x, y;
    char s[15];
    scanf("%s", s);
    for(int i = 0; i < 9; ++i) {
        a[i / 3 + 1][i % 3 + 1] = s[i] - '0'; //巧妙存储一下状态
        if(!(s[i] - '0')) x = i / 3 + 1, y = i % 3 + 1; //确定0的初始位置
    }
    //特判不用移动,直接得答案
    if(check()) {
        printf("0\n");
        return 0;
    }
    //枚举最大深度，所谓迭代加深
    while(++k) {
        A_star(0, x, y, -1);
        if(judge) {
            printf("%d\n", k);
            break;
        }
    }
    return 0;
}
