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

  bool operator== (modint x) { return v == x.v; }
  bool operator!= (modint x) { return v != x.v; }

  modint operator+ (modint x) { return v + x.v; }
  modint operator- (modint x) { return v - x.v; }
  modint operator* (modint x) { return (ll)v * x.v; }

  modint& operator+= (const modint x) { return *this = (*this + x); }
  modint& operator-= (const modint x) { return *this = (*this - x); }
  modint& operator*= (const modint x) { return *this = (*this * x); }

  int operator* () { return v; }
};

int N, M;
vector< pair<int, int> > intervals;
int F;
vector< int* > renum;

int main() {
  assert(scanf("%d%d", &N, &M) == 2);
  intervals.reserve(M+1);
  intervals.resize(M);
  renum.reserve(2*M);
  for(auto &interval : intervals) {
    assert(scanf("%d%d", &interval.first, &interval.second) == 2);
    assert(1 <= interval.first && interval.first < interval.second && interval.second <= N);
    renum.push_back(&interval.first);
    renum.push_back(&interval.second);
  }

  sort(intervals.begin(), intervals.end());
  int mxr = 1;
  for(auto &interval : intervals) {
    if(mxr+1 < interval.first) {
      printf("0\n");
      return 0;
    }
    mxr = max(mxr, interval.second);
  }

  {
    intervals.push_back(pair<int, int>(1, N));
    pair<int, int> &interval = intervals[M];
    renum.push_back(&interval.first);
    renum.push_back(&interval.second);
  }

  F = 1;
  renum.push_back(&F);
  N -= 1;
  renum.push_back(&N);

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

  sort(intervals.begin(), intervals.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
    return make_pair(a.first, -a.second) < make_pair(b.first, -b.second);
  });

  // 0. 전처리
  vector<modint> pow2(M+1);
  pow2[0] = 1;
  for(int i = 1; i <= M; i++) {
    pow2[i] = pow2[i-1] * 2;
  }

  // 1. 중복 제거
  vector< pair< pair<int, int>, int> > unique_intervals;
  for(int i = 0; i < intervals.size(); ) {
    int j = i;
    while(j < intervals.size() && intervals[i] == intervals[j])
      j += 1;
    unique_intervals.push_back(make_pair(intervals[i], j - i - (i == 0)));
    i = j;
  }

  // 2.
  stack<int> stk;
  vector< vector<int> > childs(unique_intervals.size());
  vector<int> parent(unique_intervals.size(), -1);
  vector<int> roots;
  modint ans = 1;

  for(int i = 0; i < unique_intervals.size(); i++) {
    pair<int, int> interval; int cnt;
    tie(interval, cnt) = unique_intervals[i];
    while(!stk.empty()) {
      int tp = stk.top();
      if(unique_intervals[tp].first.second < interval.first) {
        stk.pop();
      }else {
        childs[tp].push_back(i);
        parent[i] = tp;
        break;
      }
    }
    if(stk.empty()) {
      roots.push_back(i);
    }
    stk.push(i);
  }

  queue<int> que;
  vector<int> deg(unique_intervals.size());
  vector<modint> ways(unique_intervals.size());
  vector<int> subtree_size(unique_intervals.size());

  for(int i = 0; i < unique_intervals.size(); i++) {
    deg[i] = childs[i].size();
    if(deg[i] == 0) {
      que.push(i);
    }
  }

  while(!que.empty()) {
    int u = que.front(); que.pop();
    pair<int, int> interval; int cnt;
    tie(interval, cnt) = unique_intervals[u];

    subtree_size[u] += cnt;

    int p = parent[u];
    if(p >= 0) {
      if(--deg[p] == 0) que.push(p);
      subtree_size[p] += subtree_size[u];
    }

    pair<int, int> merged(-1, -1);
    for(auto ch : childs[u]) {
      if(merged.first == -1) merged = unique_intervals[ch].first;
      else if(merged.second + 1 == unique_intervals[ch].first.first)
        merged = make_pair(merged.first, unique_intervals[ch].first.second);
      else {
        merged = make_pair(-2, -2);
        break;
      }
    }

    ways[u] = pow2[subtree_size[u] - cnt] * (pow2[cnt] - 1);
    if(merged == interval) {
      modint cur = 1;
      for(int child : childs[u]) cur *= ways[child];
      ways[u] += cur;
    }
  }

  assert(roots.size() == 1);
  printf("%d\n", *ways[roots[0]]);
  return 0;
}
