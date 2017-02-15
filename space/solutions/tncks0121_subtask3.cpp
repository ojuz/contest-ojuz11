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
  assert(1 <= n && n <= 300);

  vector< vector<int> > v(n, vector<int>(3));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 3; j++) {
      assert(scanf("%d", &v[i][j]) == 1);
      assert(1 <= v[i][j] && v[i][j] <= (int)1e9);
    }
  }

  vector< vector<long long> > cost(n, vector<long long>(n));
  vector< vector<int> > rev(n, vector<int>(n));

  for(int i = 0; i < n; i++) {
    cost[i][i] = v[i][0]; // i 혼자만 사용
  }
  for(int diff = 1; diff < n; diff++) {
    for(int l = 0, r = diff; r < n; l++, r++) {
      // [l+1, f] => l (인접한 1개가 사용됨)

      for(int f = l; f <= r; f++) {
        // f: 마지막으로 날릴 공의 번호.

        long long new_cost;
        if(f == l)
          new_cost = cost[l+1][r] + v[f][1]; // [l+1, r] => l (인접한 1개만 사용됨)
        else if(f == r)
          new_cost = cost[l][r-1] + v[f][1]; // [l, r-1] => r (인접한 1개만 사용됨)
        else
          new_cost = cost[l][f-1] + cost[f+1][r] + v[f][2]; // [l, f-1] => [f+1, r] => f (인접한 2개가 모두 사용됨)

        if(cost[l][r] < new_cost) {
          cost[l][r] = new_cost;
          rev[l][r] = f;
        }
      }
    }
  }

  printf("%lld\n", cost[0][n-1]);

  stack< pair<int, int> > stk;
    // pair.first >= 0이면 pair는 구간을 나타냄.

  stk.push(pair<int, int> (0, n-1));
  while(!stk.empty()) {
    int l, r; tie(l, r) = stk.top(); stk.pop();
    if(l == r) {
      printf("%d ", r+1);
      continue;
    }

    int f = rev[l][r];
    stk.push(pair<int, int>(f, f));

    if(l <= f-1)
      stk.push(pair<int, int>(l, f-1));

    if(f+1 <= r)
      stk.push(pair<int, int>(f+1, r));
  }
  return 0;
}
