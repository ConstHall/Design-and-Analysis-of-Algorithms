#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 0x3f3f3f3f;//无穷大

//链式前向星，用于存储图结构信息
//关键字inline：内联函数，同宏函数一样将在被调用处进行代码展开，省去了参数压栈、栈帧开辟与回收，结果返回等，从而提高程序运行速度
struct graph{
    //head：第一个以i为起点的边的位置，同时head初始化为-1
    //next：与第i条边同一个起点的下一条边
    //to：第i条边的终点
    //wei：容量
    //cost：流量
    int head[maxn],next[maxn],to[maxn],wei[maxn],cost[maxn],cnt;
    inline graph():cnt(1){}
    inline void add(int u,int v,int w,int c){
        next[++cnt] = head[u];
        to[cnt] = v;
        wei[cnt] = w;
        head[u] = cnt;
        cost[cnt] = c;
    }
}gr;

//存放货物和仓库的坐标
struct node{
    int x,y;
    inline node(){}
    inline node(int x,int y):x(x),y(y){}
};

int n,m;//地图的行数和列数
node a[maxn],b[maxn];//a代表仓库，b代表货物
int a_len,b_len,s,t;//仓库数量，货物数量，费用流起点，费用流终点

//计算两点间麦哈顿距离
inline int getdis(const node& p,const node& q){
    return abs(p.x-q.x)+abs(p.y-q.y);
}

int dis[maxn],pre[maxn][2];//dis[i]表示当前从起点走到点i的最少费用,pre[i][0]表示最短路中的节点i的前驱节点，pre[i][1]则表示节点i的前驱边
bool inq[maxn];//inq[i]表示点i是否在队列中

//使用SPFA求最短路径
inline bool spfa(){
    queue<int> que;
    for(int i = 1;i <= t;i++){
        dis[i] = inf;//首先设置起点到所有点的距离为无穷大
    }

    que.push(s);//放入起点
    inq[s] = true;//起点在队列中
    dis[s] = 0;//起点到起点的距离为0

    //SPFA算法求最短路
    while(!que.empty()){
        int u = que.front();
        que.pop();
        inq[u] = false;
        for(int i = gr.head[u];i;i = gr.next[i]){
            int v = gr.to[i],w = gr.wei[i],c = gr.cost[i];
            if(w == 0){
                continue;//如果边的容量不为0
            }
            if(dis[v] > dis[u] + c){//松弛操作，更新两点间最短距离
                dis[v] = dis[u] + c;
                pre[v][0] = u;//设置前驱点
                pre[v][1] = i;//设置前驱边
                if(!inq[v]){//如果没在队列中，就将v点加入队列
                    inq[v] = true;
                    que.push(v);
                }
            }
        }
    }
    return dis[t] != inf;//判断起点到终点是否还有流量
}

//求解最小费用最大流
inline int solve(){
    int ans = 0;
    while(spfa()){
        ans += dis[t];
        int u = t;//从终点往前走
        while(pre[u][0]){
            gr.wei[pre[u][1]]--;//正向边的容量-1
            gr.wei[pre[u][1]^1]++;//反向边的容量+1
            u = pre[u][0];
        }
    }
    return ans;
}

//主函数
int main(){
    //输入需要求解的地图
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            char v;
            cin >> v;
            if(v == 'W'){
                a[++a_len] = node(i,j);//仓库
            }else if(v == 'G'){
                b[++b_len] = node(i,j);//货物
            }
        }
    }

    //货物向仓库连边
    for(int i = 1;i <= b_len;i++){
        int u = i;
        for(int j = 1;j <= a_len;j++){
            int v = b_len+j;
            int d = getdis(b[i],a[j]);
            gr.add(u,v,1,d);
            gr.add(v,u,0,-d);
        }
    }
    s = a_len + b_len + 1;
    t = s + 1;

    //起点向货物连边
    for(int i = 1;i <= b_len;i++){
        int u = i;
        gr.add(s,u,1,0);
        gr.add(u,s,0,0);
    }
    
    //仓库向终点连边
    for(int i = 1;i <= a_len;i++){
        int v = b_len + i;
        gr.add(v,t,1,0);
        gr.add(t,v,0,0);
    }

    //输出答案
    cout << solve() << endl;
    return 0;
}