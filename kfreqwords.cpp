#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class TrieNode{
public:
	vector<TrieNode*> nxt;
	int freq;
	int mhidx;
	bool isEnd;
	TrieNode(){
		freq = 0;
		mhidx = -1;
		isEnd = false;
		nxt = vector<TrieNode*>(26,NULL);
	}
};
class MinHeapNode{
public:	
	string s;
	TrieNode* root;
	MinHeapNode(TrieNode* rt,string ss){
		root = rt;
		s = ss;
	}
	//friend class MinHeap;
	//friend void displayMinHeap(MinHeap&);
};
class MinHeap{
public:	
	vector<MinHeapNode*> array;
	unsigned cap;
	MinHeap(int k){
		cap = k;
	}
	int parent(int idx){
		return (idx-1)/2;
	}
	int left(int idx){
		return 2*idx+1;
	}
	int right(int idx){
		return 2*idx+2;
	}
	void minHeapify(int idx){
		int smallest = idx;
		int l = left(idx);
		int r = right(idx);
		if(l < array.size()&&array[l]->root->freq < array[smallest]->root->freq){
			smallest = l;
		}
		if(r < array.size()&&array[r]->root->freq < array[smallest]->root->freq){
			smallest = r;
		}
		if(smallest != idx){
			array[idx]->root->mhidx = smallest;
			array[smallest]->root->mhidx = idx;
			swap(array[idx],array[smallest]);
			minHeapify(smallest);
		}
	}
	void insertKey(TrieNode* rt,string s){
		if(rt->mhidx!=-1){
			minHeapify(rt->mhidx);
		}else if(array.size() < cap){
			MinHeapNode* min_rt = new MinHeapNode(rt,s);
			array.push_back(min_rt);
			int i = array.size()-1;
			rt->mhidx = i;
			while(i!=0&&array[parent(i)]->root->freq > array[i]->root->freq){
				array[parent(i)]->root->mhidx = i;
				array[i]->root->mhidx = parent(i);
				swap(array[parent(i)],array[i]);
				i = parent(i);
			}
		}else{
			if(rt->freq > array[0]->root->freq){
				array[0]->root->mhidx = -1;
				delete array[0];
				array[0] = new MinHeapNode(rt,s);
				rt->mhidx = 0;
				minHeapify(0);
			}
		}
	}
	//friend void displayMinHeap(MinHeap& );
};
void insertTrieAndHeap(string wd,TrieNode *rt, MinHeap& minH){
	for(int i = 0;i < wd.length();i++){
		if(rt->nxt[tolower(wd[i])-'a'] == NULL){
			rt->nxt[tolower(wd[i])-'a'] = new TrieNode();
		}
		rt = rt->nxt[tolower(wd[i])-'a'];
	}
	rt->freq++;
	rt->isEnd = true;
	minH.insertKey(rt,wd);
}
void displayMinHeap(MinHeap& minH ){
	for(auto it:minH.array){
		cout<<it->s<<" "<<it->root->freq<<endl;
	}
}
void printKMostFreq(ifstream& fp, int k )
{
    // Create a Min Heap of Size k
    MinHeap minHeap( k );
    
    // Create an empty Trie
    TrieNode* root = new TrieNode();
 
    // A buffer to store one word at a time
    string buffer;
    // Read words one by one from file.  Insert the word in Trie and Min Heap
    while(fp>>buffer){
		insertTrieAndHeap(buffer, root, minHeap);
		
	}
	displayMinHeap( minHeap );
    // The Min Heap will have the k most frequent words, so print Min Heap nodes
    
}
int main()
{
    int k = 5;
    ifstream fp("file.txt",ios::in);
    if (!fp)
        printf ("File doesn't exist ");
    else
        printKMostFreq (fp, k);
    return 0;
}
