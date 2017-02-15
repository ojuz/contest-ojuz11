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

int main() {
  assert(scanf("%d%d", &N, &M) == 2);
  assert(1 <= N && N <= 20);
  assert(1 <= M && M <= 20);
  intervals.resize(M);
  for(auto &interval : intervals) {
    assert(scanf("%d%d", &interval.first, &interval.second) == 2);
    assert(1 <= interval.first && interval.first < interval.second && interval.second <= N);
    interval.first -= 1;
    interval.second -= 2;
  }
  N--;

  vector<bool> vec(M);
  while(1) {
    vector<int> state(N+1);
    for(int i = 0; i < M; i++) {
      if(vec[i]) {
        int l, r; tie(l, r) = intervals[i];
        state[l] += 1;
        state[r+1] -= 1;
      }
    }
    for(int i = 1; i < N; i++) {
      state[i] += state[i-1];
    }
    if(*min_element(state.begin(), state.begin() + N) > 0) {
      ans += 1;
    }

    bool good = false;
    for(int i = M-1; i >= 0; i--) {
      if(!vec[i]) {
        vec[i] = true;
        good = true;
        break;
      }
      vec[i] = false;
    }
    if(!good) break;
  }

  printf("%d\n", *ans);
  return 0;
}
