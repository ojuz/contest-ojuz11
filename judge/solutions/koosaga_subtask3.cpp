#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int get_jarisoo(int x){
	if(x == 0) return 1;
	int ans = 0;
	while(x){
		ans++;
		x /= 10;
	}
	return ans;
}

lint pw[18];

int main(){
	pw[0] = 1;
	for(int i=1; i<18; i++)pw[i] = pw[i-1] * 10;
	int q;
	cin >> q;
	while(q--){
		int a, b;
		cin >> a >> b;
		int z = get_jarisoo(a);
		for(int i=0; ; i++){
			if(a + pw[z + i] > b){
				printf("%d\n", i);
				break;
			}
		}
	}
}