#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

vector<vector<int> > dp;
vector<vector<int> > sum;


void cal_cost(vector<int>& pos){
	for(int i = 0;i < pos.size()-1;i++)
	for(int j = i+1;j <pos.size();j++){
		sum[i][j] = sum[i][j-1] + pos[j]-pos[(i+j)/2];
	}
}
int main(){
	int n,p;
	cin>>n>>p;
	vector<int> pos(n,0);
	for(int i = 0;i < n;i++){
		cin>>pos[i];
	}
	dp = vector<vector<int> >(p,vector<int>(n,INT_MAX));
	sum = vector<vector<int> >(n,vector<int>(n,0));
	cal_cost(pos);
	for(int i = 0;i < p;i++){
		for(int j = i;j < n;j++){
			if(i==0)dp[0][j]= sum[0][j];
			else if(j!=i){
				for(int k = i;k <j;k++){
					dp[i][j] = min(dp[i][j],dp[i-1][k]+sum[k+1][j]);
					//cout<<dp[i-1][k]<<" "<<sum[k+1][j]<<" "<<i<<" "<<j<<" "<<k<<endl;
					
				}
			}else if(j==i){
				dp[i][j] = 0;
			}
		}
	}
	cout<<dp[p-1][n-1]<<endl;
}
