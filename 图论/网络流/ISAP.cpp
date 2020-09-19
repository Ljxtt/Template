#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-x))
#define mem(i, a) memset(i, a, sizeof(i))
#define sqr(x) ((x) * (x))
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
typedef long long ll;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 7;
using namespace std;
struct edge {
    int v, w, nxt;
} e[maxn << 1];
int h[maxn], tot, n, m, gap[maxn], last[maxn], d[maxn], que[maxn], ql, qr;
void add(int u, int v, int w) {
    e[++tot] = (edge){v, w, h[u]};
    h[u] = tot;
    e[++tot] = (edge){u, w, h[v]};
    h[v] = tot;
}
void init(int s, int t) {
    memset(gap, 0, sizeof gap), memset(d, 0, sizeof d), ++gap[d[t] = 1];
    for (int i = 1; i <= n; ++i) last[i] = h[i];
    que[ql = qr = 1] = t;
    while (ql <= qr) {
        int x = que[ql++];
        for (int i = h[x], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
            if (!d[v]) ++gap[d[v] = d[x] + 1], que[++qr] = v;
    }
}
ll aug(int x, int s, int t, int mi) {
    if (x == t) return mi;
    ll flow = 0;
    for (int &i = last[x], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
        if (d[x] == d[v] + 1) {
            ll tmp = aug(v, s, t, min(mi, e[i].w));
            flow += tmp, mi -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!mi) return flow;
        }
    if (!(--gap[d[x]])) d[s] = n + 1;
    ++gap[++d[x]], last[x] = h[x];
    return flow;
}
int maxflow(int s, int t) {
    init(s, t);
    ll ret = aug(s, s, t, inf);
    while (d[s] <= n) ret += aug(s, s, t, inf);
    return ret;
}
typedef pair<pair<int, int>, int> pii;
pii arr[maxn];
int main(void) {
#ifdef ljxtt
    freopen("data.in", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        mem(h, 0);

        for (int i = 0; i < n; i++) {
            scanf("%d%d", &arr[i].first.first, &arr[i].first.second);
            arr[i].second = i + 1;
        }
        sort(arr, arr + n);
        tot = 1;
        for (int i = 0, x, y, c; i < m; i++) {
            scanf("%d%d%d", &x, &y, &c);
            add(x, y, c);
        }
        printf("%lld\n", maxflow(arr[0].second, arr[n - 1].second));
    }
    return 0;
}