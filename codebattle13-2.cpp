#include <iostream>
#include <string>
#include <fstream>

#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int dp[1001][1001];


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle13.txt", ios_base::in);    

    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        for (int i = 0; i < 1001; i++){
            memset(dp[i], 0, 1001);
        }
        int res = 0;
        string s1;
        string s2;
        cin >> s1 >> s2;
        if (s2.length() > s1.length()) swap(s1, s2);
        int m = s1.length();
        int n = s2.length();


        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (s1[i] == s2[j]){
                    dp[i][j]++;
                    dp[i + 1][j + 1] = max(dp[i][j], dp[i + 1][j + 1]);
                }
                else {
                    dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
                    dp[i][j + 1] = max(dp[i][j], dp[i][j + 1]);
                    dp[i + 1][j + 1] = max(dp[i][j], dp[i + 1][j + 1]);
                }
            }
        }


        for (int i = 0; i <= m; i++)
        {
            for (int k = 0; k <= n; k++)
            {
                cout << dp[i][k] << ' ';
            }
            cout << '\n';   
        }
        
        for (int i = 0; i <= m; i++){
            res = max(res, dp[i][n]);
        }

        cout << '#' << t + 1 << ' ' << res << '\n';
    }
}

