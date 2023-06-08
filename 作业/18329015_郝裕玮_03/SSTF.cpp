#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	//设置磁道访问请求数量最多为1000
	const int N = 1000;
	//存储访问序列
	int queue[N];
	//存储当前位置到磁头处的距离
	int dis[N];
	//磁道访问请求数量
	int n = 0;
	//磁头起始位置
    int start = 0;
	//磁头移动总数
    int sum = 0;
	//输入磁道访问请求数量和磁头起始位置
	cin >> n >> start;
	//输入磁道访问序列并计算每个磁道与磁头初始位置的距离的绝对值
	for(int i = 0; i <= n-1 ; i++){
		cin >> queue[i];
        dis[i] = abs(queue[i] - start);
	}
	//循环n次，即访问n次磁道
	cout << endl << "调度方案为:" << endl;
    int times = n;
    while(times--){
		//min为距离最小值，每次比较不断更新
		int min = 10000;
		//index为离磁头距离最近的磁道的下标
        int index = 0;
		//从尚未访问过的磁道中找出距离当前磁头最近的下标和距离最小值并更新
		//若某磁道已访问过则会将其对应的dis[i]置为-1表示已访问过
		for(int i = 0; i <= n-1 ; i++){
			if(dis[i] < min && dis[i] != -1){
                index = i;
                min = dis[i];
            }
		}
		cout << queue[index] << " -> ";
		//更新磁头移动总数
		sum += dis[index];//更新sum
		//若某磁道已访问过则会将其对应的dis[i]置为-1表示已访问过
        dis[index] = -1;
		//对磁头的位置进行移动（即更新）
		start = queue[index];
		//根据新的磁头位置对剩下的磁道访问请求的距离数组dis进行更新
		for(int i = 0; i <= n-1 ; i++){
			//若为-1则代表已访问过，无需计算dis
			if(dis[i] == -1){
                continue;
            }
            dis[i] = abs(queue[i] - start);
		}
    }
	cout << "访问结束" << endl;
	//输出磁头移动总数
	cout << endl << "磁头移动总数为：" << sum <<endl;
	return 0;
}

