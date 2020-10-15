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
typedef vector<double> poly;
poly operator * (const poly &a, const poly &b){
    poly ans; ans.resize(a.size() + b.size() - 1);
    for(auto &it: ans) it = 0; 
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            ans[i + j] += a[i] * b[j];
        }
    }
    return ans;
}
poly operator + (const poly &a, const poly &b){
    poly ans; ans.resize(max(a.size(), b.size()));
    for(auto &it: ans) it = 0; 
    for(int i = 0; i < a.size(); i++) ans[i] += a[i];
    for(int i = 0; i < b.size(); i++) ans[i] += b[i];
    return ans;
}
poly operator / (const poly &a, double t){
    poly ans = a;
    for(auto &it: ans) it /= t;
    return ans;
}
poly operator * (const poly &a, double t){
    poly ans = a;
    for(auto &it: ans) it *= t;
    return ans;
}
void print(poly ans){
    for(auto it: ans) printf("%f ", it);
    puts("");
}
poly lip(const poly &px, const poly &py, int l, int r){
    poly ans;
    for(int i = l; i <= r; i++){
        poly up; up.push_back(1);
        double down = 1;
        for(int j = l; j <= r; j++){
            if(i == j) continue;
            double tmp[] = {-px[j], 1};
            up = up * poly(tmp, tmp + 2);
            down *= px[i] - px[j];
        }
        up = up * py[i]; up = up / down;
        ans = ans + up;
    }
    return ans;
}
double fun(const poly &arr, double x){
    double ans = 0;
    for(int i = arr.size(); i >= 0; i--){
        ans = ans * x + arr[i];
    }
    return ans;
}
int main(void){
#ifdef ljxtt
freopen("data.in", "r", stdin);
#endif
    double tmp[] = {1,9, 41, 109, 205, 325, 473, 649, 853, 1085}; 
    int n = sizeof(tmp) / sizeof(tmp[0]);
    poly brr(tmp, tmp + n);
    poly arr; for(int i = 0; i < n; i++) arr.push_back(i);
    for(int l = 0; l < n - 1; l++){
        for(int r = l + 1; r < n - 1; r++){
            poly tmp = lip(arr, brr, l, r);
            for(int i = r + 1; i < n; i++) if(brr[i] != fun(tmp, i)) goto end;
            printf("%d %d: ", l, r); print(tmp);
            end:;
        }
    }
    return 0;
}