#include <vector>
#include <iostream>
using namespace std;

int partition(int* arr,int l,int r){
	if(l > r)return 0;
	if(l == r)return 1;
	int init = l;
	int pivot = r;
	r--;
	while(l <= r){
		while(l<=r&&arr[l] <= arr[pivot])l++;
		while(l<=r&&arr[r] > arr[pivot])r--;
		if(l < r)swap(arr[l],arr[r]);
	}
	if(l < pivot)swap(arr[l],arr[pivot]);
	return l-init+1;
}

int kth_ele(int* arr1,int l1,int r1,int* arr2,int l2,int r2,int k){
	if(k<=0)return 0;
	if(l1>r1&&l2>r2)return 0;
	int p1 = partition(arr1,l1,r1);
	int p2 = partition(arr2,l2,r2);
	//cout<<p1<<endl;
	//for(int i = l1;i <= r1;i++)cout<<arr1[i]<<" ";
	//cout<<endl;
	//cout<<p2<<endl;
	//for(int i = l2;i <= r2;i++)cout<<arr2[i]<<" ";
	//cout<<endl;
	if(p1==0&&p2==k)return arr2[l2+p2-1];
	if(p2==0&&p1==k)return arr1[l1+p1-1];
	if(p1+p2 > k){
		if(p1==0||arr2[l2+p2-1] >arr1[l1+p1-1])return kth_ele(arr1,l1,r1,arr2,l2,l2+p2-2,k);
		if(p2==0||arr1[l1+p1-1] >= arr2[l2+p2-1])return kth_ele(arr1,l1,l1+p1-2,arr2,l2,r2,k);
	}else{
		if(p2==0||(p1!=0&&arr2[l2+p2-1] > arr1[l1+p1-1]))return kth_ele(arr1,l1+p1,r1,arr2,l2,r2,k-p1);
		if(p1==0||(p2!=0&&arr1[l1+p1-1] >= arr2[l2+p2-1]))return kth_ele(arr1,l1,r1,arr2,l2+p2,r2,k-p2);
	}
}

int main(){
	int k;
	while(cin>>k&&k){
		int a[] = {3,1,7,8,6};
		int b[] = {4,9,5,2};		
		cout<<kth_ele(a,0,sizeof(a)/sizeof(int)-1,b,0,sizeof(b)/sizeof(int)-1,k)<<endl;
	}
}
