#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle3.txt", ios_base::in);    
    
    int testcase;
    cin >> testcase;
    int N;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        cin >> N;
        res = 1;
        cout << '#' << tc << ' ' << N * (res - 1) << '\n';
    }



}