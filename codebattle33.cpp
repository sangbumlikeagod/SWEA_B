#include <fstream>

#include <iostream>

#include <vector>
#include <map>
#include <cstring>

#include <unordered_map>
#include <queue>
using namespace std;

int TIMENOW;
const int MAXVAL = 50001;

// map<pair<int, int>, int> Training;
map<int, priority_queue<int, vector<int>, greater<int>>> Training;
int robots[MAXVAL];
map<int, int> works[MAXVAL];

void init(int N)
{
	// 초기화
    TIMENOW = 0;
    Training.clear();
    memset(robots, 0, sizeof(robots));
    for (int i = 1; i <= N; i++)
    {
        works[i].clear();
        Training[0].push(i);
    }
}

int callJob(int cTime, int wID, int mNum, int mOpt)
{
    TIMENOW = cTime;
    int ans = 0;
    map<int, priority_queue<int, vector<int>, greater<int>>>::iterator start;  
    // priority_queue<int, vector<int>, greater<int>>* Q = &(start -> second);
    if (mOpt)
    {
        start = --Training.end();
    }
    else
    {
        start = Training.begin();
    }
    
    while (mNum)
    {
        int intel = TIMENOW - (start -> first);
        // Q가 비어있지 않은동안 반복
        while (!(start -> second).empty())
        {
            // robots중 (*.)top() 요소에 작업함을 동기화
            robots[(start -> second).top()] = -wID;
            // works wID인덱스에 로봇이 intel만큼의 지능을 가지고 왔다는것을 표현
            works[wID][(start -> second).top()] = intel;
            // 1개만큼 로봇 씀
            mNum--;
            // 고유번호 합
            ans += (start -> second).top();
            // 그 값을 map에서 지움
            (start -> second).pop();

            // mNum이 다 사라졌다면 ans를 리턴함
            if (!mNum) return ans;
        }

        if (mOpt)
        {
            // 바보같은 순으로 뽑는다면
            start--;
        }
        else
        {
            // 똑똑한순으로 뽑는다면 오른쪽으로 
            start++;
        }
           
    }
	return ans;
}

void returnJob(int cTime, int wID)
{
    TIMENOW = cTime;
	
    // for (map<int, int>::iterator start = works[wID].begin(); start != works[wID].end(); start++)
    // {
    //     // 지금 로봇의 지능을 보존된 지능값을 현재시간에서 뺀것으로 환산해서 상대적인 비교 가능하게함 로봇에 지능 업데이트
    //     int Intel = TIMENOW - (start -> second);
        
    //     Training[Intel].push(start -> first);
    //     robots[start -> first] = Intel;

    // }
    for (const auto& pair : works[wID]) {
    int Intel = TIMENOW - pair.second;
    Training[Intel].push(pair.first);
    robots[pair.first] = Intel;
    }
    // 전부 복귀이니 데이터 없앰
    works[wID].clear();
    
}

void broken(int cTime, int rID)
{
	TIMENOW = cTime;
    if ((robots[rID] < 0) &&  (robots[rID] != -50001))
    {
        // 지금 로봇이 일하고있는 작업장에서 rID의 로봇을 없애고 로봇에도 업데이트한다
        works[-1 * robots[rID]].erase(rID);
        robots[rID] = -50001;
    }
    
}

void repair(int cTime, int rID)
{
	TIMENOW = cTime;
    if (robots[rID] == -50001){
    robots[rID] = cTime;
    Training[cTime].push(rID);}
}

int check(int cTime, int rID)
{
    TIMENOW = cTime;
    if (robots[rID] == -50001)
    {
        return 0;
    }
    else if (robots[rID] < 0)
    {
        return robots[rID];
    }
    else
    {
        return TIMENOW - robots[rID];
    }
    
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle33.txt", ios_base::in);    
    

    int testcase, gar;
    cin >> testcase >> gar;
    int N;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        int n;
        cin >> n;
        cin >> N;
        cout << tc << '\t' << N << '\n';
        init(n);
        int idx = 1;
        for (int command = 0; command < N; command++)
        {
            int com;
            cin >> com;
            // 100 callJOB

            if (com == 100){
                int a, b, c, d;
                cin >> a >> b >> c >> d;
                int ans = callJob(a, idx++, b, c);
                if (ans != d){
                    cout << command << "\t" << com << "@" << ans << ' ' << d << ' ' << b << ' ' << c <<'\n';
                }
            } 
            else if (com == 200)
            {
                int a, b;
                cin >> a >> b;
                returnJob(a, b);
            }
            else if (com == 300)
            {
                int a, b;
                cin >> a >> b;
                broken(a, b); 
            }
            else if (com == 400)
            {
                int a, b;
                cin >> a >> b;
                repair(a, b);

            }
            else if (com == 500)
            {
                int a, b, c;
                cin >> a >> b >> c;
                int ans = check(a, b);
                if (ans != c){
                    cout << command << "\t" << com <<  '#' << ans << ' ' << c << ' ' << robots[b] << '\n';
                }
            }
            
        }
        if (tc == 10) break;
    }


    // cout << callJob(11, 3, 2, 0) << '\n';
    // cout <<  check(4, 5) << '\n';

}