/* *************************************************
* Miller_Rabin 算法进行素数测试
* 速度快可以判断一个小于 2^63 的数是不是素数
* 成功概率极大，S 一般 8 - 10，测试 5e5 组数据无错，不能用 int128 可以换成快速乘，速度会慢很多
* 
* Pollard_Rho 算法质因数分解
* 时间复杂度为 O(n ^(1/4))。
/* **************************************************/
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
// const int maxn = e + 7;
using namespace std;

mt19937 myrand(time(0));
ll factor[1000], tol;       //记得初始化
ll qmul(__int128 a, __int128 b, ll mod) {
        return a * b % mod;
//     ll ans = 0;
//     for(a %= mod, b %= mod; b; b >>= 1){
//         if(b & 1) ans = ans + a - (ans + a > mod? mod: 0);
//         a <<= 1;
//         if(a > mod) a -= mod;
//     }
//     return ans;
}

ll qpow(ll a, ll n, ll mod){
    ll ans = 1;
    for(a %= mod; n; n >>= 1){
        if(n & 1) ans = qmul(ans, a, mod);
        a = qmul(a, a, mod);
    }
    return ans;
}

// 通过a^(n-1)=1(mod n)来判断n 是不是素数
// n - 1 = x ∗ 2t 中间使用二次判断
// 是合数返回true, 不一定是合数返回false
bool judge(ll a, ll n, ll x, ll t) {
    ll ans = qpow(a, x, n), last = ans;
    for (int i = 1; i <= t; i++) {
        ans = qmul(ans, ans, n);
        if (ans == 1 && last != 1 && last != n - 1) return true;  //合数
        last = ans;
    }
    return ans != 1;
}

bool Miller_Rabin(ll n) {
    int S = 8;          //随机算法判定次数一般 8∼10 就够了
    if (n == 2) return true;
    if (n < 2 || !(n & 1)) return false;
    ll x = n - 1, t = 0;
    while ((x & 1) == 0) {
        x >>= 1; t++;
    }

    for (int i = 0; i < S; i++) {
        ll a = myrand() % (n - 1) + 1;
        if (judge(a, n, x, t)) return false;
    }
    return true;
}

ll Pollard_Rho(ll x, ll c){
    ll k = 2, x0 = myrand() % (x - 1) + 1, y = x0;
    for(int i = 2; 1; i++){
        x0 = (qmul(x0, x0, x) + c) % x;
        ll d = __gcd(abs(y - x0), x);
        if(d != 1 && d != x) return d;
        if(y == x0) return x;
        if(i == k){y = x0; k <<= 1;}
    }
}

void findfac(ll n){
    if(n == 1) return;
    if(Miller_Rabin(n)){
        factor[tol++] = n;
        return;
    }
    ll p = n, c = 107;
    while(p >= n) p = Pollard_Rho(p, c--);
    findfac(p); findfac(n / p);
}

int main(void) {
#ifdef ljxtt
    freopen("data.in", "r", stdin);
#endif
    int n; scanf("%d", &n);
    int cnt = 0;
    for(int i = 0, t; i < n; i++){
        scanf("%d", &t);
        if(Miller_Rabin(t)) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}
