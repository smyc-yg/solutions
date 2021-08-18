/*
HDU 2200 Eddy's AC难题
题意：从n个互不相同的数里挑出m个数，将这m个数分成两组，第一组的最大数比第二组的最小数要小，
      求有多少种取法。
题目类型：DP/排列组合
难度：1星
解题思路：
1. DP
  已知dp[n - 1]求dp[n]，可以分为三种情况：
  1）不添加新元素，与(n - 1)完全相同，共dp[n - 1]种；
  2）一组为(n - 1)的非空子集，另一组为元素n，共2 ^ (n - 1) - 1种；
  3）在(n - 1)的基础上加入元素n，共dp[n - 1]种。
  综上，状态转移方程为 dp[n] = dp[n - 1] * 2 + 2 ^ (n - 1) - 1。
2. 排列组合
  m的取值范围为[2, n]，对于选出的m个数，可以先排序再插隔板(m - 1)，
  所以答案为C(n, i) * (i - 1)，其中2 <= i <= n。
*/

/*
#include <cstdio>
#include <cmath>

using namespace std;

long long dp[105];

int main() {
	dp[0] = dp[1] = 0;
	dp[2] = 1;
	for(int i = 3; i <= 60; i++)
	  dp[i] = dp[i - 1] * 2 + pow(2, i - 1) - 1;
	int n;
	while(scanf("%d", &n) != EOF)
		printf("%lld\n", dp[n]);
	return 0;
}
*/

#include <cstdio>
#include <cmath>
#define ll long long

using namespace std;

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
        if(n < 2) {
            printf("0\n");
            continue;
        }
        ll ans = 0;
        for(int i = 2; i <= n; i++) {
            ll tmp = 1ll;
            for(int j = 1; j <= i; j++) {
                tmp = tmp * (n - j + 1) / j;
            }
            ans += tmp * (i - 1);
        }
		printf("%lld\n", ans);
	}
	return 0;
}
