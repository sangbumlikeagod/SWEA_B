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
        nodeArr = {};
    }
    void addArr(Node* node){
        // cout << node->val << '\n';
        if (!nodeArr.empty()) {nodeArr.back()->next = node;}
        nodeArr.push_back(node);
        // cout << nodeArr.size();
    };
    void cleanArr() {};
    void insertNode(int x, int y){
        if (head == nullptr)
        {
            head = nodeArr[0];
            tail = nodeArr[y - 1];
        } 
        else 
        {
            if (x == 0)
            {
                nodeArr[y - 1]->next = head;
                head = nodeArr[0];
            }
            else
            {
                Node* tmphead = head;
                for (int i = 0; i < x - 1; i++){
                    tmphead = tmphead->next;
                }
                Node* tmpheadNext = tmphead->next;
                tmphead->next = nodeArr[0];
                nodeArr[y - 1]->next = tmpheadNext;
                if (x == nodeCnt) {tail = nodeArr[y - 1];}
            }
        }
        nodeArr = {};
        nodeCnt += y;
    };
    void addNode(int y) {
        // cout << nodeArr[0]->val;
        if (head == nullptr)
        {
            head = nodeArr[0];
            tail = nodeArr[y - 1];
        } 
        else 
        {
            tail->next = nodeArr[0];
        }
        // cout << "head" << head;
        nodeArr = {};
        nodeCnt += y;
        // cout << nodeArr.empty() << '\n';

    };
    void deleteNode(int x, int y) {
        if (x > nodeCnt){
            return;
        }
        Node* tmphead = head;
        for (int i = 0; i < x; i++){
            tmphead = tmphead->next;
        }

        if ((x + y) >= nodeCnt)
        {
            tmphead->next = nullptr;
            tail = tmphead;
        }
        else 
        {
            Node* tmpNext = tmphead;
            for (int i = 0; i < y; i++)
            {
            tmpNext = tmpNext->next;
            }
            tmphead->next = tmpNext->next;
            if (x == 0)
            {
                head = tmphead->next;
            }
        }
        nodeCnt -= y;
    };
};



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle3.txt", ios_base::in);    
    
    int tc = 10;

    // cin >> tc;
    for (int t = 0; t < tc; t++){
        int numOfCommand;
        int N;  
        cin >> N;



        LinkedList list = LinkedList();
        for (int p = 0; p < N; p++)
        {
            int val;
            cin >> val;
            list.addArr(new Node(val)); 
        }
        list.addNode(N);
        cin >> numOfCommand;


        for (int command = 0; command < numOfCommand; command++){
            char com;
            cin >> com;
            if (com == 'I')
            {

                int x, y;
                cin >> x >> y;
                for (int p = 0; p < y; p++)
                {
                    int val;
                    cin >> val;
                    list.addArr(new Node(val)); 
                }
                list.insertNode(x, y);

            } 
            else if (com == 'D')
            {
                int x, y;
                cin >> x >> y;
                list.deleteNode(x, y);
            }
            else if (com == 'A')
            {
                int y;
                cin >> y;
                for (int p = 0; p < y; p++)
                {
                    int val;
                    cin >> val;
                    list.addArr(new Node(val)); 
                }
                list.addNode(y);
            }
        }
        cout << '#' << t + 1 << ' ';
        for (int i = 0; i < 10; i++)
        {
            cout << list.head->val << ' ';
            list.head = list.head->next;
        }
        cout << '\n';
        }
    // int* ptr_a = &a;
    // 포인터로써 선언함
    // list.addArr(&a);
    // list.addArr(&b);
    // list.addNode(2);
}


