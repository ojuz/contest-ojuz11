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

using namespace std;
typedef long long ll;
typedef unsigned long long llu;
typedef double lf;
typedef unsigned int uint;
typedef long double llf;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

#define debug(format, ...) printf(format, __VA_ARGS__);

const int N_ = 200500;

int N;
long long V[N_][3];

long long tb[N_][3], mx[3];
int tbp[N_][3], mxp[3];

long long sum1;

int timing[N_];

int main() {
  scanf("%d", &N);
  for(int i = 1; i <= N; i++) {
    for(int k = 0; k < 3; k++) {
      scanf("%lld", &V[i][k]);
    }
    sum1 += V[i][1];
    V[i][0] -= V[i][1];
    V[i][2] -= V[i][1];
    V[i][1] = 0;
  }

  tb[1][0] = V[1][0];
  tie(mx[0], mxp[0]) = make_pair(tb[1][0], 1);

  tb[1][2] = -(ll)1e18;
  tie(mx[2], mxp[2]) = make_pair(tb[1][2], 1);

  for(int i = 2; i <= N; i++) {
    tie(tb[i][0], tbp[i][0]) = max(make_pair(mx[2] + V[i][0], mxp[2]), make_pair(V[i][0], 0));
    tie(tb[i][2], tbp[i][2]) = make_pair(mx[0] + V[i][2], mxp[0]);
    for(int k = 0; k < 3; k++) {
      if(mx[k] < tb[i][k])
        tie(mx[k], mxp[k]) = make_pair(tb[i][k], i);
    }
  }

  printf("%lld\n", mx[0] + sum1);

  fill(timing + 1, timing + N + 1, 1);
  for(int i = mxp[0], s = 0; i > 0; i = tbp[i][s], s = 2 - s) {
    timing[i] = s;
  }

  for(int i = 1; i <= N; i++) {
    if(timing[i] == 0) printf("%d ", i);
  }
  for(int i = 1; i <= N; i++) {
    if(timing[i] == 0) {
      for(int j = i+1; j <= N && timing[j] == 1; j++) printf("%d ", j);
      for(int j = i-1; j > 0 && timing[j] == 1; j--) printf("%d ", j);
    }
  }
  for(int i = 1; i <= N; i++) {
    if(timing[i] == 2) printf("%d ", i);
  }

  return 0;
}
