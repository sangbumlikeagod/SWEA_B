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


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle10.txt", ios_base::in);    
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        int res;
        int N;
        cin >> N;

        int start = 2;
        nodeVec.resize(N, nullptr);
        nodeVec[0] = new Node(1);


        cout << '#' << t + 1 << ' ' << res;
    }
}