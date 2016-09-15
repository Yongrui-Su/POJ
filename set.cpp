#include <utility>
#include <vector>
#include <unordered_set>
#include <queue>
#include <initializer_list>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std; 
bool compare(const pair<int,int>& a,const pair<int,int>& b){
    if(a.first!=b.first)return a.first < b.first;
    else return a.second > b.second;
}
class Solution {
    class Compare{
    public:
        bool operator()(const pair<int,int>& a,const pair<int,int>& b){
            if(a.first!=b.first)return a.first < b.first;
            else return a.second > b.second;
        }
    };
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        if(envelopes.empty())return 0;
        set<pair<int,int>,Compare> st;
        sort(envelopes.begin(),envelopes.end(),compare);
        vector<int> dp;
        for(int i = 0;i < envelopes.size();i++){
            int k = lower_bound(dp.begin(),dp.end(),envelopes[i].second)-dp.begin();
            if(k==dp.size())dp.push_back(envelopes[i].second);
            else dp[k] = envelopes[i].second;
        }
        return dp.size();
    }
};

int main(){
	return 1;
}
