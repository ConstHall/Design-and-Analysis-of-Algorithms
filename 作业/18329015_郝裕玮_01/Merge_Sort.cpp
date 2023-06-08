#include <iostream>
using namespace std;

long long ans = 0;//����������Ϊȫ�ֱ���

void Merge(int a[], int left, int right)
{
    if (left == right) {
    	return;
	}
    int mid = (left + right) / 2;
    //left �� mid �ֱ���Ҫ�ϲ��ĵ�һ�����еĿ�ͷ�ͽ�β��mid+1 �� right �ֱ��ǵڶ������еĿ�ͷ�ͽ�β
    //i��j �ֱ��ǵ�1�͵�2�����еĵ�ǰλ�ã�k �Ǳ�ǵ�ǰҪ�ŵ��������һ��λ��
    int i = left, j = mid + 1, k = left;
    int *temp = new int[right - left + 1];
    Merge(a, left, mid);
    Merge(a, mid + 1, right);
    //����������е�����û���꣬ѭ��
    while (i <= mid && j <= right)
    {
        if (a[i] < a[j]) {
        	temp[k++] = a[i++];
		}
        //�������������(a[i]>a[j])����� i �� mid �� mid-i+1 ���������a[j]�󣬾�Ϊ������������ans
        else {
            temp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    //����󣬽�ʣ��û�в���Ƚϵ���ֱ�ӷŽ�a����
    while (i <= mid) {
    	temp[k++] = a[i++];
	}
    while (j <= right) {
    	temp[k++] = a[j++];
	}
    for (int i = left; i <= right; ++i) {
    	a[i] = temp[i];
	}
}

int main()
{
    int n;//������������ָ��� 
	cin >> n;
    int *a = new int[n + 1];//Ϊ������������n+1���ռ䣬���1-n������0�±���һ���ռ䣩
    //������������
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
	}
    //�鲢����
    Merge(a, 1, n);
    //���������
    cout << ans << endl;
}
