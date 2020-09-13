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
int n, m, s, t, tot;
int head[maxn], nex[maxn], edge[maxn], ver[maxn], d[maxn];
void add(int x, int y, int z){
    ver[++tot] = y; edge[tot] = z; nex[tot] = head[x]; head[x] = tot;
    ver[++tot] = x; edge[tot] = 0; nex[tot] = head[y]; head[y] = tot;
}
queue<int> que;
bool bfs(void){
    while(que.size()) que.pop();
    mem(d, 0);
    d[s] = 1;
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
int dinic(int s, int flow){
    if(s == t) return flow;
    int rest = flow, k;
    for(int i = head[s]; i && rest; i = nex[i]){
        int ne = ver[i];
        if(edge[i] && d[ne] == d[s] + 1){
            k = dinic(ne, min(rest, edge[i]));
            if(!k) d[ne] = 0;
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    scanf("%d%d%d%d", &n, &m, &s, &t);
    tot = 1;
    for(int i = 0, x, y, z; i < m; i++){
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    ll maxflow = 0;
    while(bfs()){
        maxflow += dinic(s, inf);
    }
    printf("%lld\n", maxflow);   
    return 0;
}