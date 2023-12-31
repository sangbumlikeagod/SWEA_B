#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;
#define MAX_N 50000
#define MAX_M 50000
#define MAX_LEN 11

unordered_map<string, int> visited;
map<int, int> contester;
map<string, int> box[26];
int numofWord = 0;
vector<int> visitedVec;

void init(int N, int M, char mWords[][MAX_LEN])
{
    numofWord = 0;
    visited.clear();
    visitedVec.resize(2 * M , 0); 
    visitedVec.clear();
    contester.clear();
    for (int z = 0; z < 26; z++)
    {
        box[z].clear();
    }
    

    for (int i = 1; i <= N; i++)
    {
        contester[i] = 1;
    }

    for (int j = 0; j < M ; j++)
    {
        string s = mWords[j];
        if (!visited[s])
        {
            visited[s] = numofWord++;
        }
        
        box[s[0] - 'a'][s] = 1;
        reverse(s.begin(), s.end());

        if (!visited[s])
        {
            visited[s] = numofWord++;
        }
    }
}

int playRound(int mID, char mCh)
{
    vector<string> leftover;
    vector<map<string, int>::iterator> pointer;
    for (int i = 0; i < 26; i++)
    {
        pointer.push_back(box[i].begin());
    }
    int index = mCh - 'a';
    int player = mID;
    while (true)
    {
        if (pointer[index] == box[index].end()){
            break;
        }
        string word = pointer[index] -> first;
        cout << word << '\t';

        // 선택한 단어를 방문처리
        visitedVec[visited[word]] = 1;

        // 지금 begin 포인터를 다음으로 옮김
        pointer[index]++;
        reverse(word.begin(), word.end());
        
        // 이미 중복된 상황이 아닐경우 뒤집은 문자 추가 
        cout << word << ' ' << visitedVec[visited[word]] << '\n';
        if (!visitedVec[visited[word]])
        {
            leftover.push_back(word);   
        }
        
        // 다음 인덱스 지정 
        index = word[0] - 'a';
        
        // 다음 플레이어 선정
        if (contester.upper_bound(player) == contester.end()){
            player = contester.begin() -> first;
        } else {
            player = contester.upper_bound(player) -> first;
        }
    }

    // 이번턴에서 사용했던 요소들을 정리한다.
    for (int i = 0; i < 26; i++)
    {   
        // cout << box[i].size() << ' ';
        box[i].erase(box[i].begin(), pointer[i]);
        // cout << box[i].size() << '\t';
    }

    // 추가됐던 놈들 전부 다시 map에 추가한다.
    for (string s : leftover)
    {
        box[s[0] - 'a'][s] = 1;
    }
    
    
    contester.erase(player);
	return player;
}



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle36.txt", ios_base::in);    
    
    // int testcase;
    // cin >> testcase;
    // int N;
    // int res;
    // for (int tc = 1; tc <= testcase; tc++){
    //     cin >> N;
    //     res = 1;
    //     cout << '#' << tc << ' ' << N * (res - 1) << '\n';
    // }

    
    char list[][11] = {"eye", "ezone", "event", "tee", "east"};


    init(4, 5, list);
    for (pair<string, int> i : box['e' - 'a'])
    {
        cout << i.first << '\t';
    }
    cout << '\n';
    
    cout << playRound(3, 'e') << '\n';
    cout << playRound(3, 't') << '\n';
    cout << playRound(3, 'e') << '\n';
    cout << "=====================================================================================" << '\n'; 
    char list2[][11] = {"six", "but", "soap", "laugh", "everybody", "three", "eye"};

    init(5, 7, list2);

    for (pair<string, int> i : visited)
    {
        cout << i.first << ' ' << i.second << '\t';
    }

    cout << '\n';
    cout << playRound(1, 'e') << '\n';



    cout << playRound(3, 'y') << '\n';
    cout << playRound(1, 't') << '\n';


}