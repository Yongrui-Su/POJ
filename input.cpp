#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main(){
	vector<vector<int> > data;
	string s;
	while(getline(cin,s,'\n')){
		vector<int> tmp;
		stringstream ss(s);
		int t;
		while(ss>>t){
			tmp.push_back(t);
		}
		if(!tmp.empty())data.push_back(tmp);
	}
	for(int i = 0;i < data.size();i++){
		for(int j = 0;j < data[i].size();j++)cout<<data[i][j]<<" ";
		cout<<endl;
	}
}
