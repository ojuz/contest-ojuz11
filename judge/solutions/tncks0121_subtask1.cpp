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
  for(int tc = 0; tc < n; tc++) {
    int p, t;
    assert(scanf("%d%d", &p, &t) == 2);
    assert(0 <= p && p <= t);
    assert(t == 100);

    int ans;
    if(p == 0) ans = 2;
    else if(1 <= p && p <= 9) ans = 1;
    else ans = 0;

    printf("%d\n", ans);
  }
  return 0;
}
