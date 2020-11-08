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

typedef double db;
struct node{db x, y;};
typedef node point, vec;

db operator ^ (const node &a, const node &b){
    return a.x * b.y - a.y * b.x;
}
node operator - (const node &a, const node &b){
    return node{a.x - b.x, a.y - b.y};
}
bool operator < (const node &a, const node &b){
    return a.x == b.x ? a.y < b.y: a.x < b.x;
}
vec makevec(const point &a, const point &b){
    return b - a;
}

db dis(const node &a, const node &b, bool op = 0){
    db ans = sqr(a.x - b.x) + sqr(a.y - b.y);
    return op? ans: sqrt(ans);
}

int Andrew(point arr[], int n, point res[]) {
    sort(arr, arr + n);
    int top = 0;
    // 求下凸包
    for (int i = 0; i < n; i++) {
        while (top > 1 && (makevec(res[top - 1], res[top]) ^ makevec(res[top], arr[i])) <= 0) 
            top--;
        res[++top] = arr[i];
    }
    // 求上凸包
    int cnt = top;
    for (int i = n - 2; i >= 0; i--) {
        while (top > cnt && (makevec(res[top - 1], res[top]) ^ makevec(res[top], arr[i])) <= 0)
            top--;
        res[++top] = arr[i];
    }
    return top;
}
point arr[maxn], res[maxn];
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lf%lf", &arr[i].x, &arr[i].y);
    int top = Andrew(arr, n, res);
    db ans = 0;
    for(int i = 1; i < top; i++) ans += dis(res[i], res[i + 1]);
    printf("%.2f\n", ans);
    return 0;
}