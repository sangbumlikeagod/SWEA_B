#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

const int MOD = 20171109;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        priority_queue<int, vector<int>, greater<int>> minH;
        priority_queue<int, vector<int>, less<int>> maxH;

        int N, A;
        cin >> N >> A;

        minH.push(A);
        int answer = 0;

        for (int i = 0; i < N; i++) {
            int num1, num2;
            cin >> num1 >> num2;

            if (num1 > num2) {
                minH.push(num1);
                maxH.push(num2);
            } else {
                minH.push(num2);
                maxH.push(num1);
            }

            while (!minH.empty() && !maxH.empty() && minH.top() < maxH.top()) {
                int minVal = minH.top();
                int maxVal = maxH.top();
                minH.pop();
                maxH.pop();
                minH.push(maxVal);
                maxH.push(minVal);
            }

            answer = (minH.top() + answer) % MOD;
        }

        cout << "#" << t << " " << answer << endl;
    }

    return 0;
}
