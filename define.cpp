#include <iostream>
#include <stdlib.h>
using namespace std;
#define language 500
#if language < 400
#undef language
#else
#define language 850
#ifdef language
	printf("%d",language);
#endif
#endif


int main(){
	cout<<1<<endl;
}
