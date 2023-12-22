#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int island[22][22];
int numConstructor[55556];
int numVertical[55556];
vector<vector<pair<int, int>>> horizontalConstructor;
vector<vector<pair<int, int>>> verticalConstructor;

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
            if((i == 0 || i == roundN + 1) && (j == 0 || j == roundN + 1)){
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
            if ((0 <= nx <= roundN) && (0 <= ny <= roundN) && (check[nx][ny] != 0) && (island[nx][ny] < height))
            {
                check[nx][ny] = 1;
                q.push(make_pair(nx, ny));
            }
        }
        
    }
    for (int i = 1; i <= roundN ; i++)
    {
        for (int j = 1; j <= roundN; j++)
        {
            if(!check[i][j]) result++;
        }
    }
    
    return result;
};

void init(int N, int mMap[20][20]){
    roundN = N;
    horizontalConstructor.resize(55556, vector<pair<int, int>> {});
    verticalConstructor.resize(55556, vector<pair<int, int>> {});
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
                if (val == 4){
                    cout << j << ' ' << k << '\n';
                }
                int p = 1;
                while (k + p <= N && p < 5)
                {
                    val *= 10;
                    val += island[j][k + p];
                    numConstructor[val]++;
                    horizontalConstructor[val].push_back(make_pair(j, k + p));
                    p++;
                }
                p = 1;
                val = island[j][k];
                while (j + p <= N && p < 5)
                {
                    val *= 10;
                    val += island[j + p][k];
                    verticalConstructor[val].push_back(make_pair(j + p, k));
                    numVertical[val]++;
                    p++;
                }
            }
        }        
};

int numberOfCandidate(int M, int mStructure[5]){
    int result;
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

    cout << val << ' ' << reverse << '\n';

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

    int result;
    int val = 0;
    int reverse = 0;
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

    cout << val << ' ' << reverse << '\n';

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
                    island[x + i][y] += mStructure[i];
                }
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] -= mStructure[i];
                }
            }
            for(const pair<int, int>& arg: horizontalConstructor[tmpVal - reverse]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] += mStructure[i];
                }
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] -= mStructure[i];
                }
            }
            for(const pair<int, int>& arg: verticalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] += mStructure[i];
                }
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] -= mStructure[i];
                }
            }
            for(const pair<int, int>& arg: verticalConstructor[tmpVal - reverse]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] += mStructure[i];
                }
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] -= mStructure[i];
                }
            }
        }
        else{
            for(const pair<int, int>& arg: horizontalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] += mStructure[i];
                }
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x + i][y] -= mStructure[i];
                }
            }
            for(const pair<int, int>& arg: verticalConstructor[tmpVal - val]){
                int x = arg.first;
                int y = arg.second;
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] += mStructure[i];
                }
                result = max(result, BFS(mSeaLevel));
                for (int i = 0; i < M; i++)
                {
                    island[x][y + i] -= mStructure[i];
                }
            }
        }
    }


    return result;
};


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle12.txt", ios_base::in);    
    int tc, ans;
    cin >> tc >> ans;
    for (int t = 0; t < tc; t++){
        int res;
        int command;
        cin >> command;
        for (int pos = 0; pos < command; pos++)
        {
            int id;
            cin >> id;
            if (id == 1)
            {
                int N;
                int mMap[20][20] = {0, };
                cin >> N;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        int tmp;
                        cin >> tmp;
                        mMap[i][j] = tmp;
                    }
                }
                init(N, mMap);
            }
            else if(id == 2)
            {
                int N;
                cin >> N;
                int mStructure[5] = {0, };
                for (int i = 0; i < N; i++)
                {
                    cin >> mStructure[i];
                }
                int ans = numberOfCandidate(N, mStructure);
                int mAns;
                cin >> mAns;
                cout << ans << '\t' << mAns << '\n';
                
            }
            else if(id == 3)
            {
                int N;
                int mStructure[5] = {0, };
                cin >> N;
                for (int i = 0; i < N; i++)
                {
                    cin >> mStructure[i];
                }
                int mSeaLevel;
                cin >> mSeaLevel;
                int ans = maxArea(N, mStructure, mSeaLevel);
                int mAns;
                cin >> mAns;
                cout << ans << ' ' << mAns << " 꾸엑" << '\n';
            }
        }
        



        cout << '#' << t + 1 << ' ' << res;
        break;
    }
}
