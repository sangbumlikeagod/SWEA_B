#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


int processor[13][13] = {0, };
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
vector<vector<int>> chips;
// 위 1 아래 2 왼 4 오 8 
int maxConnect = 0;
int minCost = 1000000;   
int N;
 

void backtracking(vector<vector<int>>& chips, int index, int curConnect, int curCost){

    if (index == chips.size()) {
        if (maxConnect < curConnect) {

            maxConnect = curConnect;
            minCost = curCost;
        }
        else if (maxConnect == curConnect){
            minCost = min(curCost, minCost);
        }
        return;
    }
    int x = chips[index][0];
    int y = chips[index][1];
    

    if (processor[x][y])
    {
        if (curConnect + chips.size() - index >= maxConnect)
        {
            for (int i = 0; i < 4; i++){
                if (processor[x][y] & (1 << i))
                {
                    int forRecover[13] = {0, }; 
                    int k = 0;
                    int isokay = 1;
                    if (i == 0){
                            int nx = x;
                            int ny = y;
                            while (nx)
                            {
                                if (!processor[nx][ny]) {
                                    isokay = 0;
                                    break;
                                }
                                forRecover[k] = processor[nx][ny];
                                processor[nx][ny] = 0;
                                k++;
                                nx += dx[1];
                                ny += dy[1];
                            }
                            if (!isokay) {
                                while (k){
                                nx += dx[0];
                                ny += dy[0];
                                processor[nx][ny] = forRecover[--k];
                                }
                                continue;
                                }
                            k = 0;
                            backtracking(chips, index + 1, curConnect + 1, curCost + x);
                            nx = x;
                            ny = y;
                            while (nx)
                            {
                                processor[nx][ny] = forRecover[k];
                                k++;
                                nx += dx[1];
                                ny += dy[1];
 
                        }
                    }


                    else if (i == 1){
                            int nx = x + dx[0] * k;
                            int ny = y + dy[0] * k;
                            while (nx < N)
                            {
                                if (!processor[nx][ny]) {
                                    isokay = 0;
                                    break;
                                }
                                forRecover[k] = processor[nx][ny];

                                processor[nx][ny] = 0;
                                k++;
                                nx += dx[0];
                                ny += dy[0];
                            }
                            if (!isokay) {
                                while (k){
                                nx += dx[1];
                                ny += dy[1];
                                processor[nx][ny] = forRecover[--k];
                                }
                                continue;}

                            k = 0;
                            backtracking(chips, index + 1, curConnect + 1, curCost +  N - 1 - x);
                            nx = x;
                            ny = y;
                            while (nx < N) 
                            {
                                processor[nx][ny] = forRecover[k];
                                k++;
                                nx += dx[0];
                                ny += dy[0];
                            }
                    }


                    else if (i == 2){

                            int nx = x ;
                            int ny = y ;
                            while (ny)
                            {
                                if (!processor[nx][ny]) {
                                    isokay = 0;
                                    break;
                                }
                                forRecover[k] = processor[nx][ny];

                                processor[nx][ny] = 0;
                                k++;
                                nx += dx[3];
                                ny += dy[3];
                            }
                            if (!isokay) {
                                while (k){
                                nx += dx[2];
                                ny += dy[2];
                                processor[nx][ny] = forRecover[--k];
                                }
                                continue;}

                            k = 0;
                            nx = x;
                            ny = y;
                            backtracking(chips, index + 1, curConnect + 1, curCost + y);
                            while (ny) 
                            {
                                processor[nx][ny] = forRecover[k];
                                k++;
                                nx += dx[3];
                                ny += dy[3];
                            }
  
                    }



                    else if (i == 3){

                            int nx = x ;
                            int ny = y ;
                            while (ny < N)
                            {
                                if (!processor[nx][ny]) {
                                    isokay = 0;
                                    break;
                                }
                                forRecover[k] = processor[nx][ny];
                                processor[nx][ny] = 0;
                                k++;
                                nx += dx[2];
                                ny += dy[2];
                            }
                            if (!isokay) {
                            while (k){
                                nx += dx[3];
                                ny += dy[3];
                                processor[nx][ny] = forRecover[--k];
                                }
                                continue;}

                            k = 0;
                            nx = x;
                            ny = y;
                            backtracking(chips, index + 1, curConnect + 1, curCost +  N - 1 - y);
                            while (ny < N) 
                            {
                                processor[nx][ny] = forRecover[k];
                                k++;
                                nx += dx[2];
                                ny += dy[2];
                            }

                    }
                }
            }
        }
    }
    backtracking(chips, index + 1, curConnect, curCost);
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle11.txt", ios_base::in);    
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++){
        maxConnect = 0;
        minCost = 1000000;  
        N = 0;
        cin >> N;
        chips.clear();
        for (int j = 0; j < 13; j++)
        {
            for (int k = 0; k < 13; k++)
            {
                processor[j][k] = 15;
            }
        }
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                int val;
                cin >> val;
                
                if (val){
                    if ( (0 < j && j < N - 1) && (0 < k && k < N - 1) ) chips.push_back(vector<int> {j, k});

                    for (int i = 0; i < 4; i++)
                    {
                        int nx = j + dx[i];
                        int ny = k + dy[i];
                        while ( (0 <= nx) && (nx < N) && (0 <= ny) && (ny < N) && ((1 << i) & processor[nx][ny]))
                        {
                            processor[nx][ny] -= (1 << i);
                            nx += dx[i];
                            ny += dy[i];
                        }
                    }
                }
            }
        }

        backtracking(chips, 0, 0, 0);
        cout << '#' << t + 1 << ' ' << minCost << '\n';

    }
}