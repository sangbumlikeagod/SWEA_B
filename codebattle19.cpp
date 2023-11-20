#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;


int hash1 = 31;
int hash2 = 37;
int hash3 = 41;


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin(".txt", ios_base::in);    
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        int res;
        string a;
        string b;
        cin >> a;
        cin >> b;
    




        cout << '#' << t + 1 << ' ' << res;
    }
}