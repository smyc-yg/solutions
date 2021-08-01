/*
���⣺һ��ȳ���ľ����������Ϻ�ÿһ��ľ���ĳ��ȶ�������50�����ȵ�λ������ԭľ������С���ܳ��ȡ�
����������Ϊ��֦���Խ϶࣬��������ȫ
��֦���ԣ�
1. ԭʼľ�����ȷ�Χ����СΪ ����֮�����С�����ȣ����Ϊ����С������֮�͡�
2. ԭʼľ������һ���� ����С������֮�� ��һ��Լ����
3. ���ȿ��ǳ��Ƚϳ���С������Ϊ��ľ���ȳ�ľ��������ƴ�ӳɹ���
4. ������ͬ��С������Ҫ�������ԡ�
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
int a[65], n, sum, num, ans;//ans��ʾ��С���ܳ��ȣ�num��ʾ��ƴ�ɵĳ���Ϊans��ľ��������sum��ʾľ�����ܳ���
bool mark[65];

bool cmp(int x, int y) {
    return x > y;
}

//cnt��ʾ��ǰ�Ѿ�ƴ�ɵ�Сľ���ĸ�����len��ʾ��ǰ����ƴ��ԭľ�����ȣ�pos��ʾҪ���Ե�Сľ�����±�
bool dfs(int cnt, int len, int pos) {
    if(cnt == num) return true; //�ɹ�ƴ��
    bool sign = (len ? false : true);
    for(int i = pos + 1; i < n;i++) {
        if(mark[i]) continue; //�ɹ��ù���Сľ������ʹ��

        //������ϸպ�ƴ�� ��Ϊans��ľ������Ҫ��ʼƴ�ӵ�(cnt+1)��ԭľ����
        if(len + a[i] == ans) {
            mark[i] = true;
            if(dfs(cnt + 1, 0, -1)) //��һ���ɹ�
                return true;
            ////ʧ���˾�Ҫ����false��������
            mark[i] = false;
            return false;
        }

        //������ϵ�ǰ����� ������ȻС��ans���ͼ���ƴ��cnt��ľ��
        else if(len + a[i] < ans) {
            mark[i] = true;
            if(dfs(cnt, len + a[i], i)) //������տ���ƴ��
                return true;
            //�������
            mark[i] = false;
            if(sign) return false;
            //������ͬ�Ĳ���Ҫ��������
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
        sort(a, a + n, cmp); //��ľ���Ӵ�С����
        //����Ŀ�ʼ����
        for(ans = a[0]; ans <= sum; ans++) {
            //ԭ���ȱ����ܹ����ܳ�������
            if(!(sum % ans)) {
                num = sum / ans; //num��ʾ������£�����ɹ��Ļ�������ƴ�ɵ�ľ����Ŀ��
                memset(mark, false, sizeof(mark));
                //�����ɹ����������Ϊ�����Ǵ���С���ܳ��ȿ�ʼö�ٵ�
                if(dfs(1, 0, -1)) {
                    printf("%d\n", ans);
                    break;
                }
            }
        }
    }
    return 0;
}
