#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN = 51;
struct BigInt;

BigInt &countConnectedGraphs(int n);
BigInt &countNonConnectedGraph(int n);
inline BigInt &countAllGraphs(int n);

struct BigInt{
	vector<char> v;
	BigInt(){
		*this = 0;
	}
	BigInt(int x){
		*this = x;
	}
	BigInt &operator=(int x){
		v.clear();
		do v.push_back(x%10);while(x/=10);
		return *this;
	}
	BigInt &operator=(const BigInt x){
		v.resize(x.v.size());
		memcpy(const_cast<char *>(v.data()),x.v.data(),x.v.size()*sizeof(char));
		return *this;
	}
};

ostream &operator<<(ostream &out,const BigInt &x){
	for(int i = x.v.size()-1;i >=0; i--)out<<(char)(x.v[i]+'0');
	return out;
}
BigInt operator+(const BigInt &a,const BigInt &b){
	BigInt result;
	result.v.clear();
	bool flg = false;
	for(int i = 0;i < (int) max(a.v.size(),b.v.size());i++){
		int tmp = 0;
		if(i < (int)a.v.size())tmp += a.v[i];
		if(i < (int)b.v.size())tmp += b.v[i];
		if(flg)tmp++;
		flg = false;
		if(tmp >= 10)tmp -= 10,flg = true;
		result.v.push_back(tmp);
	}
	if(flg)result.v.push_back(1);
	return result;
}
BigInt &operator+=(BigInt &a,const BigInt &b){
	a = a+b;
	return a;
}
BigInt operator-(const BigInt &a,const BigInt &b){
	BigInt res;
	res.v.clear();
	bool flg = false;
	for(int i = 0;i < a.v.size();i++){
		int tmp = a.v[i];
		if(i < b.v.size())tmp -= b.v[i];
		if(flg)tmp--,flg = false;
		if(tmp < 0)tmp += 10,flg = true;
		res.v.push_back(tmp);
	}
	int sz = res.v.size();
	while(sz >1&&res.v[sz-1]==0)sz--;
	res.v.resize(sz);
	return res;
}

BigInt operator*(const BigInt &a,const BigInt &b){
	BigInt res;
	res.v.resize(a.v.size()+b.v.size());
	for(int i = 0;i < a.v.size();i++)
	for(int j = 0;j < b.v.size();j++){
		res.v[i+j] += a.v[i]*b.v[j];
		res.v[i+j+1] += res.v[i+j]/10;
		res.v[i+j] %= 10;
	}
	int size = res.v.size();
	while(size>1&&res.v[size-1]==0)size--;
	res.v.resize(size);
	return res;
}

BigInt combo[MAXN][MAXN];
void combination(){
	for(int i = 1; i < MAXN;i++){
		combo[i][i] = 1,combo[i][0] = 1;
		for(int j = 1;j < i;j++){
			combo[i][j] = combo[i-1][j] + combo[i-1][j-1];
		}
	}
}
inline BigInt& C(int n,int k){
	return combo[n][k];
}

BigInt &countConnectedGraphs(int n){
	static bool calced[MAXN];
	static BigInt mem[MAXN];
	BigInt &ans = mem[n];
	if(calced[n])return ans;
	calced[n] = true;
	ans = countAllGraphs(n)-countNonConnectedGraph(n);
	return ans;
}

BigInt &countAllGraphs(int n){
	static bool calced[MAXN];
	static BigInt mem[MAXN];
	BigInt &ans = mem[n];
	if(calced[n])return ans;
	calced[n] = true;
	BigInt x = 2;
	int t = n*(n-1)/2;
	for(ans = 1;t;t>>=1,x = x*x){
		if(t&1)ans = ans*x;
	}
	return ans;
}

BigInt &countNonConnectedGraph(int n){
	static bool calced[MAXN];
	static BigInt mem[MAXN];
	BigInt &ans = mem[n];
	if(calced[n])return ans;
	calced[n] = true;
	ans = 0;
	for(int k = 1;k <= n-1;k++){
		ans += C(n-1,k-1)*countConnectedGraphs(k)*countAllGraphs(n-k);
	}
	return ans;
}
int main(){
	combination();
	int n;
	while(true){
		cin>>n;
		if(n==0)break;
		cout<<countConnectedGraphs(n)<<endl;
	}
}
