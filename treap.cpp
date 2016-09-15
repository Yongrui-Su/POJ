#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class node{
public:
    int val;
    int cnt;
    int prior;
    node *l,*r;
    node(int v):val(v),cnt(1),l(NULL),r(NULL),prior(rand()){};
};

class treap{
 public:
    int sz(node* rt){
        return rt?rt->cnt:0;
    }
    void upd_sz(node* rt){
        if(rt)rt->cnt = 1+sz(rt->l)+sz(rt->r);
    }
    /*void split(node* rt,node* &l,node* &r,int pos,int add = 0){
        if(!rt){
            l = NULL;
            r = NULL;
            return;
        }
        int cur_pos = add+sz(rt->l) + 1;
        if(cur_pos <=pos){
            split(rt->r,rt->r,r,pos,cur_pos);
            l = rt;
        }else{
            split(rt->l,l,rt->l,pos,add);
            r = rt;
        }
        upd_sz(rt);
    }*/
    void split(node *t, node *&l, node *&r, int pos, int add = 0)
    {
        if(!t) return void(l = r = NULL);
        int cur_pos = add + sz(t->l) + 1;
        if(cur_pos <= pos) split(t->r, t->r, r, pos, cur_pos), l = t;
        else split(t->l, l ,t->l, pos, add), r = t;
        upd_sz(t);
    }
    void merge(node *&t, node *l, node *r)
    {
        if(!l || !r) t = l? l:r;
        else if(l->prior > r->prior) {
            merge(l->r, l->r, r); t = l;
        }else {
            merge(r->l, l, r->l);t = r;
        }
        upd_sz(t);
    }    
    /*void merge(node* &t,node* l,node* r){
        if(!l||!r){
            t = l?l:r;
            return;
        }
        if(l->prior > r->prior){
            merge(l->r,l->r,r);
            t = l;
        }else{
            merge(r->l,l,r->l);
            t = r;
        }
        upd_sz(t);
    }*/
    /*void insert(node* &t,int pos,int val){
        node* it = new node(val);
        node *l,*r;
        split(t,l,r,pos-1);
        merge(t,l,it);
        merge(t,t,r);
        upd_sz(t);
    }*/
    void insert(node *&t, int pos, int val)
    {
        node *l, *r, *cur = new node(val);
        split(t, l, r, pos-1);
        merge(t, l, cur);
        //merge(t, t, r);
    }    
    void erase(node* &t,int pos){
        node* l,*r;
        node* cur;
        split(t,l,r,pos-1);
        split(r,cur,r,1);
        delete cur;
        merge(t,l,r);
        upd_sz(t);
    }
    int find_kth(node* t,int k,int add = 0){
        int cur_pos = add + sz(t->l) + 1;
        if(cur_pos == k)return t->val;
        else if(cur_pos < k){
            return find_kth(t->r,k,cur_pos);
        }else{
            return find_kth(t->l,k);
        }
    }
};
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,m;
    cin>>n>>m;
    treap tr;
    node* rt=NULL;
    int type,low,up;
    node *leftnode,*midnode,*rightnode;
    for(int i = 0;i < n;i++){
        int a;
        cin>>a;
        tr.insert(rt,i+1,a);
    }
    for(int i = 0;i < m;i++){
        cin>>type>>low>>up;
        tr.split(rt,leftnode,midnode,low-1);
        tr.split(rt,midnode,rightnode,up,low-1);
        if(type==1){
            tr.merge(rt,midnode,leftnode);
            tr.merge(rt,rt,rightnode);
        }else{
            tr.merge(rt,leftnode,rightnode);
            tr.merge(rt,rt,midnode);
        }
        cout<<abs(tr.find_kth(rt,1)-tr.find_kth(rt,n))<<endl;
        for(int i = 0;i < n;i++){
            cout<<tr.find_kth(rt,i+1)<<" ";
        }
        cout<<endl;
    }
    return 0;
}
