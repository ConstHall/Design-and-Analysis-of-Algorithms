#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	//���ôŵ����������������Ϊ1000
	const int N = 1000;
	//�洢��������
	int queue[N];
	//�洢��ǰλ�õ���ͷ���ľ���
	int dis[N];
	//�ŵ�������������
	int n = 0;
	//��ͷ��ʼλ��
    int start = 0;
	//��ͷ�ƶ�����
    int sum = 0;
	//����ŵ��������������ʹ�ͷ��ʼλ��
	cin >> n >> start;
	//����ŵ��������в�����ÿ���ŵ����ͷ��ʼλ�õľ���ľ���ֵ
	for(int i = 0; i <= n-1 ; i++){
		cin >> queue[i];
        dis[i] = abs(queue[i] - start);
	}
	//ѭ��n�Σ�������n�δŵ�
	cout << endl << "���ȷ���Ϊ:" << endl;
    int times = n;
    while(times--){
		//minΪ������Сֵ��ÿ�αȽϲ��ϸ���
		int min = 10000;
		//indexΪ���ͷ��������Ĵŵ����±�
        int index = 0;
		//����δ���ʹ��Ĵŵ����ҳ����뵱ǰ��ͷ������±�;�����Сֵ������
		//��ĳ�ŵ��ѷ��ʹ���Ὣ���Ӧ��dis[i]��Ϊ-1��ʾ�ѷ��ʹ�
		for(int i = 0; i <= n-1 ; i++){
			if(dis[i] < min && dis[i] != -1){
                index = i;
                min = dis[i];
            }
		}
		cout << queue[index] << " -> ";
		//���´�ͷ�ƶ�����
		sum += dis[index];//����sum
		//��ĳ�ŵ��ѷ��ʹ���Ὣ���Ӧ��dis[i]��Ϊ-1��ʾ�ѷ��ʹ�
        dis[index] = -1;
		//�Դ�ͷ��λ�ý����ƶ��������£�
		start = queue[index];
		//�����µĴ�ͷλ�ö�ʣ�µĴŵ���������ľ�������dis���и���
		for(int i = 0; i <= n-1 ; i++){
			//��Ϊ-1������ѷ��ʹ����������dis
			if(dis[i] == -1){
                continue;
            }
            dis[i] = abs(queue[i] - start);
		}
    }
	cout << "���ʽ���" << endl;
	//�����ͷ�ƶ�����
	cout << endl << "��ͷ�ƶ�����Ϊ��" << sum <<endl;
	return 0;
}

