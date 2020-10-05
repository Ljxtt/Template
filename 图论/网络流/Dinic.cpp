/*************************************************
Dinic 算法
时间复杂度：O(m sqrt(n)) 
往往到不了上界， 一般能用于 10^4 - 10^5 的图，注意流量是否会爆 int
*************************************************/
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
#define mem(i, a) memset(i, a, sizeof(i))
#define sqr(x) ((x)*(x))
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
typedef long long ll;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 7;
using namespace std;
int head[maxn], nex[maxn], edge[maxn], ver[maxn], d[maxn], tot = 0;
void add_edge(int x, int y, int z){
    ver[++tot] = y; edge[tot] = z; nex[tot] = head[x]; head[x] = tot;
}
void add(int x, int y, int z){
    add_edge(x, y, z);
    add_edge(y, x, 0);
}
queue<int> que;
bool bfs(int s, int t){
    while(que.size()) que.pop();
    mem(d, 0); d[s] = 1;
    que.push(s); 
    while(que.size()){
        int now = que.front(); que.pop();
        for(int i = head[now]; i; i = nex[i]){
            int ne = ver[i];
            if(edge[i] && !d[ne]){
                d[ne] = d[now] + 1;
                que.push(ne);
                if(ne == t) return 1;
            }
        }
    }
    return 0;
}
int dfs(int s, int t, int flow){
    if(s == t) return flow;
    int rest = flow, k;
    for(int i = head[s]; i && rest; i = nex[i]){
        int ne = ver[i];
        if(edge[i] && d[ne] == d[s] + 1){
            k = dfs(ne, t, min(rest, edge[i]));
            if(!k) d[ne] = 0;
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}
ll dinic(int s, int t){
    ll maxflow = 0, flow = 0;
    while(bfs(s, t)) while(flow = dfs(s, t, inf)) maxflow += flow;
    return maxflow;
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    tot = 1;
    for(int i = 0, x, y, z; i < m; i++){
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    printf("%lld\n", dinic(s, t));   
    return 0;
}