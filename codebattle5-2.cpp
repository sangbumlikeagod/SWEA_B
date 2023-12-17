#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


struct Node
{
    int Id;
    int Version;
    int Team;
    Node* next;
    Node(int mid, int mVersion) : Id(mid), Version(mVersion), next(nullptr){};
};
class LinkedList
{
public:
    Node* head;
    Node* tail;
    void addNode(Node* node)
    {
        if (head == nullptr) 
        { 
            head = node;
            tail = node;
        }
        else 
        {
            tail->next = node;
            tail = tail->next;
        }
    }    
    LinkedList() : head(nullptr), tail(nullptr) {};
};
int soldierVersion[100001] = {0, };
int soldierTeam[100001] = {0, };


vector<vector<LinkedList>> Team = {5, vector<LinkedList> {5, LinkedList()}};


void init() 
{

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
        Team[i][j] = LinkedList();
        }
    }
    
    for (int j = 0; j < 100000; j++){
        soldierVersion[j] = 0;
        soldierTeam[j] = 0;
    }
};


void hire(int mID, int mTeam, int mScore)
{
    Team[mTeam - 1][mScore - 1].addNode(new Node(mID ,soldierVersion[mID]));
    soldierTeam[mID] = mTeam;
};

void fire(int mID)
{ 
    soldierVersion[mID]++;
    soldierTeam[mID] = -1;
}

void updateSoldier(int mID, int mScore)
{
    soldierVersion[mID]++;
    Team[soldierTeam[mID] - 1][mScore - 1].addNode(new Node(mID, soldierVersion[mID]));
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore > 0)
    {   
        int start = 4;
        while (start > 0)
        {   
            if (Team[mTeam - 1][start - 1].head == nullptr) {
                start--;
                continue;
            }
            if (Team[mTeam - 1][min(4, mChangeScore + start - 1)].tail != nullptr)
            {
                Team[mTeam - 1][min(4, mChangeScore + start - 1)].tail->next = Team[mTeam - 1][start - 1].head;
                Team[mTeam - 1][min(4, mChangeScore + start - 1)].tail = Team[mTeam - 1][start - 1].tail;
            }
            else 
            {
                Team[mTeam - 1][min(4, mChangeScore + start - 1)].head = Team[mTeam - 1][start - 1].head;
                Team[mTeam - 1][min(4, mChangeScore + start - 1)].tail = Team[mTeam - 1][start - 1].tail;
            }
            Team[mTeam - 1][start - 1].head = nullptr;
            Team[mTeam - 1][start - 1].tail = nullptr;
            // Team[mTeam - 1][min(4, mChangeScore + start - 1)].printhead();
            start--;
        }
    }
    else if (mChangeScore == 0)
    {
        return;
    }
    else if (mChangeScore < 0)
    {
        int start = 1;
        while (start < 5)
        {
            if (Team[mTeam - 1][start].head == nullptr) {
                start++;
                continue;
            }
            if (Team[mTeam - 1][max(0, mChangeScore + start)].tail != nullptr)
            {
                Team[mTeam - 1][max(0, mChangeScore + start)].tail->next = Team[mTeam - 1][start].head;
                Team[mTeam - 1][max(0, mChangeScore + start)].tail = Team[mTeam - 1][start].tail;
            }
            else
            {
                Team[mTeam - 1][max(0, mChangeScore + start)].head = Team[mTeam - 1][start].head;
                Team[mTeam - 1][max(0, mChangeScore + start)].tail = Team[mTeam - 1][start].tail; 
            }
            Team[mTeam - 1][start].head = nullptr;
            Team[mTeam - 1][start].tail = nullptr;
            start++;
        }
    }
}

int bestSoldier(int mTeam)
{
    int start = 4;
    int maxNum = 0;
    while ((!maxNum) & (start >= 0) )
    {
        // Team[mTeam - 1][start].printhead();
        Node* tmpHead = Team[mTeam - 1][start].head;
        while (tmpHead != nullptr)
        {
            if ((tmpHead->Version == soldierVersion[tmpHead->Id]) & (mTeam == soldierTeam[tmpHead->Id]) ){
                maxNum = max(maxNum, tmpHead->Id);
            }
            tmpHead = tmpHead->next;
        }
        start--;
    }
    return maxNum;
}