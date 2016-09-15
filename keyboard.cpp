#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <string>
//#include <unordered_map>
using namespace std;
const int M = 91;

int sum[M][M];
int dp[M][M];
int idx[M][M];
string key;
string lett;
int freq[M];
void initial(){
	for(int i = 0;i < M;i++){
		for(int j = 0;j  < M;j++)sum[i][j] = 0;
	}
	for(int i = 0;i < M;i++){
		for(int j = 0;j  < M;j++)dp[i][j] = INT_MAX;
	}
	for(int i = 0;i < M;i++){
		for(int j = 0;j  < M;j++)idx[i][j] = -1;
	}	
}


void local_cost(int* f,int L){
	for(int i = 0;i < L;i++)
	for(int j = i; j < L;j++){
		sum[i][j] = sum[i][j-1] + f[j]*(j-i+1);
	}
}

int main(){
	int t,K,L;
	cin>>t;
	int cnt = 0;
	while(t--){
		initial();
		cin>>K>>L;
		cin>>key;
		cin>>lett;
		

		
		for(int i = 0;i < L;i++)cin>>freq[i];
		local_cost(freq,L);
		
		for(int i = 0;i < K;i++){
			if(i == 0){
				for(int j = i;j < L;j++){
					dp[i][j] = sum[0][j];
					idx[0][j] = 0;
				}
			}else{
				int tmp = i;
				for(int j = i;j < L;j++){
					for(int z=i; z <=j;z++){
						if(dp[i-1][z-1] + sum[z][j] < dp[i][j]){
							dp[i][j] = dp[i-1][z-1] + sum[z][j];
							idx[i][j] = z;
						}
					}
					//cout<<i<<" "<<j<<" "<<idx[i][j]<<" "<<dp[i][j]<<endl;
				}
			}
		} 
		vector<string> res(K,"");
		int i = K;
		int last = L;
		while(i > 0){
			res[i-1] = lett.substr(idx[i-1][last-1],last-idx[i-1][last-1]);
			last = idx[i-1][last-1];
			i--;
		}
		cout<<"Keypad #"<<++cnt<<":"<<endl;
		for(int i = 0;i < K;i++){
			cout<<key[i]<<": "<<res[i]<<endl;
		}
		cout<<endl;
	}
	return 0;
}
