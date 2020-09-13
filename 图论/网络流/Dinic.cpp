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