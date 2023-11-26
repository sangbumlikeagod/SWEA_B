#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int check_test[10];

bool notFinished(){
    for (int i = 0; i < 10; i++){
        if (!check_test[i]){
            return true;
        }
    }
    return false;
};

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle1.txt", ios_base::in);    

    int testcase;
    cin >> testcase;
    int N;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        cin >> N;
        res = 1;
        // cout << N;
        for (int r = 0; r < 10; r++){
            check_test[r] = 0;
        }

        while (notFinished()){
            int nthVal = N * res;
            // cout << nthVal << '\n';
            while (nthVal){
            if (!check_test[nthVal % 10]){
                    check_test[nthVal % 10] = 1;
                }
                nthVal /= 10;
            }
            res++;
        }

        cout << '#' << tc << ' ' << N * (res - 1) << '\n';
    }



}