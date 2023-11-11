#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int arr[100][1000];
int recur(pair<int, int> *list, int N, int K)
{
    if (!N){
        return 0;
    }
    if (K < 0){
        return -100000000;
    }
    if (arr[N][K]){
        return arr[N][K];
    }
    int res = 0;

    if ((list)[N].first <= K){
        int tmp1 = recur(list, N - 1, K - (list[N].first)) + list[N].second;
        if (res < tmp1) res = tmp1;
    }
    int tmp2 = recur(list, N - 1, K);
    if (res < tmp2) res = tmp2;
    arr[N][K] = res;
    return res;
};

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("14.txt", ios_base::in);    
    int test_case;
    cin >> test_case;

    for (int i = 0; i < test_case; i++){
        for (int j = 0; j < 100; j++){
            for (int k = 0; k < 1000; k++){
                arr[j][k] = 0;
            }
        }
        int N, K;
        cin >> N >> K;
        pair<int, int>* list = new pair<int, int>[N + 1];
        for (int idx = 1; idx < N + 1; idx++){
            int a, b;
            cin >> a >> b;
            list[idx] = make_pair(a, b);
        }
        int result = recur(list, N, K);
        delete[] list;
        cout << '#' << i + 1 << ' ' << result << '\n';
    }
}

