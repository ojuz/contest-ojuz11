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
    assert(1 <= t && t <= (int)2e9);

    char strp[20];
    sprintf(strp, "%d", p);

    int ans = -1;
    for(int i = 0; i < 10; i++) {
      long long new_score;
      sscanf((string("1") + string(i, '0') + strp).c_str(), "%lld", &new_score);
      if(!(p < new_score && new_score <= t)) {
        ans = i;
        break;
      }
    }
    assert(ans >= 0);

    printf("%d\n", ans);
  }
  return 0;
}
