#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


unordered_map<string,bool> ret;

string hasher(vector<int> v){
	sort(v.begin(),v.end());
	string res ="#";
	for(auto& d:v)res+=to_string(d)+"#";
	return res;
}
void displace(const vector<int>& cur){
	for(auto& d:cur)cout<<d<<" ";
	cout<<endl;
}
bool solver(vector<int> cur){
	string s = hasher(cur);
	if(ret.count(s)){
		//cout<<s<<" "<<(ret[s]?"True":"False")<<endl;
		return ret[s];
	}
	bool &ans = ret[s];
	vector<int> tmp;
	for(int i = 0;i < cur.size();i++){
		for(int j = 0;j+2<=cur[i];j++){
			int a = j;
			int b = cur[i] - (j+2);
			vector<int> nxt = tmp;
			if(a >=2){
				nxt.push_back(a);
			}
			if(b >=2){
				nxt.push_back(b);
			}
			nxt.insert(nxt.end(),cur.begin()+i+1,cur.end());
			//displace(nxt);
			if(solver(nxt)==false){
				ans = true;
				return true;
			}
		}
		tmp.push_back(cur[i]);
	}
	ans = false;
	return ans;
}

int main(){
	string s;
	ret["#"] = false;
	cin>>s;
	vector<int> cur;
	int i = 0;
	while(i < s.length()-1){
		if(i < s.length()-1&&s[i]=='+'&&s[i+1]=='+'){
			int cnt = 1;
			while(i < s.length()-1&&s[i]=='+'&&s[i+1]=='+'){
				cnt++;
				i++;
			}
			cur.push_back(cnt);
		}
		i++;
	}
	//displace(cur);
	if(solver(cur))cout<<"True"<<endl;
	else cout<<"False"<<endl;
}
