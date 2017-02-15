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
  assert(1 <= n && n <= 8);

  vector< vector<int> > v(n, vector<int>(3));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 3; j++) {
      assert(scanf("%d", &v[i][j]) == 1);
      assert(1 <= v[i][j] && v[i][j] <= (int)1e9);
    }
  }

  vector<int> p(n);
  pair< long long, vector<int> > ans;
  for(int i = 0; i < n; i++) p[i] = i;
  do {
    vector<int> c(n);
    long long val = 0;
    for(int x : p) {
      int deg = 0;
      if(x-1 >= 0) deg += c[x-1];
      if(x+1  < n) deg += c[x+1];
      val += v[x][deg];
      c[x] = 1;
    }
    if(val > ans.first) {
      ans = make_pair(val, p);
    }
  }while(next_permutation(p.begin(), p.end()));

  printf("%lld\n", ans.first);
  for(int x : ans.second) printf("%d ", x+1);
  return 0;
}
