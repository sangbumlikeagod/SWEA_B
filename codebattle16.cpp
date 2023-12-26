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
        priority_queue<int, vector<int>> queueOdd;
        priority_queue<int, vector<int>> queueEven;
        cin >> N >> A;
        res = 0;
        queueOdd.push(A);
        for (int i = 0; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            queueOdd.push(a);
            queueOdd.push(b);
            int size = queueOdd.size() / 2;
            for (int j = 0; j < size; j++)
            {
                queueEven.push(queueOdd.top()); 
                queueOdd.pop();
            }
            res += (queueOdd.top() % 20171109);
            res %= 20171109;
            while (!queueEven.empty())
            {
                queueOdd.push(queueEven.top());
                queueEven.pop();
            }
        }
        
        cout << '#' << tc << ' ' << res << '\n';
    }
}