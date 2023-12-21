#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int idx;
    int parent;
    vector<Node*> vec;
    Node(int num) : idx(num), parent(0){
        vec = {};
    }
};
vector<Node*> nodeVec;

int matrix[10001][10001] = {0, };

int findParent(Node* now, Node* next){
    if (now->idx == next->idx) return 0;
    if (matrix[now->idx][next->idx]) return matrix[now->idx][next->idx];
    else {
        if (now->idx < next->idx){
            matrix[now->idx][next->idx] = findParent(now, nodeVec[next->parent - 1]) + 1; 
        }
        else {
            matrix[now->idx][next->idx] = findParent(nodeVec[now->parent - 1], next) + 1;
        }
        return matrix[now->idx][next->idx];
    }   
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle10.txt", ios_base::in);    
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        int res = 0;
        int N;
        cin >> N;
        for (int i = 0; i <= N; i++){
            for (int j = 0; j <= N; j++){
                matrix[i][j] = 0;
            }
        }
        int start = 2;
        nodeVec.resize(N, nullptr);
        nodeVec[0] = new Node(1);

        for (int i = 1; i < N; i++){
            nodeVec[start - 1] = new Node(start);
            int parent;
            cin >> parent;
            nodeVec[parent - 1]->vec.push_back(nodeVec[start - 1]);
            matrix[start + 1][parent] = 1;
            matrix[parent][start + 1] = 1;
            nodeVec[start - 1]->parent = parent;
            start++;
        }
        queue<Node*> q;
        q.push(nodeVec[0]);

        while (!q.empty()){
            Node* now = q.front();
            for(const auto& node: now->vec){
                q.push(node);
            }
            q.pop();
            if (q.empty()) {break;}
            Node* next = q.front();
            int val = findParent(now, next);
            res += val;
        }
        cout << '#' << t + 1 << ' ' << res << '\n';
    }
}
