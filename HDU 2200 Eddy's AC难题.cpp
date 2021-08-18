/*
HDU 2200 Eddy's AC����
���⣺��n��������ͬ����������m����������m�����ֳ����飬��һ���������ȵڶ������С��ҪС��
      ���ж�����ȡ����
��Ŀ���ͣ�DP/�������
�Ѷȣ�1��
����˼·��
1. DP
  ��֪dp[n - 1]��dp[n]�����Է�Ϊ���������
  1���������Ԫ�أ���(n - 1)��ȫ��ͬ����dp[n - 1]�֣�
  2��һ��Ϊ(n - 1)�ķǿ��Ӽ�����һ��ΪԪ��n����2 ^ (n - 1) - 1�֣�
  3����(n - 1)�Ļ����ϼ���Ԫ��n����dp[n - 1]�֡�
  ���ϣ�״̬ת�Ʒ���Ϊ dp[n] = dp[n - 1] * 2 + 2 ^ (n - 1) - 1��
2. �������
  m��ȡֵ��ΧΪ[2, n]������ѡ����m�����������������ٲ����(m - 1)��
  ���Դ�ΪC(n, i) * (i - 1)������2 <= i <= n��
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
