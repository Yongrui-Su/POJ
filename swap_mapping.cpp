#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sol(vector<string>& arr,vector<int>& mp){
	int i = 0;
	while(i < arr.size()){
		if(mp[i]!=i){
			int nxt = mp[i];
			while(nxt<i)nxt = mp[nxt];
			swap(arr[nxt],arr[i]);
			mp[i] = nxt;
		}
		i++;
	}
}

int main(){
	vector<string> array;
	array.push_back("a");
	array.push_back("ana");
	array.push_back("anana");
	array.push_back("banana");
	array.push_back("na");
	array.push_back("nana");
	vector<int> idx;
	idx.push_back(5);
	idx.push_back(3);
	idx.push_back(1);
	idx.push_back(0);
	idx.push_back(4);
	idx.push_back(2);
	for(int i = 0;i < array.size();i++)cout<<array[i]<<" ";
	cout<<endl;
	sol(array,idx);
	for(int i = 0;i < array.size();i++)cout<<array[i]<<" ";
	cout<<endl;
}
