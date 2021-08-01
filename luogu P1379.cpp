/*
A*�㷨�����ķ������£�
��ǰ���ϸ��λ���� + ������� > ����������k
*/
#include<algorithm>
#include<cstring>
#include<cstdio>

using namespace std;

int ans[4][4] = { {0,0,0,0}, {0,1,2,3}, {0,8,0,4}, {0,7,6,5} }; //Ŀ��״̬
int a[5][5], k, judge;
int tx[] = {0, 1, -1, 0};
int ty[] = {1, 0, 0, -1};

//�ж��Ƿ񵽴�Ŀ��״̬
int check() {
    for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
            if(ans[i][j] != a[i][j]) return 0;
    return 1;
}

//����
int test(int step) {
    int cnt = 0;
    for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
            if(ans[i][j] != a[i][j]) { //��δ��Ŀ��״̬
                if(++cnt + step > k) return 0; //��ǰ���ϸ��λ���� + ������� > ����������k
            }
    return 1;
}

//����
void A_star(int step, int x, int y, int pre) {
    //��������һ���ﵽ��ǰ���Ƶ�������
    if(step == k) {
        if(check()) judge = 1;
        return;
    }
    ////���������������ҵ���
    if(judge) return;
    for(int i = 0; i < 4; ++i) {
        int nx = x + tx[i], ny = y + ty[i];
        if(nx < 1 || nx > 3 || ny < 1 || ny > 3 || pre + i == 3) continue; //Խ�� �� �����������Լ�֦
        swap(a[x][y], a[nx][ny]);
        if(test(step) && !judge) A_star(step + 1, nx, ny, i); //A*���ۺϷ� �� δ�ҵ��� ����������
        swap(a[x][y], a[nx][ny]);
    }
}

int main() {
    int x, y;
    char s[15];
    scanf("%s", s);
    for(int i = 0; i < 9; ++i) {
        a[i / 3 + 1][i % 3 + 1] = s[i] - '0'; //����洢һ��״̬
        if(!(s[i] - '0')) x = i / 3 + 1, y = i % 3 + 1; //ȷ��0�ĳ�ʼλ��
    }
    //���в����ƶ�,ֱ�ӵô�
    if(check()) {
        printf("0\n");
        return 0;
    }
    //ö�������ȣ���ν��������
    while(++k) {
        A_star(0, x, y, -1);
        if(judge) {
            printf("%d\n", k);
            break;
        }
    }
    return 0;
}
