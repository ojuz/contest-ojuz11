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
  int n, k;
  assert(scanf("%d%d", &n, &k) == 2);
  assert(1 <= k && k <= n && n <= 8);

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
  sort(b.begin(), b.end());

  int ans = 0;

  do {
    vector<int> s(n);
    for(int i = 0; i < n; i++) s[i] = a[i] + b[i];

    bool good = true;
    for(int i = 0; i < k; i++) {
      int rank = 1;
      for(int j = 0; j < n; j++) {
        if(s[j] > s[i]) rank += 1;
      }
      if(rank > k) good = false;

      for(int j = k; j < n; j++) {
        if(s[i] < s[j]) good = false;
      }
    }

    if(good) ans += 1;
  }while(next_permutation(b.begin(), b.end()));

  printf("%d\n", ans);
  return 0;
}
