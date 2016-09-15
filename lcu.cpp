#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <typeinfo>
#include <unordered_map>
using namespace std;

class node{
    public:
    int key;
    int val;
    node* next;
    node* prev;
    node(){
        next = NULL;
        prev = NULL;
    };
    node(int k,int v){
        key = k;
        val = v;
        next = NULL;
        prev = NULL;
    }
};
class LRUCache{
    unordered_map<int,node*> kk;
    node* head;
    node* last;
    int sz;
    int cap;
    void rm(){
        sz--;
        kk.erase(last->key);
        last = last->prev;
        delete last->next;
        last->next = NULL;
    }
public:
    
    LRUCache(int capacity) {
        cap = capacity;
        sz = 0;
        head = new node();
        last = head;
    }

    int get(int key) {
        if(kk.count(key)==0)return -1;
        node* tmp = kk[key];
        if(tmp == head->next)return tmp->val;
        tmp->prev->next = tmp->next;
        if(tmp->next)tmp->next->prev = tmp->prev;
        if(tmp==last)last = tmp->prev;
        head->next->prev = tmp;
        tmp->next = head->next;
        tmp->prev = head;
        head->next = tmp;
        return tmp->val;
    }
    
    void set(int key, int value) {
        if(kk.count(key)){
            kk[key]->val = value;
            if(kk[key]==head->next)return;
            kk[key]->prev->next = kk[key]->next;
            if(kk[key]->next)kk[key]->next->prev = kk[key]->prev;
            head->next->prev = kk[key];
            kk[key]->next = head->next;
            kk[key]->prev = head;
            head->next = kk[key];
            cout<<head->next->key<<endl;
            return;
        }
        if(sz>=cap)rm();
        node* tmp = new node(key,value);
        sz++;
        tmp->next = head->next;
        if(head->next)head->next->prev = tmp;
        head->next = tmp;
        tmp->prev = head;
        if(last==head)last = head->next;
        kk[key] = tmp;
    }
};


int main(){
	LRUCache lrc(2);
	lrc.set(2,1);
	lrc.set(1,1);
	lrc.get(2);
	lrc.set(4,1);
	lrc.get(1);
	lrc.get(2);
	
}
