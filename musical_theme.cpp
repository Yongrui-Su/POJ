#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

struct suffix{
	int idx;
	int rank[2];
};

bool cmp(struct suffix a,struct suffix b){
	return (a.rank[0]==b.rank[0])?(a.rank[1]<b.rank[1]):(a.rank[0]<b.rank[0]);
}
suffix sa[20050];
int r[20050],ind[20050],lcp[20050],ans,n;
void buildSa(int n){
	for(int i = 0;i < n;i++){
		sa[i].idx = i;
		sa[i].rank[0] = r[i];
		sa[i].rank[1] = ((i+1) < n)?r[i+1]:-1;
	}
	sort(sa,sa+n,cmp);
	for(int k = 4;k < 2*n;k *= 2){
		int rank = 0;
		int prev_rank = sa[0].rank[0];
		sa[0].rank[0] = 0;
		ind[sa[0].idx] = 0;
		for(int i = 1;i < n;i++){
			if(sa[i].rank[0] == prev_rank&&sa[i].rank[1]==sa[i-1].rank[1]){
				prev_rank = sa[i].rank[0];
				sa[i].rank[0] = rank;
			}else{
				prev_rank = sa[i].rank[0];
				sa[i].rank[0] = ++rank;
			}
			ind[sa[i].idx] = i;
		}
		for(int i = 0;i < n;i++){
			int next = sa[i].idx +k/2;
			sa[i].rank[1] = (next < n)?sa[ind[next]].rank[0]:-1;
		}
		sort(sa,sa+n,cmp);
		
	}
	for(int i = 0;i < n;i++){
		ind[sa[i].idx] = i;
	}	
}

void cal_h(){
	int k = 0;
	for(int i = 0;i <n;i++){
		if(ind[i]==0){
			k = 0;
			continue;
		}
		int j = sa[ind[i]-1].idx;
		while(i+k <n&&j+k < n&&r[i+k]==r[j+k])k++;
		lcp[ind[i]] = k;
		if(k>0)k--;
	}
}

bool C(int mid,int len){
	for(int i = 1;i < len;i++){
		if(lcp[i] < mid)continue;
		for(int j = i-1;j >=0;j--){
			if(abs(sa[i].idx-sa[j].idx)>=mid)return true;
			if(lcp[j] < mid)break;
		}
	}
	return false;
}

void solver(){
	int l = 1;
	int r = n;
	while(l <=r){
		int mid = (l+r)>>1;
		if(C(mid,n)){
			l = mid+1;
			ans = mid;
		}else{
			r = mid-1;
		}
	}
}

int main(){
	while(scanf("%d",&n)&&n){
		for(int i = 0; i < n;i++)scanf("%d",&r[i]);
		if(n<10){
			printf("0\n");
			continue;
		}
		for(int i = 0;i < n;i++)r[i] = r[i+1]-r[i]+90;
		n--;
		buildSa(n);
		cal_h();
		solver();
		if(ans<4)printf("0\n");
		else printf("%d\n",ans+1);
		
	}
}
