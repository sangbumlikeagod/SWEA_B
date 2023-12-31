#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

struct Node{
    int x;
    Node* next;
    Node* before;
    Node(int x) : x(x), next(nullptr), before(nullptr){}
};

map<int, Node*> LADDER[101];
const int MAXNUM = 1000000000;

void init()
{
    for (int i = 1; i < 101; i++)
    {
        LADDER[i].clear();
        Node* start = new Node(i);
        Node* end = new Node(i);
        start -> next = end;
        end -> before = start;
        LADDER[i][0] = start;
        LADDER[i][MAXNUM] = end;
    }
}

void add(int mX, int mY)
{
    Node* xNode = new Node(mX);
    Node* yNode = new Node(mX + 1);
    LADDER[mX][mY] = xNode;
    LADDER[mX + 1][mY] = yNode;
    map<int, Node*>::iterator left = LADDER[mX].upper_bound(mY);
    map<int, Node*>::iterator right = LADDER[mX + 1].upper_bound(mY);

    Node* leftNode = left -> second;
    Node* rightNode = right -> second;

    xNode->next = rightNode;
    xNode->before = leftNode -> before;
    
    yNode->next = leftNode;
    yNode->before = rightNode -> before;

    leftNode->before->next = xNode;
    rightNode->before->next = yNode;
    leftNode->before = yNode;
    rightNode->before = xNode;

}

void remove(int mX, int mY)
{
    Node* left = LADDER[mX].find(mY) -> second;
    Node* right = LADDER[mX + 1].find(mY) -> second;
    left->before->next = right->next;
    right->next->before = left->before;
    right->before->next = left->next;
    left->next->before = right->before;
    LADDER[mX].erase(mY);
    LADDER[mX + 1].erase(mY);
}

int numberOfCross(int mID)
{
    Node* start = LADDER[mID].begin() -> second;
    int count = 0;
    while (start->next != nullptr)
    {
        start = start->next;
        count++;
    }
	return count - 1;
}

int participant(int mX, int mY)
{
    map<int, Node*>::iterator start;
    if (mY == MAXNUM)
    {
        start = LADDER[mX].find(mY);
    } 
    else {
        Node* xNode = new Node(mX);
        LADDER[mX][mY] = xNode;
        start = LADDER[mX].upper_bound(mY);
        LADDER[mX].erase(mY);
    }
    
    Node* startNode = start -> second;
    while (startNode->before != nullptr)
    {
        startNode = startNode->before;
    }
	return startNode->x;
}



int main(){
    ios::sync_with_stdio(false), cin.tie(0), cin.tie(0);
    ifstream cin("codebattle29.txt", ios_base::in);    
    
   
    int testcase, gar;
    cin >> testcase >> gar;
    int N;
    int res;
    for (int tc = 1; tc <= testcase; tc++){
        cin >> N;
        cout << tc << '\t' << N << '\n';
        for (int command = 0; command < N; command++)
        {
            int com;
            cin >> com;
            if (com == 1){
                init();
            } 
            else if (com == 2)
            {
                int a, b;
                cin >> a >> b;
                add(a, b);
            }
            else if (com == 3)
            {
                int a, b;
                cin >> a >> b;
                remove(a, b);
            }
            else if (com == 4)
            {
                int a, b;
                cin >> a >> b;
                int ans = numberOfCross(a);
                if (ans != b){
                    cout << '!' << ans << ' ' << b << '\n';
                }
            }
            else if (com == 5)
            {
                int a, b, c;
                cin >> a >> b >> c;
                int ans = participant(a, b);
                if (ans != c){
                    cout << '#' << ans << ' ' << c << '\n';
                }
            }
            
        }

    }


}