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
  assert(1 <= k && k <= n && n <= 100);

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

  vector<modint> fac(n+1);
  fac[0] = 1;
  for(int i = 1; i <= n; i++) fac[i] = fac[i-1] * i;

  vector< vector<modint> > comb(n+1, vector<modint>(n+1));
  comb[0][0] = 1;
  for(int i = 1; i <= n; i++) {
    comb[i][0] = comb[i][i] = 1;
    for(int j = 1; j < n; j++) comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
  }

  auto count_ways = [&a, &b, &n, &k, &fac, &comb] (int high_bound, int low_bound) {
    // 최초 상위 k명은 최종 점수 high_bound 이상, 최초 하위 n-k명은 최종 점수 low_bound 이하인 경우의 수를 세는 함수.
    vector<int> bound(n, -1);
    for(int i = 0; i < k; i++) {
      for(int j = n-1; j >= 0; j--) {
        if(a[i] + b[j] >= high_bound) {
          bound[i] = j;
          break;
        }
      }
    }
    for(int i = k; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(a[i] + b[j] <= low_bound) {
          bound[i] = j;
          break;
        }
      }
    }

    if(find(bound.begin(), bound.end(), -1) != bound.end()) {
      return modint(0);
    }

    vector< vector<modint> > ta(n, vector<modint>(k+1));

    for(int j = n-1; j >= bound[k]; j--) {
      int h = 0;
      for(int i = 0; i < k; i++) if(j <= bound[i]) h += 1;
      ta[j][0] = 1;
      if(j == n-1) {
        ta[j][1] = h;
      }else {
        for(int i = 1; i <= k; i++) {
          ta[j][i] = ta[j+1][i] + ta[j+1][i-1] * max(h - (i-1), 0);
        }
      }
    }

    vector< vector<modint> > tb(n, vector<modint>(n));
    modint ways = 0;

    for(int s = 0; s <= k; s++) {
      tb[k-1][s] = ta[bound[k]][s] * fac[k-s];
    }
    for(int i = k; i < n; i++) {
      int w = (i == k) ? 0 : (bound[i-1] - bound[i]);
      for(int s = 0; s <= k; s++) {
        for(int c = 0; c <= w && c <= s; c++) {
          tb[i][s] += tb[i-1][s-c] * comb[w][c] * max((n - bound[i]) - (i - k) - s, 0);
        }
      }
    }
    for(int s = 0; s <= k; s++) {
      ways += tb[n-1][s] * comb[bound[n-1]][k-s];
    }
    return ways;
  };

  modint ans = 0;

  if(k == n) {
    ans = fac[n];
  }else {
    set<int> cuts;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
      cuts.insert(a[i] + b[j]);
    }
    for(int cut : cuts) {
      ans += count_ways(cut, cut) - count_ways(cut+1, cut);
    }
  }

  printf("%d\n", *ans);
  return 0;
}
