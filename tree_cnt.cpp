#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int dp[1000];

int tree_cnt(int n){
	int &ans = dp[n];
	if(ans!=0)return ans;
	if(n==1||n==2){
		ans = 1;
		return ans;
	}
	ans = tree_cnt(n-1)*tree_cnt(n-1);
	for(int i = 1;i <=n-2;i++){
		ans += 2*tree_cnt(n-1)*tree_cnt(i);
	}
	return ans;
}

int main(){
	
	int n;
	while(cin>>n&&n){
		memset(dp,0,sizeof(dp));
		cout<<tree_cnt(n)<<endl;
	}
}
