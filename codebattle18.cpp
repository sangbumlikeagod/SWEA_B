#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<string, int> map;

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle18.txt", ios_base::in); 
    int tc;
    cin >> tc;
    for (int i = 0; i < tc; i++){
        map.clear();
        int N, M;
        cin >> N >> M;
        int res = 0;
        string s;
        for (int j = 0; j < N; j++){
            cin >> s;
            map[s] = 1;
        }
        for (int k = 0; k < M; k++){
            cin >> s;
            if (map[s]){
                res++;
            }
        }
        cout << '#' << i + 1 << ' '<< res << '\n';
    }
}