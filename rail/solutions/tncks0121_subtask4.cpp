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

const int N_ = 500500;
const int M_ = 500500;

const int MOD = (ll)1e9 + 7;

class modint {
  int v;
public:
  modint (): v(0) { }
  modint (ll v): v((v + MOD) % MOD) { }
  modint operator+ (modint x) { return v + x.v; }
  modint operator+= (modint x) { return *this = *this + x; }
  modint operator- (modint x) { return v - x.v; }
  modint operator-= (modint x) { return *this = *this - x; }
  modint operator* (modint x) { return (ll)v * x.v; }
  modint operator*= (modint x) { return *this = *this * x; }
  int& operator* () { return v; }
};

int N, M;
vector< pair<int, int> > intervals;

modint ans;

int F;
vector< int* > renum;

int main() {
  assert(scanf("%d%d", &N, &M) == 2);
  intervals.resize(M);
  renum.reserve(2*M);
  for(auto &interval : intervals) {
    assert(scanf("%d%d", &interval.first, &interval.second) == 2);
    assert(1 <= interval.first && interval.first < interval.second && interval.second <= N);
    renum.push_back(&interval.first);
    renum.push_back(&interval.second);
  }
  F = 1;
  renum.push_back(&F);
  renum.push_back(&N);

  sort(intervals.begin(), intervals.end());

  sort(renum.begin(), renum.end(), [&](const int *a, const int *b){
    return *a < *b;
  });

  for(int i = 0, k = 0; i < renum.size(); ) {
    int j = i, v = *renum[i];
    k += 1;
    for(; j < renum.size() && *renum[j] == v; j++) *renum[j] = k;
    i = j;
  }

  for(auto &interval : intervals) {
    interval.second -= 1;
  }
  N -= 1;

  vector<modint> cur(N+1), prv(N+1);

  prv[0] = 2;
  for(int j = 1; j <= intervals[0].second; j++) prv[j] = 1;

  for(int i = 1; i < M; i++) {
    int l, r; tie(l, r) = intervals[i];
    for(int j = 0; j <= l-1; j++) {
      cur[j] = prv[j] * 2;
    }
    for(int j = l; j <= r; j++) {
      cur[j] = prv[l-1] + prv[j];
    }
    for(int j = r+1; j <= N; j++) {
      cur[j] = prv[j] * 2;
    }
    prv = cur;
  }

  ans = prv[N];

  printf("%d\n", *prv[N]);
  return 0;
}
