#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
};

struct LinkedList{
    ListNode* root;
    ListNode* end;
    void append(ListNode* node){
        if (this->end == nullptr){
            this->root = node;
            this->end = node;
        } else {
            this->end->next = node;
            this->end = node;
        }
    }
    void Insert(int idx, int ct){
        if (idx == 0){
            
        }
    }

    void Delete(int idx, int ct){

    }
};

int main(){
    for (int i = 0; i < 10; i++){
        int N;
        cin >> N;
        ListNode root(5);




    }
}