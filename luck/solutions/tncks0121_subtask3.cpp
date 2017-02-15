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
  assert(1 <= k && k <= n && n <= 15);

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

  vector< vector<int> > on(1<<n);
  for(int mask = 1; mask < (1<<n); mask++) {
    for(int i = 0; i < n; i++) if((mask >> i) & 1) {
      on[mask].push_back(i);
    }
  }

  auto count_ways = [&a, &b, &n, &k, &on] (int high_bound, int low_bound) {
    // 최초 상위 k명은 최종 점수 high_bound 이상, 최초 하위 n-k명은 최종 점수 low_bound 이하인 경우의 수를 세는 함수.
    vector< vector<bool> > allowed(n, vector<bool>(n));
    for(int i = 0; i < k; i++) {
      for(int j = 0; j < n; j++) {
        if(a[i] + b[j] >= high_bound) allowed[i][j] = true;
      }
    }
    for(int i = k; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(a[i] + b[j] <= low_bound) allowed[i][j] = true;
      }
    }

    vector<modint> ways(1<<n);
    ways[0] = 1;
    for(int mask = 1; mask < (1<<n); mask++) {
      int i = on[mask].size()-1;
      for(int j : on[mask]) {
        if(allowed[i][j])
          ways[mask] += ways[mask ^ (1<<j)];
      }
    }
    return ways[(1<<n)-1];
  };

  modint ans = 0;

  set<int> cuts;
  for(int i = 0; i < k; i++) for(int j = 0; j < n; j++) {
    cuts.insert(a[i] + b[j]);
  }
  for(int cut : cuts) {
    ans += count_ways(cut, cut) - count_ways(cut+1, cut);
  }

  printf("%d\n", *ans);
  return 0;
}
