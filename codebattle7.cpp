#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

const int MaxNum = 100;
struct Node{
    char val;
    Node* left;
    Node* right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {};
};


class Graph{
    int NodeNum;
    vector<Node*> NodeContainer;
public:
    Node* root;
    Graph() : root(nullptr), NodeNum(0) {
        NodeContainer.resize(MaxNum + 1, nullptr);
    }
    void Insert(Node* node){
        NodeContainer[++NodeNum] = node;

        if (NodeNum != 1){

            Node* parent = NodeContainer[NodeNum / 2];
            if (NodeNum % 2){
                parent->right = node;
            } else {
                parent->left = node;
            }
        }
        else {root = node;}
    }
    void InOrderRead(Node* node){
        if (node == nullptr) return;
        if (node->left != nullptr){
            InOrderRead(node->left);
        }
        cout << node->val;
        if (node->right != nullptr){
            InOrderRead(node->right);
        }
        }
};


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle7.txt", ios_base::in);    
    int tc = 10;

    for (int t = 0; t < tc; t++){
        int N;
        Graph graph = Graph();
        cin >> N;
        cin.ignore();
        for (int i = 0; i < N; i++){

            string s;
            getline(cin ,s);
            bool flag = false;

            for (const auto& c : s){
                if (flag){
                    graph.Insert(new Node(c));
                    break;
                }
                if (c == ' ') flag = true;
            }
        }
        


        cout << '#' << t + 1 << ' ' ;
        graph.InOrderRead(graph.root);
        cout << '\n';
    }
}