#include <iostream>
using namespace std;

void heapify(int *a,int idx,int sz){
	int largest = idx;
	int left = 2*idx+1;
	int right =2*idx+2;
	if(left < sz&&a[left] > a[largest])largest = left;
	if(right < sz&&a[right] > a[largest])largest = right;
	if(largest != idx){
		swap(a[largest],a[idx]);
		heapify(a,largest,sz);
	}
}

void heapsort(int *a,int n){
	for(int i = (n-1)/2;i >=0;i--)heapify(a,i,n);
	for(int i = n-1;i >0;i--){
		swap(a[0],a[i]);
		heapify(a,0,i);
	}
}


int main(){
	int a[] = {9,4,3,1,2,12,7,8,5,9,1};
	heapsort(a,sizeof(a)/sizeof(int));
	for(int i =0; i < sizeof(a)/sizeof(int);i++)cout<<a[i]<<" ";
	cout<<endl;
}
