/*
题意：一组等长的木棒被随机砍断后，每一节木棍的长度都不超过50个长度单位，计算原木棒的最小可能长度。
打三星是因为剪枝策略较多，不容易想全
剪枝策略：
1. 原始木棒长度范围：最小为 砍断之后最长的小棒长度；最大为所有小棒长度之和。
2. 原始木棒长度一定是 所有小棒长度之和 的一个约数。
3. 优先考虑长度较长的小棒，因为短木棒比长木棒更容易拼接成功。
4. 长度相同的小棒不需要反复尝试。
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
int a[65], n, sum, num, ans;//ans表示最小可能长度，num表示能拼成的长度为ans的木棒个数，sum表示木棒的总长度
bool mark[65];

bool cmp(int x, int y) {
    return x > y;
}

//cnt表示当前已经拼成的小木棒的个数，len表示当前正在拼的原木棒进度，pos表示要尝试的小木条的下标
bool dfs(int cnt, int len, int pos) {
    if(cnt == num) return true; //成功拼接
    bool sign = (len ? false : true);
    for(int i = pos + 1; i < n;i++) {
        if(mark[i]) continue; //成功用过的小木棒不再使用

        //如果加上刚好拼成 长为ans的木棒，就要开始拼接第(cnt+1)根原木棒啦
        if(len + a[i] == ans) {
            mark[i] = true;
            if(dfs(cnt + 1, 0, -1)) //下一根成功
                return true;
            ////失败了就要返回false，并回溯
            mark[i] = false;
            return false;
        }

        //如果加上当前这根后 长度仍然小于ans，就继续拼第cnt根木棒
        else if(len + a[i] < ans) {
            mark[i] = true;
            if(dfs(cnt, len + a[i], i)) //如果最终可以拼成
                return true;
            //否则回溯
            mark[i] = false;
            if(sign) return false;
            //长度相同的不需要反复尝试
            while(a[i] == a[i + 1]) i++;
        }
    }
    return false;
}

int main() {
    while(scanf("%d", &n) != EOF,n) {
        if(!n) break;
        sum = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        sort(a, a + n, cmp); //将木棒从大到小排序
        //从最长的开始搜索
        for(ans = a[0]; ans <= sum; ans++) {
            //原长度必须能够被总长度整除
            if(!(sum % ans)) {
                num = sum / ans; //num表示该情况下，如果成功的话，可以拼成的木棒数目。
                memset(mark, false, sizeof(mark));
                //搜索成功即输出，因为我们是从最小可能长度开始枚举的
                if(dfs(1, 0, -1)) {
                    printf("%d\n", ans);
                    break;
                }
            }
        }
    }
    return 0;
}
