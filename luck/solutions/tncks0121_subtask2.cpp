#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <deque>
#include <utility>
#include <bitset>
#include <limits.h>
#include <time.h>
#include <functional>
#include <numeric>
#include <iostream>

using namespace std;
typedef long long ll;
typedef unsigned long long llu;
typedef double lf;
typedef unsigned int uint;
typedef long double llf;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

const int MOD = (int)1e9 + 7;

class modint {
  int v;
public:
  modint (): v(0) { }
  modint (ll v): v((v + MOD) % MOD) { }

  bool operator== (modint x) { return v == x.v; }
  bool operator!= (modint x) { return v != x.v; }

  modint operator+ (modint x) { return v + x.v; }
  modint operator- (modint x) { return v - x.v; }
  modint operator* (modint x) { return (ll)v * x.v; }

  modint& operator+= (const modint x) { return *this = (*this + x); }
  modint& operator-= (const modint x) { return *this = (*this - x); }
  modint& operator*= (const modint x) { return *this = (*this * x); }

  int operator* () { return v; }
};

int main() {
  int n, k;
  assert(scanf("%d%d", &n, &k) == 2);
  assert(1 == k && k <= n && n <= 100);

  vector<int> a(n), b(n);
  for(int &x : a) {
    assert(scanf("%d", &x) == 1);
    assert(1 <= x && x <= 1000);
  }
  for(int &y : b) {
    assert(scanf("%d", &y) == 1);
    assert(1 <= y && y <= 1000);
  }
  sort(a.begin(), a.end(), greater<int>());
  sort(b.begin(), b.end(), greater<int>());

  modint ans = 0;

  for(int i = 0; i < n; i++) {
    int cut = a[0] + b[i];
    modint cur = 1;
    for(int j = 1; j < n; j++) { // match a[j] and b[k]
      int c = 0;
      for(int k = 0; k < n; k++) {
        if(k != i && a[j] + b[k] <= cut) c++;
      }
      cur *= max(0, c - (j-1));
    }
    ans += cur;
  }

  printf("%d\n", *ans);
  return 0;
}
