#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <typeinfo>
using namespace std;
class TrieNode {
public:
    char val;
    bool iskey;
    vector<TrieNode*> ptr;
    // Initialize your data structure here.
    TrieNode(char v):val(v){
		iskey = false;
    }
    TrieNode(){
		iskey = false;
    }
};

class Trie {
private:
    void insert_help(TrieNode* rt,string word){
        if(word.empty())return;
        for(size_t i = 0;i<rt->ptr.size();i++){
			TrieNode *child = rt->ptr[i];
            if(child->val==word[0]){
                if(word.size()>1)insert_help(child,word.substr(1));
                else child->iskey = true;
                return;
            }
        }
        TrieNode* c = new TrieNode(word[0]);
        if(word.size()>1)insert_help(c,word.substr(1));
        else c->iskey = true;
        rt->ptr.push_back(c);
        return;
    }
    bool search_help(TrieNode* rt,string word){
        if(rt== NULL&&!word.empty())return false;
        for(size_t i = 0;i<rt->ptr.size();i++){
			TrieNode *child = rt->ptr[i];
            if(child->val==word[0]){
                if(word.size()==1)return true;
                else return search_help(child,word.substr(1));
            }
        }
        return false;
    }
    bool word_search_help(TrieNode* rt,string word){
        if(rt== NULL&&!word.empty())return false;
        for(size_t i = 0;i<rt->ptr.size();i++){
			TrieNode *child = rt->ptr[i];
            if(child->val==word[0]){
                if(word.size()== 1){
					return child->iskey;
                }else{
                    return word_search_help(child,word.substr(1));
                }
            }
        }
        return false;
    }
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        insert_help(root,word);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        return word_search_help(root,word);
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        return search_help(root,prefix);
    }

private:
    TrieNode* root;
};
class Person{
	
public:
	string *namePtr;
	Person(){namePtr = new string;}
	void setName(char *s){*namePtr = s;}
};
class object1{
	virtual ~object1(){}
};
class object2{
	virtual ~object2(){}
};
int main(){
	/*Trie sol;
	sol.insert("abc");
	if(sol.search("abc"))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(sol.search("ab"))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	sol.insert("ab");
	if(sol.search("abc"))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	sol.insert("ab");
	if(sol.search("ab"))cout<<"true"<<endl;
	else cout<<"false"<<endl;*/
	int a=1;
	int b=2;
	int &c = a;
	cout<<c<<endl;
	c = b;
	cout<<c<<endl;

	return 0;
}
