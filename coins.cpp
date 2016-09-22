#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100001;
const int M = 100;
int coins[M];
int cnt[M];
bool f[N];
int mem[N];
int n,m;

int main(){
	while(scanf("%d %d",&n,&m)==2){
		if(n==0&&m==0)break;
		memset(f,false,sizeof(f));
		f[0] = true;
		for(int i = 0;i < n;i++)scanf("%d",&coins[i]);
		for(int i = 0;i < n;i++)scanf("%d",&cnt[i]);
		int ans = 0;
		for(int i = 0;i < n;i++){
			for(int k = 0;k <=m;k++)mem[k] = 0;
			for(int j = coins[i];j <= m;j++){
				if(!f[j]&&f[j-coins[i]]&&mem[j-coins[i]] < cnt[i]){
					f[j] = true;
					mem[j] = mem[j-coins[i]]+1;
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
}
