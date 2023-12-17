#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

const int MAXVAL = 1000000007;


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle6.txt", ios_base::in);    
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        string s;
        cin >> s;
        int length = s.length();
        int res = 0;
        int diary[16][10002] = {0, };

        for (int tmp = 1; tmp < 16; tmp++){
            diary[tmp][0] = 1;
        }
        
        for (int i = 0; i < length; i++)
        {
            int mask = (1 << (s[i] - 'A'));
            if (!i) mask = mask | 1;
            for (int j = 1; j < 16; j++)
            {   
                if ( (j & mask) == mask) 
                {
                    if (i == length - 1)
                    {
                        res = (res + diary[ j ][ i ]) % MAXVAL;
                    }
                    else 
                    {
                        for(int k = 1; k < 16; k++)
                        {
                            if (k & j)
                            {
                                diary[ k ][ i + 1 ] = (diary[ k ][ i + 1 ] + diary[ j ][ i ]) % MAXVAL;
                            }
                        }
                    }
                } 
            }
        }
        cout << '#' << t + 1 << ' ' << res << '\n';
    }
}
