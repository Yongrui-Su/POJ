#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Treap{
    int val, prior, cnt;
    Treap *l, *r;
    Treap(int v): l(NULL), r(NULL), val(v), prior((rand() << 15) + rand()), cnt(1) {}
};

int sz(Treap *t) {return (t == NULL) ? 0:t->cnt;}

void upd_sz(Treap *t){
    if(t) t->cnt = 1 + sz(t->l) + sz(t->r);
}

void split(Treap *t, Treap *&l, Treap *&r, int pos, int add = 0)
{
    if(!t) return void(l = r = NULL);
    int cur_pos = add + sz(t->l) + 1;
    if(cur_pos <= pos) split(t->r, t->r, r, pos, cur_pos), l = t;
    else split(t->l, l ,t->l, pos, add), r = t;
    upd_sz(t);
}

void merge(Treap *&t, Treap *l, Treap *r)
{
    if(!l || !r) t = l? l:r;
    else if(l->prior > r->prior) {merge(l->r, l->r, r); t = l;}
    else {merge(r->l, l, r->l);t = r;}
    upd_sz(t);
}

void insert(Treap *&t, int pos, int val)
{
    Treap *l, *r, *cur = new Treap(val);
    split(t, l, r, pos-1);
    merge(t, l, cur);
    merge(t, t, r);
}

void erase(Treap *&t, int pos)
{
    Treap *l, *r, *g;
    split(t, l, r, pos-1);
    split(r, g, r, 1);
    merge(t, l, r);
}

int find_kth(Treap *t, int k, int add = 0)
{
    int cur_pos = add + sz(t->l) + 1;
    if(cur_pos == k) return t-> val;
    if(cur_pos < k) return find_kth(t->r, k, cur_pos);
    return find_kth(t->l, k, add);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,m;
    cin>>n>>m;
    //treap tr;
    Treap* rt = NULL;
    int type,low,up;
    Treap *leftpart,*midpart,*rightpart;
    for(int i = 0;i < n;i++){
        int a;
        cin>>a;
        insert(rt,i+1,a);
    }
    for(int i = 1;i <= m;i++){
        cin>>type>>low>>up;
        split(rt,leftpart,rightpart,low-1);
        //split(rt,midnode,rightnode,up,low-1);
        split(rightpart,midpart,rightpart,up-low+1);
        if(type==1){
            merge(rt,midpart,leftpart);
            merge(rt,rt,rightpart);
        }else{
            merge(rt,leftpart,rightpart);
            merge(rt,rt,midpart);
        }
        cout<<abs(find_kth(rt,1)-find_kth(rt,n))<<endl;
        for(int i = 0;i < n;i++){
            cout<<find_kth(rt,i+1)<<" ";
        }
        cout<<endl;
    }
    return 0;
    
/*    int i, j, k, n, m, v;
    int type, low, up;
    Treap *leftpart,*midpart,*rightpart;
    Treap* rt=NULL;
    cin>>n>>m;
    for(i = 1; i <= n; i++)
    {
        cin>>v;
        insert(rt, i, v);
    }

    for(i = 1; i <= m; i++)
    {
        cin>>type>>low>>up;

        split(rt,leftpart,rightpart,low-1);
        split(rightpart,midpart,rightpart,up,low-1);

        if(type == 1)
        {
            merge(rt,midpart,leftpart);
            merge(rt,rt,rightpart);
        }
        else
        {
            merge(rt,leftpart,rightpart);
            merge(rt,rt,midpart);
        }
    }

        cout<<abs(find_kth(rt,1)-find_kth(rt,n))<<endl;
        for(int i = 0;i < n;i++){
            cout<<find_kth(rt,i+1)<<" ";
        }
        cout<<endl;
*/
    return 0;    
}
