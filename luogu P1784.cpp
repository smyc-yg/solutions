/*
�ص���������ת�����֣�������еĶ��壬������Ǵ� Dancing Links X
*/
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN = 3010; //���ڵ���
int a[10][10];

struct DLX {
    int n, m, s; //n��m�У�s��ʾ�ڵ���
    //Left[]ָ����ߵ�Ԫ�ء�Right[]ָ���ұߵ�Ԫ�ء�Up[]ָ���ϱߵ�Ԫ�ء�Down[]ָ���±ߵ�Ԫ��
    //Col[]ָ���б�Ԫ�ء�Row[]��ʾ��ǰԪ�����ڵ���
    int Up[MAXN], Down[MAXN], Left[MAXN], Right[MAXN], Col[MAXN], Row[MAXN];
    int Head[MAXN]; //Head[]��ʾ����ָ�룬��Head[0] = 0ʱ������Ϊ��
    int S[MAXN]; //S[i]��ʾ��i���еĽڵ���
    int ansR, ans[MAXN];//ansR��ʾ����������������ans[]��¼��

    //��ʼ��,�����յ�ʮ������
    void pre(int _n, int _m) {
        n = _n, m = _m;
        for(int i = 0; i <= m; i++) {
            //��ʵ��������Ԫ�ض��ԣ�������ҪUp��Downָ������Ϊ�˷����һ��д��
            Up[i] = i;
            Down[i] = i;
            Left[i] = i - 1;
            Right[i] = i + 1;
            Col[i] = i;
            Row[i] = 0; //����Ԫ��ͳһ���ڵ�0��
            S[i] = 0; //��ʼʱÿ�нڵ�������
        }
        Left[0] = m;
        Right[m] = 0;
        s = m; //��m��Ԫ�غ�ͱ�ʾ��ͨԪ��
        for(int i = 0; i <= n; i++) {
            Head[i] = -1;
            ans[i] = 0;
        }
        //memset(Head, -1, sizeof(Head));
        //memset(ans, 0, sizeof(ans));
        ansR = 0;
    }

    //�ڵ�r�У���c�е�λ������µĽڵ�(ע�����������²��롢����ǰ�巨)
    void Insert(int r, int c) {
        s++; //�ڵ���+1
        Down[s] = Down[c]; //�½ڵ���²�ָ��ָ���б�Ԫ���±ߵĽڵ�
        Up[s] = c; //�½ڵ���ϲ�ָ��ָ���б�Ԫ��
        Up[Down[c]] = s; //ԭ�����б�Ԫ���±ߵĽڵ���ϲ�ָ��ָ���½ڵ�
        Down[c] = s; //�б�Ԫ�ص��²�ָ��ָ���½ڵ�
        //�½ڵ�λ�ڵ�r�У���c��
        Row[s] = r;
        Col[s] = c;
        S[c]++; //��c�еĽڵ���+1
        //�������ɸ��е�һ��Ԫ��
        if(Head[r] < 0) {
            Head[r] = s; //���е�һ��Ԫ��Ϊ�½ڵ�
            //����Right��Left��û�нڵ�
            Right[s] = s;
            Left[s] = s;
        }
        else {
            Left[s] = Head[r]; //�½ڵ�����ָ��ָ����һ�еĵ�һ���ڵ�
            Right[s] = Right[Head[r]]; //�½ڵ���Ҳ�ָ��ָ����һ�е�һ���ڵ��ұߵĽڵ�
            Left[Right[Head[r]]] = s; //��һ�е�һ���ڵ��ұߵĽڵ�����ָ��ָ���½ڵ�
            Right[Head[r]] = s; //��һ�еĵ�һ���ڵ���Ҳ�ָ��ָ���½ڵ�
        }
    }

