#include <iostream>

using namespace std;

struct node{
	node* nxt;
	int val;
	node(){
		nxt = NULL;
		val = 0;
	}
	node(int _v){
		val = _v;
		nxt = NULL;
	}
};

class sol{
	node* dummy;
	node* last;
	node* cur;
	
public:
	sol(){
		dummy = new node();
		dummy->nxt = new node(1);
		cur = dummy;
		last = cur;
	}
	~sol(){
		while(dummy){
			cur =dummy->nxt;
			delete dummy;
			dummy = cur;
		}
	}
	void solver(string s){
		int i = 2;
		while(i < s.length()+2){
			node* tmp = new node(i);
			if(s[i-2] == 'i'){
				cur->nxt->nxt = tmp;
				cur = cur->nxt;
				last = cur;
			}else{
				tmp->nxt = last->nxt;
				last->nxt = tmp;
				if(last==cur)cur=cur->nxt;
			}
			i++;
		}
	}
	void displace(){
		node* tmp = dummy->nxt;
		while(tmp){
			cout<<tmp->val<<" ";
			tmp = tmp->nxt;
		}
		cout<<endl;
	}
	
};

int main(){
	string s;
	while(cin>>s){
		sol ss;
		ss.solver(s);
		ss.displace();
	}
}
