#include <iostream>
#include <cstdio>
using namespace std;

int f[30001],n;


bool ok(int time){
	bool flg = false;
	int pos = 1,np,cost = 0;
	//cout<<time<<" pos ";
	for(int i = 0;i < n;i++){
		if((f[i]-pos)*20+cost > time){
			if(flg)cost+=10;
			else flg = true;
			if((f[i]-pos)*4+cost > time){
				//cout<<"False"<<endl;
				return false;
			}
			for(np = f[i];(np-pos)*4+(np-f[i])*20 +cost <= time;np++);
			np--;
			cost += (np-pos)*4;
			//cout<<np<<" ";
			pos = np;
		}
	}
	//cout<<"True"<<endl;
	return true;
}


int main(){
	while(scanf("%d",&n)&&n){
		for(int i = 0;i < n;i++)scanf("%d",&f[i]);
		int l = (f[n-1]-1)*4;
		int r = (f[n-1]-1)*20+1;
		while(l < r){
			int mid = (l+r)>>1;
			if(ok(mid)){
				r = mid;
			}else l = mid +1;
		}
		cout<<r<<endl;
	}
}
