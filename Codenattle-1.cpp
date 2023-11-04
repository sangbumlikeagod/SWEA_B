#include <iostream>
#include <vector>


using namespace std;

// int* arr(int num){
//     int res[10] {0, };

//     while (num > 1){
//         res[num % 10] = 1;
//         num /= 10;
//     } 
//     return &(res[0]);
// }

int arr(int num)
{
    int res = 0;

    while (num >= 1)
    {
        res += (1 << (num % 10));
        num /= 10;
    }
    return res;
}

int main(){

    int N = 1692;
    int goal = 0;
    int k = 1;
    while (goal != ((1 << 10) - 1)){
        // cout << arr(N * k) << '\n';
        goal = goal | arr(N * k);
        if (k < 90){
            cout << goal << ' ' << N * k << '\n';
        }
        k += 1;
    }
    cout << N * (k - 1);
}