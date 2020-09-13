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
int p[maxn], tot, mu[maxn];    //p 是素数数组，tot是数组长度，mu是莫比乌斯函数数组
bool check[maxn];               //check[i] = 0 代表 i 是合数
void init(int n) {
    mem(check, 0);
    tot = 0;
    check[0] = check[1] = 0;
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!check[i]) {p[tot++] = i; mu[i] = -1;}
        for (int j = 0, u; j < tot && (u = i * p[j]) <= n; j++) {
            check[u] = 1;
            if (i % p[j] == 0){
                mu[u] = 0;
                break;
            }else{
                mu[u] = -mu[i];
            }
        }
    }
}
int fun(int x){
    int cnt = 0;
    for(int i = 1; i <= x; i++){
        if(x % i != 0) continue;
        if(i != 1 &&  (x / i) % i == 0) return 0;
        cnt++; x /= i;
    }
    return cnt % 2? 1: -1;
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    init(maxn - 1);
    for(int i = 1; i < maxn; i++){
        if(mu[i] != fun(i)){
            printf("%2d %2d %2d\n", i, mu[i], fun(i));
            break;
        }
    }
    return 0;
}