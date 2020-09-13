### k次置换快速幂

```cpp
/*
from winterzz1
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int a[MAXN], b[MAXN], temp[MAXN], ans[MAXN], n, m;
int col[MAXN], T;
char s[MAXN];
long long k;
bool flag;
int hash1(int x, int y) { return x * m + y; }
set<int> se1, se2;
void quick_pow(int n, long long k) {
  for (int i = 0; i < n; ++i) ans[i] = i, b[i] = a[i];
  while (k) {
    if (k & 1) {
      for (int i = 0; i < n; ++i) temp[i] = b[ans[i]];
      for (int i = 0; i < n; ++i) ans[i] = temp[i];
    }
    for (int i = 0; i < n; ++i) temp[i] = b[b[i]];
    for (int i = 0; i < n; ++i) b[i] = temp[i];
    k >>= 1;
  }
  return;
}
int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%1d", &col[hash1(i, j)]);
      }
    }
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      for (int j = 0; j < m; ++j) {
        if (s[j] == 'U') a[hash1(i, j)] = hash1(i - 1, j);
        if (s[j] == 'D') a[hash1(i, j)] = hash1(i + 1, j);
        if (s[j] == 'L') a[hash1(i, j)] = hash1(i, j - 1);
        if (s[j] == 'R') a[hash1(i, j)] = hash1(i, j + 1);
      }
    }
    quick_pow(n * m, 2000000);
    se1.clear();
    se2.clear();
    for (int i = 0; i < n * m; ++i) {
      se1.insert(ans[i]);
      if (col[i] == 0) se2.insert(ans[i]);
    }
    printf("%d %d\n", (int)se1.size(), (int)se2.size());
  }
  return 0;
}
```

