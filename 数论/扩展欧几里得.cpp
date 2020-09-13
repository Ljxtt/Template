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
using namespace std;
void exgcd(ll a, ll b, ll &x, ll &y){
    if(!b)
        x = 1, y = 0;
    else{
        exgcd(b, a % b, y, x);
        y -= x * (a / b);
    }
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    int a = 8, b = 7, x, y;
    exgcd(-a, b, x, y);
    cout << x << " " << y << endl;
    return 0;
}