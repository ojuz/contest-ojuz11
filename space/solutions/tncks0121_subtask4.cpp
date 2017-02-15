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
  assert(1 <= n && n <= 10000);

  vector< vector<int> > v(n, vector<int>(3));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 3; j++) {
      assert(scanf("%d", &v[i][j]) == 1);
      assert(1 <= v[i][j] && v[i][j] <= (int)1e9);
    }
  }

  vector< long long > cost(n, -(ll)1e18);
  vector< int > rev(n);

  cost[0] = v[0][0];
  for(int i = 1; i < n; i++) {
    ll sum1 = 0, max01 = -(ll)1e18;
    for(int j = i; j >= 0; j--) {
      sum1 += v[j][1];
      max01 = max(max01, (long long)v[j][0] - v[j][1]);
      long long new_cost;
      if(j >= 2)
        new_cost = cost[j-2] + sum1 + max01 + v[j-1][2]; // [0, j-2]   ->   [j, i]    ->   j-1
      else if(j == 1)
        new_cost = sum1 + max01 + v[0][1]; // [1, i] -> 0
      else
        new_cost = sum1 + max01; // [0, i]

      if(cost[i] < new_cost) {
        cost[i] = new_cost;
        rev[i] = j;
      }
    }
  }

  printf("%lld\n", cost[n-1]);

  stack< pair<int, int> > stk;
  stk.push( pair<int, int> (0, n-1) );
  while(!stk.empty()) {
    int l, r; tie(l, r) = stk.top(); stk.pop();
    if(l == r) {
      printf("%d ", r+1);
      continue;
    }else if(l == 0) {
      int j = rev[r];
      if(j >= 2) {
        stk.push( pair<int, int> (j-1, j-1) );
        stk.push( pair<int, int> (j, r) );
        stk.push( pair<int, int> (0, j-2) );
        continue;
      }else if(j == 1) {
        stk.push( pair<int, int> (0, 0) );
        stk.push( pair<int, int> (1, r) );
        continue;
      }
    }

    // 1. find max01 position in [l, r]
    int f = l;
    long long sum1 = v[f][1];
    for(int i = l+1; i <= r; i++) {
      sum1 += v[i][1];
      if(v[i][0] - v[i][1] > v[f][0] - v[f][1])
        f = i;
    }

    printf("%d ", f+1);
    for(int x = f-1; x >= l; x--) printf("%d ", x+1);
    for(int x = f+1; x <= r; x++) printf("%d ", x+1);
  }

  return 0;
}
