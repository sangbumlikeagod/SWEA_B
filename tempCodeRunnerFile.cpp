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