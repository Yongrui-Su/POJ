#include <stdio.h>  
#include <string.h>  
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>  
#define M 16005 
using namespace std;  
struct segment{
	int y1,y2,x;
}seg[8005];  
bool cmp(const segment& a,const segment& b){
	return a.x==b.x?a.y2 < b.y2:a.x < b.x;
}
bool a[8005][8005];  
struct segnode{
	int l;
	int r;
	int val;
	segnode(int L,int R){
		this->l = L;
		this->r = R;
		val = -1;
	}
	segnode(){
		this->l = 0;
		this->r = 0;
		val = -1;
	}
}tree[M<<2];

class Segtree{
public:
	void build(int L,int R,int rt){
		if(L>R)return;
		tree[rt] = segnode(L,R);
		//cout<<rt<<" "<<tree[rt].l<<" "<<tree[rt].r<<endl;
		if(L==R)return;
		int mid = (L+R)>>1;
		build(L,mid,2*rt+1);
		build(mid+1,R,2*rt+2);
	}
	void push_down(int rt){
		if(tree[rt].l == tree[rt].r)return;
		if(tree[rt].val !=-1){
			tree[2*rt+1].val = tree[2*rt+2].val = tree[rt].val;
			tree[rt].val = -1;
		}
	}
	void push_up(int rt){
		if(tree[rt].l == tree[rt].r)return;
		tree[rt].val = (tree[2*rt+1].val==tree[2*rt+2].val)?tree[2*rt+1].val:-1;
	}
	void update(int rt,int L,int R,int v){
		
		if(L>tree[rt].r||R < tree[rt].l)return;
		if(L<=tree[rt].l&&R>=tree[rt].r){
			//cout<<tree[rt].l<<" "<<tree[rt].r<<" "<<v<<" "<<L<<" "<<R<<endl;
			tree[rt].val = v;
			return;
		}
		if(tree[rt].l == tree[rt].r)return;
		push_down(rt);
		update(2*rt+1,L,R,v);
		update(2*rt+2,L,R,v);
		push_up(rt);
	}
	void query(int rt,int L,int R, int v){
		if(L>tree[rt].r||R < tree[rt].l)return;
		if(tree[rt].val !=-1){
			//cout<<tree[rt].val<<" "<<v<<" left "<<tree[rt].l<<" right "<<tree[rt].r<<endl;
			a[tree[rt].val][v] = true;
			return;
		}
		//if()return;
		if(tree[rt].l == tree[rt].r)return;
		query(2*rt+1,L,R,v);
		query(2*rt+2,L,R,v);
	}
};

int main()  
{  
	int t;
	cin>>t;
	while(t>0){
		int n;
		cin>>n;
		int mmax = INT_MIN;
		int mmin = INT_MAX;
		memset(a,false,sizeof(a));  
		for(int i = 0;i < n;i++){
			cin>>seg[i].y1>>seg[i].y2>>seg[i].x;
			mmax = max(mmax,seg[i].y2);
			mmin = min(mmin,seg[i].y1);
		}
		sort(seg,seg+n,cmp);  
		Segtree tree;
		tree.build(2*mmin,2*mmax,0);
		int res = 0;
		for(int i = 0;i < n;i++){
			tree.query(0,2*seg[i].y1,2*seg[i].y2,i);
			tree.update(0,2*seg[i].y1,2*seg[i].y2,i);
		}
		for(int i = 0;i < n-1;i++)
		for(int j = i+1;j < n;j++){
			if(a[i][j]){
				for(int k = i+1;k <j;k++){
					if(a[i][k]&&a[k][j])res++;
				}
			}
		}
		cout<<res<<endl;
		t--;
	}
}  
