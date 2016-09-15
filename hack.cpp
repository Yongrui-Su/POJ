#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int helper(vector<vector<int>>& dp,int i,int j,int n){
    if(i < 0||i>= n||j<0||j>=n)return 1;
    if(dp[i][j]!=0)return dp[i][j];
    int d1 = helper(dp,i-2,j+1,n);
    int d2 = helper(dp,i-2,j-1,n);
    int d3 = helper(dp,i+1,j-2,n);
    int d4 = helper(dp,i-1,j-2,n);
    if(d1==1&&d2==1&&d3==1&&d4==1){
        dp[i][j] = -1;
    }
    if(d1==-1||d2==-1||d3==-1||d4==-1){
        dp[i][j] = 1;
    }
    return dp[i][j];
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n  = 15;
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(dp[i][j]==0){
                helper(dp,i,j,n);
            }
        }
    }
    /*int test;
    cin>>test;
    while(test-->0){
        int x;
        int y;
        cin>>x;
        cin>>y;
        if(dp[x][y]==1)cout<<1;
        else if(dp[x][y]==-1)cout<<2;
    }*/
    return 0;
}
