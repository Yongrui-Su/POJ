#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
using namespace std;

void print_out(vector<int> pages,vector<vector<int> >& idx,int k,int m){
	if(k<0||m<0)return;
	print_out(pages,idx,k-1,idx[k][m]);
	if(k!=0)cout<<" / ";
	for(int i = idx[k][m]+1;i <=m;i++){
		cout<<pages[i];
		if(i!=m)cout<<" ";
	}
}
void print(int m,int n,int now,int res,vector<int>& pages){//m表示是当前  
    if(n==-1)  
        return;  
    if(now+pages[n] > res || m>n){//如果段长超过最优值或者剩下的不够每段至少一个数，那么此段输出完毕。  
        print(m-1,n,0,res,pages);  
        printf("/ ");  
    }else{  
        print(m,n-1,now+pages[n],res,pages);  
        printf("%d ",pages[n]);  
    }  
}  

int main(){
	int t,m,k;
	cin>>t;
	while(t--){
		cin>>m>>k;
		vector<vector<int> > dp(k,vector<int>(m,0));
		vector<vector<int> > idx(k,vector<int>(m,0));
		vector<int> pages(m,0);
		for(int i = 0;i < m;i++)cin>>pages[i];
		for(int i = 0;i < k;i++){
			dp[i][0] = pages[0];
		}
		idx[0][0] = -1;
		for(int i = 0;i < k;i++)
		for(int j = 1;j < m;j++){
			if(i==0){
				dp[i][j] = dp[i][j-1]+pages[j];
				idx[i][j] = -1;
				continue;
			}
			
			if(i==j){
				dp[i][j] = max(dp[i-1][j-1],pages[j]);
				idx[i][j] = j-1;
				//if(j>=i)cout<<i<<" "<<j<<" "<<idx[i][j]<<" "<<dp[i][j]<<endl;
			}else if(j < i){
				dp[i][j] = dp[i-1][j];
				idx[i][j] = idx[i-1][j];
			}else{
				int m = pages[j];
				dp[i][j] = max(dp[i-1][j-1],pages[j]);
				idx[i][j] = j-1;
				for(int a = j-2;a>=i-1;a--){
					m += pages[a+1];
					int cur = max(dp[i-1][a],m);
					if(cur <= dp[i][j]){
						dp[i][j] = cur;
						idx[i][j] = a;
					}
				}
				//if(j>=i)cout<<i<<" "<<j<<" "<<idx[i][j]<<" "<<dp[i][j]<<endl;
			}
		}
		 //print_out(pages,idx,k-1,m-1);
		 print(k-1,m-1,0,dp.back().back(),pages);
		cout<<endl;
	}
	
}
