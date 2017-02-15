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

int main() {
  int n;
  assert(scanf("%d", &n) == 1);
  assert(1 <= n && n <= 20);

  vector< vector<int> > v(n, vector<int>(3));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 3; j++) {
      assert(scanf("%d", &v[i][j]) == 1);
      assert(1 <= v[i][j] && v[i][j] <= (int)1e9);
    }
  }

  vector<long long> cost(1 << n);
  vector<int> rev(1 << n);

  for(int mask = 0; mask < (1<<n); mask++) {
    for(int i = 0; i < n; i++) if((~mask >> i) & 1) {
      int deg = 0;
      if(i-1 >= 0 && (mask >> (i-1)) & 1) deg += 1;
      if(i+1 <  n && (mask >> (i+1)) & 1) deg += 1;

      long long new_cost = cost[mask] + v[i][deg];
      if(cost[mask | (1<<i)] < new_cost) {
        cost[mask | (1<<i)] = new_cost;
        rev[mask | (1<<i)] = i;
      }
    }
  }

  vector<int> p;
  for(int mask = (1<<n)-1; mask > 0; mask ^= 1<<rev[mask]) {
    p.push_back(rev[mask]);
  }
  reverse(p.begin(), p.end());

  printf("%lld\n", cost[(1<<n) - 1]);
  for(int x : p) printf("%d ", x+1);
  return 0;
}
