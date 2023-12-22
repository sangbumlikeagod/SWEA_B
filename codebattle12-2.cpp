#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int island[22][22];
int MaxNum = 55556;
int numConstructor[55556];
int numVertical[55556];
vector<pair<int, int>> horizontalConstructor[55556];
vector<pair<int, int>> verticalConstructor[55556];

int dx[4] {1, -1, 0, 0};
int dy[4] {0, 0, -1, 1};
int roundN; 

int BFS(int height){
    queue<pair<int, int>> q;
    int result = 0;
    int check[22][22] = {0, };
    for (int i = 0; i <= roundN + 1 ; i++)
    {
        for (int j = 0; j <= roundN + 1; j++)
        {
            if((i == 0 || i == roundN + 1) || (j == 0 || j == roundN + 1)){
                check[i][j] = 1;
                q.push(make_pair(i, j));
            }
        }
    }
    

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if ((1 <= nx && nx <= roundN) && (1 <= ny && ny <= roundN) && (!check[nx][ny]) && (island[nx][ny] < height))
            {
                check[nx][ny] = -1;
                q.push(make_pair(nx, ny));
            }
        }
        
    }
    for (int i = 1; i <= roundN ; i++)
    {
        for (int j = 1; j <= roundN; j++)
        {
            if(check[i][j] != -1) result++;
        }
    }
    
    return result;
};

void init(int N, int mMap[20][20]){
    roundN = N;
    for (int i = 0; i < MaxNum; i++){
        horizontalConstructor[i].clear();
        verticalConstructor[i].clear();
    }
    // horizontalConstructor.resize(55556, vector<pair<int, int>> {});
    // verticalConstructor.resize(55556, vector<pair<int, int>> {});
    memset(numConstructor, 0, sizeof(numConstructor));
    memset(numVertical, 0, sizeof(numVertical));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            island[i][j] = mMap[i - 1][j - 1];
        }
    }
    for (int j = 1; j <= N; j++)
        {
            for (int k = 1; k <= N; k++)
            {
                int val = island[j][k];
                horizontalConstructor[val].push_back(make_pair(j, k));
                numConstructor[val]++;

                int p = 1;
                while (k + p <= N && p < 5)
                {
                    val *= 10;
                    val += island[j][k + p];
                    numConstructor[val]++;
                    horizontalConstructor[val].push_back(make_pair(j, k));
                    p++;
                }
                p = 1;
                val = island[j][k];
                while (j + p <= N && p < 5)
                {
                    val *= 10;
                    val += island[j + p][k];
                    verticalConstructor[val].push_back(make_pair(j, k));
                    numVertical[val]++;
                    p++;
                }
            }
        }        
};

int numberOfCandidate(int M, int mStructure[5]){
    int result = 0;
    int reverse = 0;
    int val = 0 ;
    int minM = 5;
    int maxM = 0;
    for (int i = 0; i < M; i++)
    {
        val *= 10;
        val += mStructure[i];
        minM = min(minM, mStructure[i]);
        maxM = max(maxM, mStructure[i]);
    }
    for (int i = M - 1; 0 <= i ; i--)
    {
        reverse *= 10;
        reverse += mStructure[i];
    }


    for (int i = maxM + 1; i <= minM + 5; i++){
        int tmpVal = 0;
        for (int j = 0; j < M; j++){
            tmpVal *= 10;
            tmpVal += i;
        }
        if (reverse != val){
            result += numConstructor[tmpVal - val];
            result += numVertical[tmpVal - val ];
            result += numConstructor[tmpVal - reverse ];
            result += numVertical[tmpVal - reverse ];
        }
        else{
            result += numConstructor[tmpVal - val ];
            result += numVertical[tmpVal - val ];
        }
    }

    return result;
};

int maxArea(int M, int mStructure[5], int mSeaLevel){
    int result = 0;
    int val = 0;
    int reverse = 0;
    int minM = 5;
    int maxM = 0;
    int attempt = 0;
    for (int i = 0; i < M; i++)
    {
        val *= 10;
        val += mStructure[i];
        minM = min(minM, mStructure[i]);
        maxM = max(maxM, mStructure[i]);
    }
    for (int i = M - 1; 0 <= i ; i--)
    {
        reverse *= 10;
        reverse += mStructure[i];
    }

    for (int i = maxM + 1; i <= minM + 5; i++){
        int tmpVal = 0;
        for (int j = 0; j < M; j++){
            tmpVal *= 10;
            tmpVal += i;
        }
        if (reverse != val){

            for(const pair<int, int>& arg: horizontalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] += mStructure[i];
                }
                int gal = BFS(mSeaLevel);
                // cout << x << ' ' << y << ' ' << gal << '\n';
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] -= mStructure[i];
                }
                attempt++;
            }
            for(const pair<int, int>& arg: horizontalConstructor[tmpVal - reverse]){
                int x = arg.first;
                int y = arg.second;
                for (int i = M - 1; i >= 0; i--)
                {
                    island[x][y + i] += mStructure[M - 1 - i];
                }
                int gal = BFS(mSeaLevel);
                // cout << x << ' ' << y << ' ' << gal << '\n';

                result = max(result, BFS(mSeaLevel));
                for (int i = M - 1; i >= 0; i--)
                {
                    island[x][y + i] -= mStructure[M - 1 - i];
                }
                attempt++;

            }
            for(const pair<int, int>& arg: verticalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] += mStructure[i];
                }
                int gal = BFS(mSeaLevel);
                // cout << x << ' ' << y << ' ' << gal << '\n';

                result = max(result, gal);
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] -= mStructure[i];
                }
                attempt++;
            }
            for(const pair<int, int>& arg: verticalConstructor[tmpVal - reverse]){
                int x = arg.first;
                int y = arg.second;
                for (int i = M - 1; i >= 0; i--)
                {
                    island[x + i][y] += mStructure[M - 1 - i];
                }
                int gal = BFS(mSeaLevel);
                // cout << x << ' ' << y << ' ' << gal << '\n';

                result = max(result, gal);
                for (int i = M - 1; i >= 0; i--)
                {
                    island[x + i][y] -= mStructure[M - 1 - i];
                }
                attempt++;
            }
        }
        else{
            for(const pair<int, int>& arg: horizontalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] += mStructure[i];

                }
                int gal = BFS(mSeaLevel);
                // cout << x << ' ' << y << ' ' << gal << '\n';

                result = max(result, gal);
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] -= mStructure[i];
                }
                attempt++;
            }
            for(const pair<int, int>& arg: verticalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] += mStructure[i];

                }
                int gal = BFS(mSeaLevel);
                // cout << x << ' ' << y << ' ' << gal << '\n';

                result = max(result, gal);
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] -= mStructure[i];
                }
                attempt++;
            }
        }
    }

    if (!result && !attempt) return -1; 
    return result;
    
};

