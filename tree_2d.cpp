#include <utility>
#include <vector>
#include <unordered_set>
#include <queue>
#include <initializer_list>
#include <iostream>
#include <set>
using namespace std;
class treenode{
public:
    pair<int,int> topleft;
    pair<int,int> bottomright;
    vector<treenode*> neighbors;
    int val;
    treenode(int v,pair<int,int> t,pair<int,int> b){
        topleft = t;
        bottomright = b;
        val = v;
        neighbors = vector<treenode*>(4,NULL);
    }
};

class SegTree{
    bool good_p(pair<int,int> t,pair<int,int> b){
        if(t.first <= b.first&&t.second <=b.second)return true;
        else return false;
    }
    vector<vector<int> > num;
public:
    SegTree(){};
    SegTree(int m,int n){
        num = vector<vector<int> >(m,vector<int>(n,0));
    }
    treenode* build(pair<int,int> t,pair<int,int> b){
        if(!good_p(t,b))return NULL;
        treenode* rt = new treenode(0,t,b);
        if(t==b)return rt;
        pair<int,int> mid({(t.first+b.first)/2,(t.second+b.second)/2});
        rt->neighbors[0] = build(t,{mid.first,mid.second});
        rt->neighbors[1] = build({mid.first+1,t.second},{b.first,mid.second});
        rt->neighbors[2] = build({t.first,mid.second+1},{mid.first,b.second});
        rt->neighbors[3] = build({mid.first+1,mid.second+1},{b.first,b.second});
        return rt;
    }
    void update_nxt(treenode* rt,int x,int y,int diff){
        if(!rt||x<rt->topleft.first||y<rt->topleft.second||x>rt->bottomright.first||y>rt->bottomright.second)return;
        rt->val += diff;
        for(int i = 0;i < 4;i++){
            update_nxt(rt->neighbors[i],x,y,diff);
        }
    }    
    void update(treenode* rt,int x,int y,int val){
        if(!rt||x<rt->topleft.first||y<rt->topleft.second||x>rt->bottomright.first||y>rt->bottomright.second)return;
        int diff = val-num[x][y];
        update_nxt(rt,x,y,diff);
        num[x][y] = val;
    }
    int query_sum(treenode *rt,pair<int,int> t,pair<int,int> b){
        if(!rt||!good_p(t,b))return 0;
        if(t.first > rt->bottomright.first||t.second >rt->bottomright.second||b.first<rt->topleft.first||b.second < rt->topleft.second)return 0;
        if(t.first <=rt->topleft.first&&t.second<=rt->topleft.second&&b.first>=rt->bottomright.first&&b.second>=rt->bottomright.second)return rt->val;
        int res = 0;
        for(int i=0;i < 4;i++){
            res += query_sum(rt->neighbors[i],t,b);
        }
        return res;
    }
};
class NumMatrix {
    SegTree tree;
    treenode* rt;
public:
    NumMatrix(vector<vector<int>> &matrix) {
		if(matrix.size()==0||matrix[0].size()==0)return;
        tree = SegTree(matrix.size(),matrix[0].size());
        rt = tree.build({0,0},{matrix.size()-1,matrix[0].size()-1});
        for(int i = 0;i < matrix.size();i++)
        for(int j = 0;j < matrix[0].size();j++){
            tree.update(rt,i,j,matrix[i][j]);
        }
    }

    void update(int row, int col, int val) {
        tree.update(rt,row,col,val);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return tree.query_sum(rt,{row1,col1},{row2,col2});
    }
};

int main(){
	vector<vector<int>> mat;
	NumMatrix nm(mat);
}
