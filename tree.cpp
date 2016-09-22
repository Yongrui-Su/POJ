#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>  
using namespace std;
const int N = 100001;
struct node{
	int v,l;
	node(int _v,int _l){
		v = _v;
		l = _l;
	}
};
vector<node> edge[N];
int ans,K,root,size,n;
int s[N],f[N],d[N];
int done[N];
vector<int> depth;

void get_root(int,int);
void get_depth(int,int);
int calc(int,int);
void worker(int);

void add_edge(int u,int v,int l){
	edge[u].push_back(node(v,l));
}	
void read(){
	memset(done,false,sizeof(done));
	for(int i = 0;i < n;i++)edge[i].clear();
	int u,v,l;
	for(int i = 1; i < n;i++){
		cin>>u>>v>>l;
		add_edge(u,v,l);
		add_edge(v,u,l);
	}
}
void print(){
	size = n;
	f[0] = size;	
	ans = 0;
	get_root(1,root= 0);
	worker(root);
	cout<<ans<<endl;
}
void get_root(int now,int fa){
	s[now] = 1;
	f[now] = 0;
	int u;
	for(int i = 0;i < edge[now].size();i++){
		if((u = edge[now][i].v)!=fa&&!done[u]){
			get_root(u,now);
			s[now] += s[u];
			f[now] = max(f[now],s[u]);
		}
	}
	f[now] = max(f[now],size-s[now]);
	if(f[now] < f[root])root = now;
}
void get_depth(int now,int fa){
	s[now] = 1;
	int u;
	depth.push_back(d[now]);
	for(int i = 0;i < edge[now].size();i++){
		if((u=edge[now][i].v)!=fa&&!done[u]){
			d[u] = d[now] + edge[now][i].l;
			get_depth(u,now);
			s[now] += s[u];
		}
	}
}

int calc(int now,int init){
    depth.clear(); d[now] = init;  
    get_depth(now, 0);  
    sort(depth.begin(), depth.end());  
    int ret = 0;  
    for (int l=0, r=depth.size()-1; l<r; )  
        if (depth[l] + depth[r] <= K) ret += r-l++;  
        else r--;  
	return ret;
}

void worker(int now){
	ans += calc(now,0);
	done[now] = true;
	int u;
	for(int i = 0;i < edge[now].size();i++){
		if(!done[u=edge[now][i].v]){
			ans -= calc(u,edge[now][i].l);
			size = s[u];
			f[0] = size;
			get_root(u,root=0);
			worker(root);
		}
	}
	
}

/*int main() {  
  
    while (scanf("%d%d", &n, &K) == 2) {  
        if (n == 0 && K == 0) break;  
        for (int i=0; i<=n; i++) edge[i].clear();  
        memset(done, false, sizeof(done));  
  
        int u, v, l;  
        for (int i=1; i<n; i++) {  
            scanf("%d%d%d", &u, &v, &l);  
            edge[u].push_back(node(v, l));  
            edge[v].push_back(node(u, l));  
        }  
        f[0] = size = n;  
        get_root(1, root=0);  
        ans = 0;  
        worker(root);  
        printf("%d\n", ans);  
    }  
    return 0;  
}  */
int main(){
	int k;
	while(true){
		cin>>n>>K;
		if(n==0&&K==0)break;
        for (int i=0; i<=n; i++) edge[i].clear();  
        memset(done, false, sizeof(done));  
  
        int u, v, l;  
        for (int i=1; i<n; i++) {  
            scanf("%d%d%d", &u, &v, &l);  
            edge[u].push_back(node(v, l));  
            edge[v].push_back(node(u, l));  
        }  
		print();
	}
}
