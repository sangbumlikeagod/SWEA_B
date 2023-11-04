#include <iostream>
using namespace std;

int tc;

int main(){
    cin >> tc;
    for(int _ = 0;_ < tc ; _++ ){
        int N, M;
        cin >> N >> M;
        // cout << N << M << endl; 
        if ((((1 << (N)) - 1) & M) == ((1 << (N)) - 1)){
            cout <<'#' << _ + 1 << ' ' << "ON";
        } else {
            // cout << (((1 << (N)) - 1) & M) << ' ' << ((1 << (N)) - 1) << ' ' << M << '\n';

            cout << '#' << _ + 1 << ' '<< "OFF";
        }
    }
}
