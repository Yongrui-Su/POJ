#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int get_point(vector<int>& arr,int left,int right){
    if(left>=right)return 0;
    if((right-left+1)%2==1)return 0;
    vector<int> nxt(arr.size(),0);
    int i = left;
    int j = right;
    int cnt = right;
    int ls = 0;
    int rs = 0;
    while(cnt>=left){
        if(ls < rs){
            ls += arr[i];
            nxt[i] = arr[cnt];
            i++;
        }else{
            ls += arr[j];
            nxt[j] = arr[cnt];
            j--;
        }
        cnt--;
    }
    if(ls != rs){
        return 0;
    }else{
        return 1+max(get_point(arr,left,i-1),get_point(arr,j+1,right));
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
    int test;
    cin>>test;
    cout<<test<<endl;
    while(test > 0){
        int n;
        cin>>n;
        vector<int> arr;
        for(int i =0;i < n;i++){
            int a;
            cin>>a;
            arr.push_back(a);
            cout<<a<<" ";
        }
        cout<<endl;
        int res = get_point(arr,0,n-1);
        printf("%d\n",res);
        test--;
    }
}
