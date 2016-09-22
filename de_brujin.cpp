#include <iostream>
#include <vector>
#include <string>
using namespace std;



void de_brujin(vector<int>& a,vector<int>& res,int k,int n,int t,int p){
  if(t>n){
    if(n%p==0)res.insert(res.end(),a.begin()+1,a.begin()+1+p);
  }else{
    a[t] = a[t-p];
    de_brujin(a,res,k,n,t+1,p);
    for(int j = a[t-p]+1;j <k;j++){
      a[t] = j;
      de_brujin(a,res,k,n,t+1,t);
    }
  }
}

int main(){
	string s = "01234";
	int n=3;
	vector<int> a(s.length()*n,0);
	vector<int> res;
	de_brujin(a,res,s.length(),n,1,1);
	string ret = "";
	for(auto& n:res)ret+=s[n];
	cout<<ret<<endl;
}
