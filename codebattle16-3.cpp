#include <iostream>
#include <fstream>
#include <algorithm>

#include <vector>
#include <map>
#include <queue>

using namespace std;



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle16.txt", ios_base::in);    
    
    int testcase;
    cin >> testcase;
    int N;
    int A;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        int size = 1;
        cin >> N >> A;

        vector<int> start {};
        res = 0;
        start.push_back(A);

        for (int i = 0; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            vector<int>::iterator whereA = upper_bound(start.begin(), start.end(), a);
            start.insert(whereA, a);
            vector<int>::iterator whereB = upper_bound(start.begin(), start.end(), b);
            start.insert(whereB, b);
            res += start[start.size() / 2] % 20171109;
            res %= 20171109;
        }   
        cout << '#' << tc << ' ' << res << '\n';
    }
}