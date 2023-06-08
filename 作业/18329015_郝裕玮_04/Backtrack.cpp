#include <iostream>
#include <string>
using namespace std;

//����������
int m,n;
//λ�����飨����+�������ң�
int f[5][2] = { {0,0} , {0,1} , {0,-1} , {1,0} , {-1,0} }; 
//������飨�ڱ�λ�ã�
int res[30][30];
//�ڱ�����
int ans;
//��ʱ�洢�ڱ�λ�� 
int sentinel[30][30];
//��ʱ�洢�ڱ�����
int p; 
//�ڱ��ܿ�����λ��
int vision[30][30];
//�����ӵĳ����Ҹ��� 
int visions;
//��������
void Sentinel(int x,int y,int c,int d);
void search(int i,int j);
 
//������
int main()
{
	//��ȡinput.txt
    FILE* file1 = fopen ( "C:\\Users\\93508\\Desktop\\input.txt" , "r" );
	if (file1 == NULL){
        cout << "�ļ���ȡʧ�ܣ�" << endl;
		return 0;
	}
	fscanf ( file1 , "%d%d" , &m , &n );
	fclose ( file1 );

    //��֦���ڱ��������ᳬ��(n*m/3+1)��
	ans = n*m/3 + 2;
	p = 0;
	//���ñ߽� 
	for(int i = 0 ; i <= m + 1 ; i++){
		vision[i][0] = vision[i][n+1] = 1;
	}
	
	for(int i = 0 ; i <= n + 1 ; i++){
		vision[0][i] = vision[m+1][i] = 1;
	}
	//��ʼ����
	search(1,1);
    //��������д��output.txt
 	cout << ans << endl;	
	FILE* file2 = fopen ( "C:\\Users\\93508\\Desktop\\output.txt" , "w" );
	for(int i = 1; i <= m ; i++){
		for(int j = 1 ; j <= n ; j++){
			cout << res[i][j] << ' ';
            fprintf ( file2,"%2d" , res[i][j] );
		}
		cout << endl;
        fprintf (file2, "\n" );
	}	
	fclose ( file2 );
}

//����λ��
void search(int i,int j)
{
	if(p >= ans){
        return;
    }
    //��λ�����ѱ�ĳ���ڱ��۲쵽������
	while(i <= m && vision[i][j]!=0 ) {
		j++;
        //����
		if(j > n){
            i++;
            j = 1; 
        }
	}
    //���´�
	if(i>m) {
		ans = p;
        //���º�Ĵ𰸸��Ƶ����ս������res��
		memcpy(res, sentinel, sizeof(sentinel));
		return;
	}
 
	if(i < m){
        Sentinel(i+1,j,i,j);
    }
	if(vision[i][j+1] == 0){
        Sentinel(i,j,i,j);
    }
	if(j < n && (vision[i][j+1] == 0 || vision[i][j+2] == 0)){
        Sentinel(i,j+1,i,j);
    }
}
 
void Sentinel(int x,int y,int c,int d)
{
	sentinel[x][y] = 1;
	p++;
	for(int i=0 ; i<=4; i++){
        int xx = x + f[i][0];
        int yy = y + f[i][1];
        vision[xx][yy]++;
        if(vision[xx][yy] == 1){
            visions++;
        }
    }
 
	search(c,d+1);
 
	sentinel[x][y] = 0;
	p--;
	for(int i=0 ; i<=4 ; i++){
        int xx = x + f[i][0];
        int yy = y + f[i][1];
        vision[xx][yy]--;
        if(vision[xx][yy]==0){
            visions--;
        }
    }
}
