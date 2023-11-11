#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


int init(){
    return 0;
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    // ifstream cin(".txt", ios_base::in);    
    int** arr = new int*[10];

    for (int i = 0; i < 10 ;i++) {
        arr[i] = new int[10];
    }
    
    arr[5][5] = 5;


    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10 ; j++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    int b[2] = {1, 5};
    cout << b[1];
}