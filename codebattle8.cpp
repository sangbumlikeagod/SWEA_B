#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


short arr[10001] {0, 0,};
vector<short> adj_arr[10001];

short dfs(short root)
{
    short depth = 1;
    short tmp = 0;

    while (!adj_arr[root].empty())
    {
        short nxt = adj_arr[root].back();
        adj_arr[root].pop_back();
        depth += dfs(nxt);  
    }
    return depth;
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("8.txt", ios_base::in);    

    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        short V, E, s, e;
        cin >> V >> E >> s >> e;

        for (short i = 0; i < 10001; i++){
            adj_arr[i].clear();
        }
        for (short i; i < 10001 ; i++ ){
            arr[i] = 0;
        }

        for (short i = 0; i < E; i++){
            short child, parent;
            cin >> parent >> child;
            arr[child] = parent;
            adj_arr[parent].push_back(child);
        }
        vector<short> v1;
        vector<short> v2;
        while (s != 0){
            v1.push_back(s);
            s = arr[s];
        }

        while (e != 0){
            v2.push_back(e);
            e = arr[e];
        }
        short idx1 = v1.size();
        short idx2 = v2.size();
        short ans;

        while (v1[idx1 - 1] == v2[idx2 - 1]){
            ans = v1[idx1 - 1];
            idx1 -= 1;
            idx2 -= 1;
        }

        cout << '#' << t + 1 << ' '<< ans << ' ';
        cout << dfs(ans) << '\n';

    }
    
}