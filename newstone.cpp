#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 101;

int cnt[MAXN];


int main(){
	int n,x;
	while(cin>>n&&n){
		memset(cnt,0,sizeof(cnt));
		for(int i = 0; i < n;i++){
			cin>>x;
			cnt[x]++;
		}
		
		if(n&1){
			cout<<1<<endl;
		}else{
			int i;
			for(i = 0; i < MAXN;i++){
				if(cnt[i]%2)break;
			}
			cout<<(i==MAXN?0:1)<<endl;
		}
	}
}
