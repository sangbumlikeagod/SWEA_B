#include <iostream>
#include <string>

using namespace std;

char* arr;
int n;
string result;

void dfs(int cur) {
    if (cur > n) return;

    dfs(cur * 2);
    cout << arr[cur];
    dfs(cur * 2 + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int tc = 1; tc <= 10; tc++) {
        cout << "#" << tc << " ";

        cin >> n;
        cin.ignore();
        arr = new char[n + 1];

        for (int i = 1; i <= n; i++) {
            string input;
            getline(cin, input);
            bool flag = false;
            for (char c : input) {
                if (flag) {
                    arr[i] = c;
                    break;
                }
                if (c == ' ') flag = true;
            }
        }

        dfs(1);
        cout << "\n";

        delete[] arr;
    }

    cout << result;

    return 0;
}
