#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;



struct Node {
    int val;
    Node* next;
    Node(int val) : val(val), next(nullptr) {}
};


class LinkedList {
    Node* head;
    Node* tail;
    int NodeCount;

public:
    LinkedList(): NodeCount(2){
        // Node headstart = Node(0);
        head = new Node(0);

        // Node headend = Node(1000000000);
        tail = new Node(1000000000);

        head->next = tail;

    }
    Node* findNext(int val) {
        Node* tmp = head;
        while (tmp->next != nullptr & tmp->next->val < val){
            cout << tmp->val << '\t';   
            tmp = tmp->next;
        }
        // cout << (*tmp).val;   
        cout << '\n';
        return tmp; 
    }
    void setHead(Node* head){
        head = head;
        tail = nullptr;
    }
    Node* getHead(){
        return head;
    }
};
vector<LinkedList*> LadderGame;
vector<set<Node*>*> Xaxis;
map<int, Node *> nodeMap[N + 1];
void init(){
    Xaxis.resize(101, nullptr);
    for (int i = 1; i <= 101; i++){
        Xaxis[i] = new set<Node*, Node*->val>;
    }
    LadderGame.resize(101, nullptr);
    for (int i = 1; i <= 101; i++){
        LadderGame[i] = new LinkedList();


    }
}

void add(int mX, int mY){

    Node* forX = new Node(mY);
    Xaxis[mX]->insert(forX);
    Node* forY = new Node(mY);
    Xaxis[mX + 1]->insert(forY);



    // 먼저 그 특정 요소를 구함 
    Node* X = Xaxis[mX]->find(forX);
    Node* XaddOne = Xaxis[mX + 1]->find(forY); 
    


    Node* NewX = new Node(mY, mX); 
    Node* NewXaddOne = new Node(mY, mX + 1); 
    NewX->next = XaddOne->next; 
    XaddOne->next = NewX; 
    NewXaddOne->next = X->next; 
    X->next = NewXaddOne; 

}
// 선을 긋는게 어려운게 아니라 이 지점 위에있는 모든 애들한테 바꾸어줘야하네 
// 그 지점을 찾는게 중요

void remove(int mX, int mY){
    Node* X = LadderGame[mX]->findNext(mY);
    Node* XaddOne = LadderGame[mX + 1]->findNext(mY);

}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    // ifstream cin("codebattle29.txt", ios_base::in);    

    init();
    add(5, 7);
    add(9, 100000);
    cout << (LadderGame[5]->getHead()->next->val) << '\n';
    cout << (LadderGame[9]->getHead()->next->val);


}