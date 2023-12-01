#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
const int NODE_MAX = 5000;

struct Node{
    Node(int a, Node* x) : val(a), next(x){};
    Node(int a){
        val = a;
        next = nullptr;
    }
    int val;
    Node* next;

};

class LinkedList {
    vector<Node*> nodeArr;
    int nodeCnt;

public:
    Node* head;
    Node* tail;
    LinkedList() : head(nullptr), tail(nullptr), nodeCnt(0) {
        nodeArr.resize(NODE_MAX, nullptr);
    }
    void addNode(Node* node){
        if (head == nullptr)
        {
            head = node;
            tail = node;
        } 
        else
        {
            tail->next = node;  
            tail = node; 
        }
    }

};



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle3.txt", ios_base::in);    
    
    int N;
    cin >> N;

    // int* ptr_a = &a;
    // 포인터로써 선언함

    cout << (Node(5).next == nullptr) << '\n';
    Node a = Node(5);
    Node* ptr_a = &a;

    Node b = Node(5, &a);
    LinkedList list = LinkedList();
    list.addNode(&a);
    Node c = Node(3);
    list.addNode(&c);
    cout << list.head->val << ' ' << list.head->next->val;




}