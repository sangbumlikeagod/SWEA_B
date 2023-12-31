
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
unordered_map<int, int> HUBMAP;
vector<vector<pair<int, int>>> Container;
vector<vector<pair<int, int>>> reverseContainer;

int idx;


int init(int N, int sCity[], int eCity[], int mCost[]) {
    idx = 0;
    HUBMAP.clear();
    Container.clear();

    for (int i = 0; i < N; i++)
    {
        if(HUBMAP.find(sCity[i]) == HUBMAP.end())
        {
            HUBMAP[sCity[i]] = idx++;
        } 
        if (HUBMAP.find(eCity[i]) == HUBMAP.end())
        {
            HUBMAP[eCity[i]] = idx++;
        }
    }
    
    Container.resize(idx, vector<pair<int, int>> {});
    reverseContainer.resize(idx, vector<pair<int, int>> {});
    for (int i = 0; i < N; i++)
    {
        Container[HUBMAP[sCity[i]]].push_back(make_pair(mCost[i], HUBMAP[eCity[i]]));
        reverseContainer[HUBMAP[eCity[i]]].push_back(make_pair(mCost[i], HUBMAP[sCity[i]]));
    }
    
	return idx;
}

void add(int sCity, int eCity, int mCost) {
    Container[HUBMAP[sCity]].push_back(make_pair(mCost, HUBMAP[eCity]));
    reverseContainer[HUBMAP[eCity]].push_back(make_pair(mCost, HUBMAP[sCity]));
	return;
}

int Dijkstra2(int mHub, vector<vector<pair<int, int>>>& Container){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    int start = HUBMAP[mHub];
    Q.push(make_pair(0, start));
    int ans = 0;
    vector<int> visited(idx, 0);

    while (!Q.empty())
    {
        int val = Q.top().first;
        int next = Q.top().second;
        if (!visited[next]){
        visited[next] = 1; 
        ans += val;
        for (pair<int, int> arg : Container[next])
        {
            if (!visited[arg.second])
            {
                Q.push(make_pair(val + arg.first, arg.second));
            }
        }
        }
        Q.pop();
    }
    return ans;
}

int cost(int mHub) {

    int ans = 0;
    ans += Dijkstra2(mHub, reverseContainer);
    ans += Dijkstra2(mHub, Container);
    return ans;
}


int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle32.txt", ios_base::in);    
    
    int sCity[10] = {3,1,5,5,3,5,1,4,2,4};
    int eCity[10] = {2,4,3,4,5,2,5,1,3,5};
    int mCost[10] = {46,15,30,31,23,47,35,24,32,13};
    init(10, sCity, eCity, mCost);
    cout << idx << '\n';
    cout << cost(5);
}