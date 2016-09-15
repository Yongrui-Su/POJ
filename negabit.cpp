#include <iostream>
#include <vector>
using namespace std;

int main(){
	int a = -5;
	int i;
	for(i = 31;i >= 0;i--){
		int t = ((a>>i)&1);
		cout<<t<<" ";
	}
	cout<<endl;
	return 0;
}
