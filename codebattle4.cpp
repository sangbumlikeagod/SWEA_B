#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int i_val): val(i_val), next(nullptr){};
};

class LinkedList{
    Node* head;
    Node* tail;
    int NodeNum;

public:
    void pushNode(Node* node){
        if (head == nullptr) 
        {
            head = node;
        } 
        else
        {
            tail->next = node;
        }
        tail = node;
        NodeNum++;
    }
    void Insert(int index, int value){
        if (index == 0) 
        {
            Node* tmpNode = new Node(value);
            tmpNode->next = head;
            head = tmpNode;
        }
        else
        {
            Node* tmpHead = head;
            for (int i = 0; i < index - 1; i++)
            {
                tmpHead = tmpHead->next;
            }
            Node* tmpNode = new Node(value);
            tmpNode->next = tmpHead->next;
            tmpHead->next = tmpNode;
        }
        NodeNum++;
    }
    void Delete(int index){
            Node* tmpHead = head;
            for (int i = 0; i < index - 1; i++)
            {
                tmpHead = tmpHead->next;
            }
            tmpHead->next = tmpHead->next->next;
            NodeNum--;
    }
    void Change(int index, int value){
        Node* tmpHead = head;
        for (int i = 0; i < index; i++)
        {
            tmpHead = tmpHead->next;
        }
        tmpHead->val = value;
    }
    int getNum(){
        return NodeNum;
    }
    int getNode(int index){
        Node* tmpHead = head;
        int ans = 0;
        int i = 0;
        while (i < index)
        {
            tmpHead = tmpHead->next;
            i++;
        }
        ans = tmpHead->val;
        // 이게 무슨 현상일까
        return ans;
    }
    void clean(){
        head = nullptr;
        tail = nullptr;
        NodeNum = 0;
    }

    LinkedList() : head(nullptr), tail(nullptr), NodeNum(0) {}

};


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle4.txt", ios_base::in);    
    int tc;
    cin >> tc;

    for (int t = 0; t < tc; t++){
        LinkedList list = LinkedList();
        int N, M, L;
        cin >> N >> M >> L;
        for (int i = 0; i < N; i++)
        {
            int value;
            cin >> value;
            list.pushNode(new Node(value));
        }
        for (int j = 0; j < M; j++)
        {
            char command;
            cin >> command;

            if (command == 'I')
            {
                int index = 0;
                int value = 0;
                cin >> index >> value;
                list.Insert(index, value);

            }
            else if (command == 'D')
            {
                int index = 0;
                cin >> index;
                list.Delete(index);
            }
            else if (command == 'C')
            {
                int index = 0;
                int value = 0;
                cin >> index >> value;
                list.Change(index, value);
            }
        }

        if (list.getNum() < L)
        {  cout << '#' << t + 1 << ' ' << -1; }
        else 
        {   
            int ans = list.getNode(L);
             cout << '#' << t + 1 << ' ' << ans; 
        }
        cout << '\n';
    }
}
