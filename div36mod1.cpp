#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

bool div36mod1(string s){
	int pre = 0;
	unordered_set<int> remains;
	for(int i = s.length()-1;i >=0 ;i--){
		if(s[i] <'0'||s[i] >'9'){
			remains.clear();
			pre = 0;
			continue;
		}
		int n = s[i]-'0';
		if(n==1)return true;
		if((n*10+pre)%36==1)return true;
		unordered_set<int> temp;
		temp.insert(n);
		temp.insert((10*n+pre)%36);
		pre = n;
		for(auto r:remains){
			int t = (n*28+r)%36;
			if(t==1)return true;
			temp.insert(t);
		}
		remains = temp;
	}
	return false;
}


int main(){
	string s("agdaadfff7424");
	if(div36mod1(s))cout<<"True"<<endl;
	else cout<<"False"<<endl;
}
