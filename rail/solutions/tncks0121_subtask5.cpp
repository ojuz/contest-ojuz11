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
const int MAX_TREE_SIZE = 1<<21;

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

int F, N, M;
vector< pair<int, int> > intervals;
vector< int* > renum;

// 서브태스크:
//  1. n, m <= 20
//  2. n <= 20 (합쳐서 10점)
//  3. n <= 1000, m <= 1000
//  4. 포함 관계
//  5. n <= 500000, m <= 500000

namespace segtree {
  struct node {
    modint sum, mul, add;
    node(modint sum = 0, modint mul = 1, modint add = 0): sum(sum), mul(mul), add(add) { }
  };

  vector<node> tree(MAX_TREE_SIZE + 1);

  void spread (int idx, int nl, int nr) {
    node& nd = tree[idx];
    node& c1 = (nl == nr) ? tree[0] : tree[idx * 2];
    node& c2 = (nl == nr) ? tree[0] : tree[idx * 2 + 1];

    if(nd.mul != 1) {
      nd.sum *= nd.mul;
      for(auto &child : {&c1, &c2}) {
        child->mul *= nd.mul;
        child->add *= nd.mul;
      }
      nd.mul = 1;
    }

    if(nd.add != 0) {
      nd.sum += nd.add * (nr - nl + 1);
      for(auto &child : {&c1, &c2}) {
        child->add += nd.add;
      }
      nd.add = 0;
    }
  }

  modint update (int idx, int nl, int nr, int l, int r, char type, modint v) {
    if(l > r) return 0;
    node &nd = tree[idx];
    spread(idx, nl, nr);
    if(l <= nl && nr <= r) {
      (type == '*' ? nd.mul : nd.add) = v;
      spread(idx, nl, nr);
      return nd.sum;
    }
    int nm = (nl + nr) >> 1;
    nd.sum = 0;
    if(l <= nm) nd.sum += update(idx*2,   nl, nm,   l, min(nm, r),   type, v);
    if(r >  nm) nd.sum += update(idx*2+1, nm+1, nr, max(nm+1, l), r, type, v);
    return nd.sum;
  }

  void multiply(int l, int r, modint v) {
    update(1, 0, N, l, r, '*', v);
  }

  void add (int l, int r, modint v) {
    update(1, 0, N, l, r, '+', v);
  }

  modint get (int idx, int nl, int nr, int x) {
    spread(idx, nl, nr);
    if(nl == nr) return tree[idx].sum;
    int nm = (nl + nr) >> 1;
    return (x <= nm) ?
                get(idx*2,   nl, nm,   x) :
                get(idx*2+1, nm+1, nr, x);
  }

  modint get(int x) {
    return get(1, 0, N, x);
  }
};

modint ans;

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
  int mxr = 1;
  for(auto &interval : intervals) {
    if(mxr < interval.first) {
      printf("0\n");
      return 0;
    }
    mxr = max(mxr, interval.second);
  }

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

  segtree::add(0, 0, 1);
  for(auto &interval : intervals) {
    int l, r; tie(l, r) = interval;
    modint v = segtree::get(l-1);
    segtree::multiply(0, l-1, 2);
    segtree::add(l, r, v);
    segtree::multiply(r+1, N, 2);
  }

  ans = segtree::get(N);
  printf("%d\n", *ans);
  return 0;
}
