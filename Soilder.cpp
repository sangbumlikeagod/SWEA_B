#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


// class Soilders{

//     Soilders(){

//     }
//     void hire(int mID, int mTeam, int mScore){

//     }
//     void fire(int mID){

//     }
//     void updateSoldier(int mID, int mScore){

//     }
//     void bestSoldier(int mTeam){

//     }

// };


int t1;
int t2;
int t3;
int t4;
int t5;

pair<int, int>  arr[100000];
int* teams[5][100000] = {0, };
void init(){
    // for (int a : arr){
    //     a = 0;
    // }
    for (int i = 0; i < 100000; i ++){
        arr[i] = make_pair(NULL, NULL);
    }
}

void fire(int mID)
{
    teams[arr[mID].first][mID] = nullptr;
    arr[mID] = make_pair(NULL, NULL);
}

void bestSoldier(int mTeam)
{

}

struct ListNode{
    int id;
    int v;
    ListNode* nxt;
    ListNode() {}
    ListNode(int id, int v):id(id), v(v), nxt(nullptr){}
    ListNode(int id, int v, ListNode *nxt) : id(id), v(v), nxt(nxt){}
}listnode[500055];
int cnt;
int version[100055], num[100055];

ListNode* getNewNode(int id, ListNode* nxt = nullptr){
    ListNode *ret = &listnode[cnt++]; 
    ret -> id = id;
    ret -> nxt = nxt;
    ret -> v = ++version[id];
    return ret;
}

struct Team{
    ListNode* head[6];
    ListNode* tail[6];
}t[6];

// linked list를 25개를 만들었다고 보면 된다.

void init()
{
    cnt = 0;
    for (int i =1; i <= 5; i++){
        for (int j = 1; j <= 5 ; j++){
            t[i].tail[j] 
        }
    }
}
void hire(int mID, int mTeam, int mScore)
{
    ListNode* newNode = getNewNode(mID);
    t[mTeam].tail[mScore] -> nxt = newNode;
    t[mTeam].tail[mScore] = newNode;
    num[mID] = mTeam;
}
void fire(int MiD){
    version[MiD] = -1;
}

void updateSoldier(int mID, int mScore)
{
    hire(mID, num[mID], mScore);
}

void updateTeam(int mTeam, int mChangeScore){
    if (mChangeScore < 0){
        for (int j = 1; j <= 5; j++){
            int k = 
        }
    } else {
        for (int j = 5; j >= 1; j == 1){
            int k = j + mChangeScore;
            if (k < 1) k = 1;
            if (k > 5) k = 5;
            if (j == k) continue;
            if (t[mTeam].head[j] -> nxt == nullptr) continue;
            t[mTeam].head[j] -> nxt = t[mTeam].head[j] ->nxt;
            t[mTeam].tail[k] = t[mTeam].tail[j];
            
        }
    }
}

// 테스트 케이스가 여러개 있는 경우에만 
// 버저놘리라는걸 해주시자나
int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("soilder.txt", ios_base::in);    
    int testCase;
    // arr[1] = 3;
    init();

    hire(5, 1, 5);
    cout << arr[5].second;
    arr[5].second += 1;
    cout << *teams[1][5];
    



}