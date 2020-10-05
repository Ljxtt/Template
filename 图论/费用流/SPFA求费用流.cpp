/*************************************************
类 Dinic 求最小费用最大流
时间复杂度：O(n m f) 
往往到不了上界，注意流量是否会爆 int.
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
ll cost = 0;
struct { int w, f; } edge[maxn];
int head[maxn], ver[maxn], nex[maxn], d[maxn], vis[maxn], tot;
void add_edge(int u, int v, int w, int f){
    ver[++tot] = v; edge[tot] = {w,  f}; nex[tot] = head[u]; head[u] = tot;
}
void add(int u, int v, int w, int f){
    add_edge(u, v, w,  f);
    add_edge(v, u, 0, -f);
}
queue<int> que;
bool spfa(int s, int t){
    while(que.size()) que.pop();
    mem(d, inf); mem(vis, 0);
    d[s] = 0; vis[s] = 1;
    que.push(s); 
    while(que.size()){
        int now = que.front(); que.pop(); vis[now] = 0;
        for(int i = head[now]; i; i = nex[i]){
            int ne = ver[i];
            if(edge[i].w && d[now] + edge[i].f < d[ne]){
                d[ne] = d[now] + edge[i].f;
                if(vis[ne]) continue;
                vis[ne] = 1;
                que.push(ne);
            }
        }
    }
    return d[t] != inf;
}
int dfs(int s, int t, int flow){
    if(s == t) return flow;
    int rest = flow, k;
    vis[s] = 1;
    for(int i = head[s]; i && rest; i = nex[i]){
        int ne = ver[i];
        if(!vis[ne] && edge[i].w && d[ne] == d[s] + edge[i].f){
            k = dfs(ne, t, min(rest, edge[i].w));
            if(!k) d[ne] = 0;
            edge[i].w -= k;
            edge[i ^ 1].w += k;
            rest -= k;
            cost += 1ll * k * edge[i].f;
        }
    }
    vis[s] = 0;
    return flow - rest;
}
ll dinic(int s, int t){
    ll flow = 0, maxflow = 0;
    while(spfa(s, t)) while(flow = dfs(s, t, inf)) maxflow += flow;
    return maxflow;
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    int n, m, s, t;
    tot = 1;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 0, u, v, w, f; i < m; i++){
        scanf("%d%d%d%d", &u, &v, &w, &f);
        add(u, v, w, f);
    }
    ll maxflow = dinic(s, t);
    printf("%lld %lld\n", maxflow, cost);
    return 0;
}