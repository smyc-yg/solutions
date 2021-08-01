/*
���⣺����һ��M*N��01�����ܷ��ҵ�һ���еļ��ϣ�ʹ�ü�����ÿһ�ж�ǡ�ð���һ��1��
ģ���⣬ֱ���ϴ���
*/
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXN = 505;
const int M = MAXN * MAXN; //���ڵ���

struct DLX {
    int n, m, s; //n��m�У�s��ʾ�ڵ���
    //Left[]ָ����ߵ�Ԫ�ء�Right[]ָ���ұߵ�Ԫ�ء�Up[]ָ���ϱߵ�Ԫ�ء�Down[]ָ���±ߵ�Ԫ��
    //Col[]ָ���б�Ԫ�ء�Row[]��ʾ��ǰԪ�����ڵ���
    int Up[M], Down[M], Left[M], Right[M], Col[M], Row[M];
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
            }
        }
        Right[Left[c]] = c; //��c�����һ�е��б�Ԫ�� ���Ҳ�ָ�� ָ���c��
        Left[Right[c]] = c; //��c���ұ�һ�е��б�Ԫ�� �����ָ�� ָ���c��
    }

    //���Ĵ��룬������dfs��Deep��ʾ�������
    bool Dance(int Deep) {
        //��Head.Right == Headʱ����
        if(Right[0] == 0) {
            ansR = Deep;
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

void deal(int n, int m) {
    dlx.pre(n, m); //��ʼ��
    //����ԭ����ֻ�洢1����Ϣ
    for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
            int x;
			scanf("%d", &x);
			if(x) dlx.Insert(i, j);	//��ÿ��λ��(i, j)��1 �ӵ�����������
		}
	}
	if(!dlx.Dance(0)) printf("It is impossible\n");
	else printf("Yes, I found it\n");
}

int main() {
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
        deal(n, m);
    return 0;
}
