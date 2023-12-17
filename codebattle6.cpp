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
        int diary[4][10002] = {0, };
        diary[0][0] = 1;
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < length; j++)
            {   
                if (s[j] - 'A' == i){
                    // 오늘 담당자가 오늘 키를 가지고 있는 사람과 같을경우
                    for (int p = 0; p < 4; p++)
                    {
                        // 오늘 총 만들어 질수 있던 경우의 수에 * 8가지의 경우의 수가 생긴다
                        if (p == i) {
                            // 키를 누가 가져가는지는 다른 분기가 분명하지만 동아리의 경우의 수와는 또 다르다 교집합을 빼고 더하고를 반복해줘야한다 
                            diary[p][j + 1] += (diary[i][j] * 8) % MAXVAL;
                        } else {
                            diary[p][j + 1] += (diary[i][j] * 4) % MAXVAL;
                        }
                    }
                } else {
                    for (int p = 0; p < 4; p++)
                    {
                        if (p == i | p == s[j] - 'A'){
                            diary[p][j + 1] += (diary[i][j] * 4) % MAXVAL;
                        } else {
                            diary[p][j + 1] += (diary[i][j] * 2) % MAXVAL;
                        }
                    }
                }
            }
            
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < length + 1; j++)
            {
                cout << diary[i][j] << '\t';
            }
            cout << '\n';
        }
        
        for (int i = 0; i < 4; i++)
        {
            res += diary[i][length + 1];
        }
        
        cout << '#' << t + 1 << ' ' << res << '\n';
        break;
    }
}