    //��ĳһ�м������Ͻڵ����ڵ��д���������ʱɾ��
    void Remove(int c) {
        Left[Right[c]] = Left[c]; //��c���ұ�һ�е����ָ��ָ���c�е����һ��
        Right[Left[c]] = Right[c]; //��c�����һ�е��Ҳ�ָ��ָ���c�е��ұ�һ��
        //������һ�е�ÿ���ڵ�
        for(int i = Down[c]; i != c; i = Down[i]) {
            //�����ýڵ��������ϵ����нڵ�
            for(int j = Right[i]; j != i; j = Right[j]) {
                //��һɾ���ڵ�j
                Up[Down[j]] = Up[j]; //�ڽڵ�j�±ߵ��Ǹ��ڵ���ϲ�ָ��ָ��ڵ�j�ϱߵĽڵ�
                Down[Up[j]] = Down[j]; //�ڽڵ�j�ϱߵ��Ǹ��ڵ���²�ָ��ָ��ڵ�j�±ߵĽڵ�
                --S[Col[j]]; //�ڵ�j���ڵ���һ�еĽڵ���-1
            }
        }
    }

    //�� ��c�м������Ͻڵ����ڵ��� ���¼�������
    void Resume(int c) {
        //���ڵ�c���ϵ�ÿ���ڵ�i
        for(int i = Up[c]; i != c; i = Up[i]) {
            //�����ڵ�i�����е�ÿ���ڵ�j
            for(int j = Left[i]; j != i; j = Left[j]) {
                Down[Up[j]] = j; //�ڵ�j�ϱ߽ڵ���²�ָ�� ָ��ڵ�j
                Up[Down[j]] = j; //�ڵ�j�±߽ڵ���ϲ�ָ�� Ҳָ��ڵ�j
                ++S[Col[j]];
            }
        }
        Right[Left[c]] = c; //��c�����һ�е��б�Ԫ�� ���Ҳ�ָ�� ָ���c��
        Left[Right[c]] = c; //��c���ұ�һ�е��б�Ԫ�� �����ָ�� ָ���c��
    }

    //���Ĵ��룬������dfs��Deep��ʾ�������
    bool Dance(int Deep) {
        //��Head.Right == Head����ʱ ����
        if(Right[0] == 0) {
            int x, y, v; //(x, y)��ֵΪv
			for(int i = 0; i < Deep; i++) {
                //������Ϣת���ɶ�Ӧ�ĵ����Ϣ
                x = (ans[i] - 1) / 9 / 9;
                y = (ans[i] - 1) / 9 % 9;
                v = ans[i] % 9;
                if(v == 0) v = 9; //��ֹ9�ı���%9==0
                    a[x][y] = v;
			}
            return true;
        }
        int c = Right[0]; //��ȡHead.Rightָ����б�Ԫ�أ���Ϊ�������
        //�������forѭ���������ҵ���ǰ״̬�нڵ������ٵ���һ��
        for(int i = Right[0]; i != 0; i = Right[i]) //��������������϶�ȡ��ǰԪ�ص��Ҳ�ָ��
            if(S[i] < S[c]) c = i;
        Remove(c); //��ѡ������һ�д�ʮ��˫��������ɾ��
        //������һ�е�ÿ���ڵ�
        for(int i = Down[c]; i != c; i = Down[i]) {
            ans[Deep] = Row[i]; //���ڵ�i���ڵ��м�¼����
            //�Ƴ����� ��ڵ�i��ͬһ�еĽڵ�j�� ���ڵ���һ��
            for(int j = Right[i]; j != i; j = Right[j])
                Remove(Col[j]);
            //�ҵ��𰸣��˳�
            if(Dance(Deep + 1)) return true;
            //���򣬻���
            for(int j = Left[i]; j != i; j = Left[j])
                Resume(Col[j]);
        }
        Resume(c); //�˳�����ǰ�����˻���c��״̬
        return false;
    }
}dlx;

int main() {
    int n = 729, m = 324;
    dlx.pre(n, m); //��ʼ��
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            scanf("%d", &a[i][j]);
            for(int k = 1; k <= 9; k++) {
                if(a[i][j] != k && a[i][j]) continue; //�Ѿ���õ���ֱ������
                int id = i * 9 * 9 + j * 9 + k;
                int c1, c2, c3, c4;
                c1 = i * 9 + j + 1;
                c2 = i * 9 + 81 + k;
                c3 = j * 9 + 81 * 2 + k;
                c4 = 81 * 3 + (i / 3 * 3 + j / 3) * 9 + k;
                dlx.Insert(id, c1);
                dlx.Insert(id, c2);
                dlx.Insert(id, c3);
                dlx.Insert(id, c4); //��������
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
