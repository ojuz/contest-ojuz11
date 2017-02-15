#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pii;

int n;
lint a[1000005], b[1000005], c[1000005], dp[1000005], trk[1000005];

void update(lint &a, lint b, lint &c, lint d){
	if(a < b){
		a = b;
		c = d;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%lld %lld %lld",&a[i],&b[i],&c[i]);
		a[i] += a[i-1];
		b[i] += b[i-1];
		c[i] += c[i-1];
	}
	dp[1] = a[1];
	lint mx = -1e18, mxp = 0;
	for(int i=2; i<=n; i++){
		dp[i] = -1e18;
		update(dp[i], dp[i-1] + b[i] - b[i-1], trk[i], i-1);
		update(dp[i], b[i-1] + a[i] - a[i-1], trk[i], 0);
		update(dp[i], mx + a[i] - a[i-1] + b[i-1], trk[i], mxp);
		update(mx, dp[i-1] + c[i] - c[i-1] - b[i], mxp, i-1);
	}
	printf("%lld\n", dp[n]);
	vector<int> v;
	for(int i=n; i; i = trk[i]){
		for(int j=trk[i] + 1; j<=i; j++){
			v.push_back(j);
		}
	}
	reverse(v.begin(), v.end());
	for(auto &i : v) printf("%d ", i);
}
