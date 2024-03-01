#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int val;
    int idx;
    Node *next;
    Node *before;
};

class LinkedList
{
    Node *Head;
    Node *Tail;
};

void init()
{
}
int move()
{
}

int trade()
{
}

int main()
{
    for (int i = 0; i < 1; i++)
    {
        int mAbility[] = {1, 5, 6, 8, 7, 3, 2, 1, 4, 5, 9, 8, 7, 6, 1};
        init(15, 3, mAbility);
        cout << '\n';
        cout << move();
        // cout << '\n';
        // cout << move();
        // cout << '\n'
        //      << trade();
        // for (int i = 0; i < 3; i++)
        // {
        //     cout << totalSeason[i]->size() << '\t' << totalSeason[i]->popLeftHead()->val << '\t';
        //     cout << '\n';
        // }

        // cout << move() << '\n';
    }
}