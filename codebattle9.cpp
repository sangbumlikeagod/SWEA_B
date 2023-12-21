#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int MaxNum = 300;

int forMine[MaxNum][MaxNum];
int forZero[MaxNum][MaxNum];
int forAns[MaxNum][MaxNum];



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle9.txt", ios_base::in);    
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        for (int i = 0; i < MaxNum; i++)
        {
            for (int j = 0; j < MaxNum; j++)
            {
                forMine[i][j] = 0;
                forZero[i][j] = 0;
                forAns[i][j] = 0;
            }
        }
        int N;
        cin >> N;
        int res = 0;
        
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                char s;
                cin >> s;
                if (s == '*'){
                    forAns[i][j] = 9;
                    forMine[i][j] = 1;
                    for (int k = 0; k < 8; k++){
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if ((0 <= nx) && (nx < N) && (0 <= ny) && (ny < N)){
                            forZero[nx][ny]++;
                        }   
                    }
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if( !forZero[i][j] && !forAns[i][j] ){
                    queue<pair<int,int>> tmp;
                    tmp.push(make_pair(i, j));
                    forAns[i][j] = ++res;
                    while (!tmp.empty())
                    {
                        int x = tmp.front().first;
                        int y = tmp.front().second;
                        for (int k = 0; k < 8; k++){
                            int nx = x + dx[k];
                            int ny = y + dy[k];
                            if ((0 <= nx) && (nx < N) && (0 <= ny) && (ny < N) && !forAns[nx][ny]){
                                forAns[nx][ny] = res;
                                if (!forZero[nx][ny]){ tmp.push(make_pair(nx, ny)); }
                            }   
                        }
                        tmp.pop();
                    }
                    // res++;
                    
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {   
                if (!forAns[i][j]) res++;
            }
        }

        cout << '#' << t + 1 << ' ' << res << '\n';
    }
}