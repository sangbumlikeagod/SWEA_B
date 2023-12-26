#include <iostream>
#include <fstream>
#include <vector>
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
        priority_queue<int, vector<int>, greater<int>> minH;
        // 큰놈들
        priority_queue<int, vector<int>, less<int>> maxH;
        // 작은놈들
        cin >> N >> A;
        res = 0;
        minH.push(A);
        for (int i = 0; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            if (a > b) {
                minH.push(a);
                maxH.push(b);
            }
            else {
                minH.push(b);
                maxH.push(a); 
            }
            // cout << minH.top() << '\t' << '\t' << maxH.top() << '\n';

            while (minH.top() < maxH.top()){
                maxH.push(minH.top());
                minH.pop();
                minH.push(maxH.top());
                maxH.pop();
            }
            // 1 2 8 3 5 6 9
            // cout << minH.top() << '\t' << '\t' << maxH.top() << '\n';
            if (minH.size() > maxH.size()){
                res += (minH.top() % 20171109);
            }
            else{
                res += (maxH.top() % 20171109);
            }
            res %= 20171109;
            cout << '\t' <<  res << '\n';
        }
        
        cout << '#' << tc << ' ' << res << '\n';
    }
}