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
int inv[maxn], mod = 1e9 + 7;
void init(int n){
    inv[1] = 1;
    for(int i = 2; i <= n; i++){
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    }
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    init(maxn - 1);
    for(int i = 1; i < maxn - 1; i++){
        printf("%lld\n", 1ll * inv[i] * i % mod);
    }
    return 0;
}